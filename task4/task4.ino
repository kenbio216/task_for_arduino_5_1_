#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON 3    // 定义按键
#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

// 课表
char list[7][20] = {"A1", "B2", "C3", "D4", "E5", "F6", "G7"};