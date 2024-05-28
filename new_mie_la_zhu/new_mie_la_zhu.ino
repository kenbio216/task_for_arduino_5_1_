/*
 * @Author: xuyang
 * @Date: 2024-05-28 13:09:05
 * @LastEditors: xuyang
 * @LastEditTime: 2024-05-28 22:16:42
 * @FilePath: \task_for_arduino_5_1_\new_mie_la_zhu\new_mie_la_zhu.ino
 * @Description:
 *
 * Copyright (c) 2024 by xuyang, All Rights Reserved
 */
// 定义引脚
const int button1Pin = 2;
const int button2Pin = 3;
const int in1Pin = 4;
const int in2Pin = 5;
const int enPin = 9;

// 热敏电阻的引脚
const int rePin = 9;
// 蜂鸣器的引脚
const int tonePin = 11;

void setup()
{
    // 初始化串口
    Serial.begin(115200);

    // 配置引脚模式
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(enPin, OUTPUT);
    pinMode(rePin, INPUT);
    pinMode(tonePin, OUTPUT);

    // 把输出引脚当做GND，GND不够了
    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);

    // 启动电机控制
    analogWrite(enPin, 255); // 设置PWM输出，255表示全速
}

void loop()
{
    /* ---------------------------------- 按键部分 ---------------------------------- */
    // 读取按钮状态
    if (digitalRead(button1Pin) == 0)
    {
        delay(10);
        if (digitalRead(button1Pin) == 0)
        {
            Serial.println("按键1按下");
            // 顺时针旋转
            digitalWrite(in1Pin, HIGH);
            digitalWrite(in2Pin, LOW);
            delay(1000);
        }
        while (digitalRead(button1Pin) == 0)
        {
        };
    }

    else if (digitalRead(button2Pin) == 0)
    {
        delay(10);
        if (digitalRead(button2Pin) == 0)
        {
            Serial.println("按键2按下");
            // 顺时针旋转
            digitalWrite(in1Pin, LOW);
            digitalWrite(in2Pin, HIGH);
            delay(1000);
        }
        while (digitalRead(button2Pin) == 0)
        {
        };
    }
    else
    {
        // 电机停止
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
    }

    /* ------------------------------- 热敏电阻和蜂鸣器部分 ------------------------------- */
    if (digitalRead(rePin) == 1)
    {
        Serial.println("热敏电阻的值为：1");
        // digitalWrite(tonePin, HIGH);
        // delay(1000);
        tone(tonePin, 1000);
        delay(1000);
        noTone(tonePin);
    }
}
