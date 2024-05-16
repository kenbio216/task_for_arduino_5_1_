#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 值日表
char list[7][20] = {"A1", "B2", "C3", "D4", "E5", "F6", "G7"};

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


#define OLED_RESET 4
#define OLED_VCC 13

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
  display.println("-NameList-");
  display.setCursor(0, oled_line2); // 设置显示位置
  display.println(list[index]);
  display.display(); // 开显示
}



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

  pinMode(OLED_VCC, OUTPUT);
  digitalWrite(OLED_VCC, HIGH);

  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(1, change, RISING); // 上升沿触发中断1，调用change函数

  pinMode(buzzerPin, OUTPUT); // 设置蜂鸣器引脚为输出模式
}

// Loop and print the time every second.
void loop()
{
  if (flag == 1)
  {
    oled_showlist(i);
    flag = 0;
    debounceFlag = false; // 重置去抖标志位
  }

  // 蜂鸣器每隔30s报时喝水
  unsigned long buzzer_currenttime = millis(); //
  Serial.println(buzzer_currenttime);
  if (buzzer_currenttime % (1*30*1000) == 0)
  {
    buzzer_ring1s();
  }
}
