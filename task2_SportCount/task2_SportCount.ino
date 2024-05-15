#include <TM1637Display.h>

// Define the pins for BUTTON
#define K1 8     // K1：左边运动员加分
#define K2 9     // K2：左边运动员减分
#define K3 10    // K3：右边运动员加分
#define K4 11    // K4：右边运动员减分
#define K5 12    // K5：中场休息，倒计时60秒，同时蜂鸣器响
#define GND_K 13 // 接地

// Define the pins for TM1637
#define CLK 3
#define DIO 2

// Create a TM1637Display object
TM1637Display display(CLK, DIO);

int left = 0;  // 左边运动员分数0-99
int right = 0; // 右边运动员分数0-99
// 判断K1是否按下，按下则左边运动员加分
void judge_k1()
{
  if (digitalRead(K1) == 0)
  {
    right += 1;
    delay(300);
  }
}
// 判断K2是否按下，按下则左边运动员减分
void judge_k2()
{
  if (digitalRead(K2) == 0)
  {
    right -= 1;
    delay(300);
  }
}
// 判断K3是否按下，按下则右边运动员加分
void judge_k3()
{
  if (digitalRead(K3) == 0)
  {
    left += 1;
    delay(300);
  }
}
// 判断K4是否按下，按下则右边运动员减分
void judge_k4()
{
  if (digitalRead(K4) == 0)
  {
    left -= 1;
    delay(300);
  }
}

#define buzzerPin 6 // 将蜂鸣器连接到Arduino的数字引脚 6
#define buzzergndPin 7 // 将蜂鸣器地连接到Arduino的数字引脚 7
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
// 判断K5是否按下，按下则中场休息，倒计时60秒，同时蜂鸣器响
void judge_k5()
{
  if (digitalRead(K5) == 0)
  {
    for (int i = 60; i >= 0; i--)
    {
      int tens = i / 10; // 计算十位数
      int ones = i % 10; // 计算个位数

      display.showNumberDecEx(tens * 10 + ones); // 显示数字
      buzzer_ring1s();// 等待1秒                                       
    }
    display.clear(); // Clear the display
  }
}

void setup()
{
  // Initialize the display
  Serial.begin(115200);
  display.setBrightness(0x0f); // Set the brightness to maximum
  display.clear();             // Clear the display

  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K3, INPUT_PULLUP);
  pinMode(K4, INPUT_PULLUP);
  pinMode(K5, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT); // 设置蜂鸣器引脚为输出模式
  pinMode(buzzergndPin, OUTPUT);
  digitalWrite(buzzergndPin, LOW);

  pinMode(GND_K, OUTPUT);
  digitalWrite(GND_K, LOW);
}

void loop()
{
  noTone(buzzerPin);     // 停止发声
  // Display "1234" on the TM1637 display
  if(left >= 0)
  {
    display.showNumberDecEx(left, 0b01000000, true, 2, 0);
  }
  else
  {
    left = 0;
    display.showNumberDecEx(left, 0b01000000, true, 2, 0);
  }
  if(right >= 0)
  {
      display.showNumberDecEx(right, 0b01000000, true, 2, 2);
  }
  else
  {
    right = 0;
    display.showNumberDecEx(right, 0b01000000, true, 2, 2);
  }


  judge_k1();
  judge_k2();
  judge_k3();
  judge_k4();
  judge_k5();
}