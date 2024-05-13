
#include <Servo.h>
Servo myservo;
int pos = 0;

const int ldrPin = A0;     // 定义光敏电阻的引脚
const int servoPin = 9;    // 定义SG90的引脚
const int beepPin = 7;     // 定义蜂鸣器引脚
const int beepPinGND = 4;  // 定义蜂鸣器引脚

void setup()
{
    pinMode(ldrPin, INPUT);
    Serial.begin(115200);
    pinMode(beepPin, OUTPUT);   // 蜂鸣器引脚设置成输出模式
    digitalWrite(beepPin, LOW); // 蜂鸣器停止工作

    pinMode(beepPinGND, OUTPUT);
    digitalWrite(beepPinGND, LOW);
    myservo.attach(9);
    Serial.println("设备上线！");
}

void loop()
{
    int ldrValue = analogRead(ldrPin); // 读取模拟口A0的值，存入变量中
    Serial.print("光敏电阻得到的数值 = ");
    Serial.println(ldrValue);          // 输出gmValue的值到串口监视器
    delay(500);
    
    if (ldrValue < 500)                //光敏电阻阈值
    {
        myservo.write(0);              //强光时，左边舵机驱动帽檐到达侧边

        digitalWrite(beepPin, HIGH);   //蜂鸣器工作
        delay(500);
        digitalWrite(beepPin, LOW); 
        delay(500);
    }

    else
    {
        digitalWrite(beepPin, LOW);    //蜂鸣器停止工作
        myservo.write(90);             //弱光时，左边舵机驱动帽檐到达前面
        delay(1000);
    }
}
