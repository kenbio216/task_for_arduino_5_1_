#include <DHT.h> //dht头文件
// oled头文件
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define DHTPIN 2      // DHT传感器数据引脚连接到Arduino的数字引脚2
#define DHTTYPE DHT11 // DHT类型为DHT11
DHT dht(DHTPIN, DHTTYPE);


#define mintemp 28
#define maxtemp 29
unsigned long startTime;  // 记录指定温度范围内开始时间
unsigned long endTime;    // 记录指定温度范围内结束时间
const unsigned long maxTimeInRange = 30000; // 指定温度范围内的最大时间，单位为毫秒，这里设置为30秒
bool inRange = false;     // 是否在指定温度范围内




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

    Serial.println("DHTxx test!");
    dht.begin();
}

void loop()
{
}
