#include <Servo.h>//舵机头文件
//oled头文件
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define trigPin 9  // 超声波传感器的 trig 引脚
#define echoPin 10 // 超声波传感器的 echo 引脚
int state = LOW;
uint16_t get_distence(void)
{

    long duration, distance;
    digitalWrite(trigPin, LOW);  // 发送低电平信号给 trig 引脚
    delayMicroseconds(2);        // 等待2微秒
    digitalWrite(trigPin, HIGH); // 发送高电平信号给 trig 引脚
    delayMicroseconds(10);       // 等待10微秒
    digitalWrite(trigPin, LOW);  // 再次发送低电平信号给 trig 引脚

    duration = pulseIn(echoPin, HIGH); // 读取 echo 引脚的脉冲宽度
    distance = duration * 0.034 / 2;   // 将脉冲宽度转换为距离（单位：厘米）
    return distance;
}



#define servoPin 6 // 舵机的控制引脚
Servo myservo;     // 创建 Servo 对象


// 课表
char list[7][20] = {"text1", "text2", "text3", "text4", "text5", "text6", "text7"}; 
#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
#define oled_line1 0
#define oled_line2 16
#define oled_line3 32
#define oled_line4 48
void oled_showlist(int index)
{

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE); // 开像素点发光

    display.clearDisplay();           // 清屏
    display.setTextSize(2);           // 设置字体大小
    display.setCursor(0, oled_line1); // 设置显示位置
    display.println("ClassList:");
    display.setCursor(0, oled_line2); // 设置显示位置
    display.println(list[index]);
    display.display(); // 开显示
}

#define BUTTON 3                       // 定义按键
volatile boolean debounceFlag = false; // 去抖标志位
volatile int i = 0;
volatile int flag = 1;
volatile unsigned long lastInterruptTime = 0;
void change()
{
    unsigned long currentInterruptTime = millis();
    // 检查上次中断以来是否已经过了足够的时间（例如 50 毫秒），以避免误触发
    if (currentInterruptTime - lastInterruptTime > 300)
    {
        debounceFlag = true;                      // 设置去抖标志位
        lastInterruptTime = currentInterruptTime; // 更新上次中断时间

        flag = 1;
        if (i >= 0 && i < 6)
        {
            i = i + 1;
        }
        else if (i == 6)
        {
            i = 0;
        }
    }
}



void setup()
{
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT); // 设置超声波传感器
    pinMode(echoPin, INPUT);

    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(1, change, RISING); // 上升沿触发中断1，调用change函数

    myservo.attach(servoPin); // 附加舵机到指定引脚
}

void loop()
{
    Serial.print("Distance: ");
    Serial.println(get_distence());


    if (flag == 1)
    {
        oled_showlist(i);
        flag = 0;
        debounceFlag = false; // 重置去抖标志位
    }

    // 根据距离控制舵机位置
    if (get_distence() <= 10)
    {
        myservo.write(0); // 将舵机转到 0 度位置
    }
    else if (get_distence() > 10)
    {
        myservo.write(90); // 将舵机转到 90 度位置
    }
}

