#include <Servo.h> //舵机头文件

#define trigPin 11 // 超声波传感器的 trig 引脚
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

#define buttonpin 3 // 按键引脚3

#define buzzerPin 13   // 蜂鸣器
#define buzzergndPin 6 // 蜂鸣器地端

// void buzzer_ring05s()
// {
//     tone(buzzerPin, 1000); // 发出1000Hz的声音
//     delay(250);            // 0.25秒
//     noTone(buzzerPin);     // 停止发声
//     delay(250);            // 0.25秒
// }
int lastbutton;

void setup()
{
    Serial.begin(9600);

    pinMode(buttonpin, INPUT_PULLUP);
    lastbutton = digitalRead(buttonpin);

    pinMode(trigPin, OUTPUT); // 设置超声波传感器
    pinMode(echoPin, INPUT);

    pinMode(buzzerPin, OUTPUT); // 设置蜂鸣器
    pinMode(buzzergndPin, OUTPUT);
    digitalWrite(buzzergndPin, LOW);

    myservo.attach(servoPin); // 附加舵机到指定引脚
}

void loop()
{
    Serial.print("Distance: ");
    Serial.println(get_distence());

    // 根据距离控制蜂鸣器，距离近持续6s以上蜂鸣器报警
    if (get_distence() <= 10)
    {
        int Timeout = 5;
        while (get_distence() <= 10 && Timeout > 0)
        {
            Serial.print("Distance: ");
            Serial.println(get_distence());
            Timeout--;
            delay(1000);
            if (digitalRead(buttonpin) == !lastbutton)
            {
                lastbutton = digitalRead(buttonpin);
                noTone(buzzerPin);
                return;
            }
        }
        // 6s后蜂鸣器报警
        if (Timeout <= 0)
        {
            tone(buzzerPin, 1000);
        }
        // 如果水开不到6s
        else
        {
            noTone(buzzerPin);
            return;
        }
        // 按键按下蜂鸣器停止报警
        if (digitalRead(buttonpin) == !lastbutton)
        {
            lastbutton = digitalRead(buttonpin);
            noTone(buzzerPin);
            return;
        }
        // // 蜂鸣器响10s后，舵机运行，蜂鸣器停止
        while (get_distence() <= 10 && Timeout >= 0 && Timeout < 5)
        {
            Serial.print("Distance: ");
            Serial.println(get_distence());
            Timeout--;
            delay(1000);
            if (digitalRead(buttonpin) == !lastbutton)
            {
                lastbutton = digitalRead(buttonpin);
                noTone(buzzerPin);
                return;
            }
        }
        if (Timeout < 0)
        {
            myservo.write(180);
            noTone(buzzerPin);
            delay(1000);
        }
        // 水开不到10s
        else if (Timeout < 5 && Timeout >= 0)
        {
            noTone(buzzerPin);
        }
    }
    else
    {
        Serial.print("Distance: ");
        Serial.println(get_distence());
        return;
    }
}
