/*
 * @Author: xuyang
 * @Date: 2024-05-04 20:49:04
 * @LastEditors: xuyang
 * @LastEditTime: 2024-05-05 18:49:32
 * @FilePath: \task_for_arduino_5_1_\task9_SmartMedicalBox\task9_SmartMedicalBox.ino
 * @Description: 
 * 
 * Copyright (c) 2024 by xuyang, All Rights Reserved 
 */

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 设置OLED显示屏的宽度和高度
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 创建舵机对象
Servo myservo;

// 函数指针类型定义
typedef void (*FunctionPointer)();

// 声明两个状态函数
void stateOne();
void stateTwo();

// 当前状态函数指针
FunctionPointer currentFunction = stateOne;

/* ---------------------------------- 定义引脚 ---------------------------------- */

void setup()
{
    // 初始化OLED显示屏
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        for (;;)
            ;
    }
    pinMode(8, OUTPUT);
    digitalWrite(8, LOW);

    // 初始化舵机，并连接到引脚9
    myservo.attach(10);

    // 设置初始状态函数
    currentFunction = stateOne;
}

void loop()
{
    // 调用当前状态函数
    currentFunction();
}

// 第一个状态函数
void stateOne()
{
    myservo.write(0);       // 舵机旋转到0度
    display.clearDisplay(); // 清空OLED显示
    display.display();      // 更新显示
    noTone(6);              // 关闭蜂鸣器声音（假设连接在引脚8）

    delay(5000);                // 延迟5秒
    currentFunction = stateTwo; // 切换到第二个状态函数
}

// 第二个状态函数
void stateTwo()
{
    myservo.write(180);     // 舵机旋转到180度
    display.clearDisplay(); // 清空显示
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("one day/3 times"); // 显示第一行文本
    display.setCursor(0, 10);
    display.println("before dinner"); // 显示第二行文本
    display.display();                // 更新显示
    tone(6, 1000);                    // 蜂鸣器发声（频率1000Hz，假设连接在引脚8）

    delay(5000);                // 延迟5秒
    currentFunction = stateOne; // 切换到第一个状态函数
}
