#include <DHT.h> //dht头文件
// oled头文件
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2      // DHT传感器数据引脚连接到Arduino的数字引脚2
#define DHTTYPE DHT11 // DHT类型为DHT11
DHT dht(DHTPIN, DHTTYPE);

#define mintemp 30                          // 最小温度
unsigned long startTime;                    // 记录指定温度范围内开始时间
unsigned long endTime;                      // 记录指定温度范围内结束时间
const unsigned long maxTimeInRange = 30000; // 指定温度范围内的最大时间，单位为毫秒，这里设置为30秒
bool inRange = false;                       // 是否在指定温度范围内

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
#define oled_line1 0
#define oled_line2 16
#define oled_line3 32
#define oled_line4 48
void oled_showlist(int time)
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE); // 开像素点发光

    display.clearDisplay();           // 清屏
    display.setTextSize(2);           // 设置字体大小
    display.setCursor(0, oled_line1); // 设置显示位置
    display.println("Time:");
    display.setCursor(0, oled_line2); // 设置显示位置
    display.println(time);
    display.setCursor(40, oled_line2); // 设置显示位置
    display.println("seconds");
    display.display(); // 开显示
}

#define buzzerPin 8 // 将蜂鸣器连接到Arduino的数字引脚 8
void buzzer_ring1s()
{
    tone(buzzerPin, 1000); // 发出1000Hz的声音
    delay(250);            // 0.25秒
    noTone(buzzerPin);     // 停止发声
    delay(250);            // 0.25秒
    tone(buzzerPin, 1000); // 发出1000Hz的声音
    delay(250);            // 0.25秒
    noTone(buzzerPin);     // 停止发声
    delay(250);            // 0.25秒
}

void setup()
{
    Serial.begin(115200);

    pinMode(buzzerPin, OUTPUT); // 设置蜂鸣器引脚为输出模式
    pinMode(7, OUTPUT);         // 设置蜂鸣器引脚为输出模式
digitalWrite(7, 0);

oled_showlist(0);

    dht.begin();
    startTime = millis(); // 记录程序开始时间
}

void loop()
{
    
    // delay(1000);
    float temperature = dht.readTemperature();

    // 检查是否成功读取温度值
    if (isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // 打印当前温度值到串口监视器
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // 判断温度是否在区间内
    if (temperature >= mintemp)
    {
        if (!inRange)
        {
            startTime = millis(); // 记录进入指定温度范围的时间
            inRange = true;
        }
        else if (inRange)
        {

            endTime = millis();                           // 记录离开指定温度范围的时间
            unsigned long duration = endTime - startTime; // 计算停留时间
            oled_showlist(duration / 1000);
            // Serial.print("Time in range: ");
            // Serial.print(duration / 1000); // 将毫秒转换为秒并打印
            // Serial.println(" seconds");

            // 如果停留时间超出了指定时间上限，触发蜂鸣器
            if (duration > maxTimeInRange)
            {
                buzzer_ring1s();
                duration = endTime - startTime; // 计算停留时间
                oled_showlist(duration / 1000);
            }
        }
    }
    else
    {
        if(inRange)
        {
            oled_showlist(0);
        }
        inRange = false;
    }
}
