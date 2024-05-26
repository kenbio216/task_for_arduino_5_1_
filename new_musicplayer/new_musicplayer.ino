/*
 * @Author: xuyang
 * @Date: 2024-05-23 21:48:07
 * @LastEditors: xuyang
 * @LastEditTime: 2024-05-23 22:24:17
 * @FilePath: \task_for_arduino_5_1_\new_musicplayer\new_musicplayer.ino
 * @Description:
 *
 * Copyright (c) 2024 by xuyang, All Rights Reserved
 */
void setup()
{
    pinMode(7, OUTPUT);        // 接音乐播放器上面的A10
    digitalWrite(7, HIGH);     // 确保上电的时候是高电平
    pinMode(8, INPUT);         // 8号引脚接倾斜开关
    pinMode(12, INPUT_PULLUP); // 设定12号引脚为按钮1号
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);     // 2号引脚充当模拟地
    pinMode(5, INPUT_PULLUP); // 设定5号引脚为按钮2号，2号按钮默认高电平，按下去变成低电平
    digitalWrite(7, HIGH);
    Serial.begin(115200);
    Serial.println("sucesss");
    // Serial.println("Serial Initialized"); // 打印初始化信息
}

void loop()
{
    // 检测倾斜开关的状态
    if (digitalRead(8) == 0) // 如果检测到倾斜开关倾斜，那么就让7号引脚输出低电平，也就是让音乐播放器播放小星星
    {
        delay(500);
        digitalWrite(7, LOW);
        delay(500);
        digitalWrite(7, HIGH);
    }
    // 检测手动按钮的状态
    if (digitalRead(12) == 0)
    {
        delay(10);
        if (digitalRead(12) == 0)
        {
            Serial.println(digitalRead(5));
            delay(500);

            digitalWrite(7, LOW);
            Serial.println(digitalRead(5));

            delay(100);
            digitalWrite(7, HIGH);
            Serial.println(digitalRead(5));
        }
        delay(500);
    }

    delay(1);
}