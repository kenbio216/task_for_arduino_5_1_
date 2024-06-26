#include <DS1302.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 值日表
char list[7][20] = {"A1", "B2", "C3", "D4", "E5", "F6", "G7"};

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

#define BUTTON 3    // 定义按键
#define buzzerPin 8 // 将无源蜂鸣器连接到Arduino的数字引脚 8

volatile boolean debounceFlag = false; // 去抖标志位
volatile int i = 0;
volatile int flag = 1;

namespace
{

  const int kCePin = 5;   // Chip Enable
  const int kIoPin = 6;   // Input/Output
  const int kSclkPin = 7; // Serial Clock

  DS1302 rtc(kCePin, kIoPin, kSclkPin);

  String dayAsString(const Time::Day day)
  {
    switch (day)
    {
    case Time::kSunday:
      return "Sunday";
    case Time::kMonday:
      return "Monday";
    case Time::kTuesday:
      return "Tuesday";
    case Time::kWednesday:
      return "Wednesday";
    case Time::kThursday:
      return "Thursday";
    case Time::kFriday:
      return "Friday";
    case Time::kSaturday:
      return "Saturday";
    }
    return "(unknown day)";
  }

  void printTime()
  {
    Time t = rtc.time();

    const String day = dayAsString(t.day);

    char buf[50];
    snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
             day.c_str(),
             t.yr, t.mon, t.date,
             t.hr, t.min, t.sec);

    Serial.println(buf);
  }

  void title()
  {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE); // 开像素点发光
    display.clearDisplay();      // 清屏

    display.setTextSize(2);  // 设置字体大小
    display.setCursor(1, 1); // 设置显示位置
    display.println("-NameList-");

    display.display(); // 开显示
  }
} // namespace

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(1, change, RISING); // 下降沿触发中断1，调用change函数
  pinMode(buzzerPin, OUTPUT);         // 设置蜂鸣器引脚为输出模式

  // 再次上传时屏蔽此代码
  rtc.writeProtect(false);
  rtc.halt(false);
  Time t(2024, 5, 1, 00, 00, 00, Time::kWednesday);
  rtc.time(t);
}

// Loop and print the time every second.
void loop()
{
  if (flag == 1)
  {
    Serial.println(i);
    title();
    display.setTextSize(2);    // 设置字体大小
    display.setCursor(15, 30); // 设置显示位置
    display.println(list[i]);
    display.display(); // 开显示
    printTime();
    flag = 0;
  }
  Time t = rtc.time();
  // 每隔两分钟报时
  if (t.min % 2 == 0 && t.sec == 0)
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
  debounceFlag = false; // 重置去抖标志位
}

void change()
{
  static unsigned long lastInterruptTime = 0;
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
