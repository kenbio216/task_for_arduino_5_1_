/*
 * @Author: xuyang
 * @Date: 2024-04-26 22:10:01
 * @LastEditors: xuyang
 * @LastEditTime: 2024-05-05 14:47:11
 * @FilePath: \task_for_arduino_5_1_\task6_ard_uno_maozi\task6_ard_uno_maozi.ino
 * @Description:
 *
 * Copyright (c) 2024 by xuyang, All Rights Reserved
 */

#include <Servo.h>
Servo myservo;
int pos = 0;

const int ldrPin = A0;    // 定义光敏电阻的引脚
const int servoPin = 9;   // 定义SG90的引脚
const int beepPin = 7;    // 定义蜂鸣器引脚
const int beepPinGND = 4; // 定义蜂鸣器引脚

void sweep() // 让舵机旋转
{
    for (pos = 0; pos <= 180; pos += 1)
    {
        myservo.write(pos);
        delay(15);
    }
    for (pos = 180; pos >= 0; pos -= 1)
    {
        myservo.write(pos);
        delay(15);
    }
}

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
    Serial.println(ldrValue); // 输出gmValue的值到串口监视器
    delay(500);
    if (ldrValue < 700)
    {
        digitalWrite(beepPin, HIGH); // 蜂鸣器工作
        sweep();
    }
    else
    {
        digitalWrite(beepPin, LOW); // 蜂鸣器停止工作
    }
}
