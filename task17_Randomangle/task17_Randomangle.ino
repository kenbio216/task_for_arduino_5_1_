#include <Stepper.h>
#include <stdio.h>

// 灯按钮连接到Arduino的3号引脚
#define lightbutton 3
#define lightgndbutton 2

// 灯连接到Arduino的12.10号引脚
#define light1 12
#define light1gnd 13
#define light2 10
#define light2gnd 11

bool lightstate;
unsigned long lastInterruptTime = 0;
unsigned long currentInterruptTime;
void change()
{
  currentInterruptTime = millis();
  // 检查上次中断以来是否已经过了足够的时间（例如 300 毫秒），以避免误触发
  if (currentInterruptTime - lastInterruptTime > 300)
  {
    lastInterruptTime = currentInterruptTime; // 更新上次中断时间
    lightstate = !lightstate;
    digitalWrite(light1, lightstate);
    digitalWrite(light2, lightstate);
  }

  // if (digitalRead(lightbutton) == LOW)
  // {            // 检测到按键初次按下
  //   delay(10); // 等待10ms
  //   // 检查按钮状态是否仍然为LOW（消抖）
  //   if (digitalRead(lightbutton) == LOW)
  //   {

  //     digitalWrite(light1, !lightstate);
  //     digitalWrite(light2, !lightstate);
  //     lightstate = !lightstate;
  //   }
  // }
}

// 这里设置步进电机旋转一圈是多少步
#define STEPS 100

// 设置步进电机的步数和引脚（就是驱动板上IN1～IN4连接的四个数字口）。
Stepper stepper(STEPS, 4, 6, 5, 7);

// 电机旋转
void run(int num)
{
  // 逆时针旋转一周
  Serial.println("Counterclockwise rotation");

  stepper.step(num * (2048 / 6)); // 4步模式下旋转一周用2048 步

  digitalWrite(light1, lightstate);
  digitalWrite(light2, lightstate);

  delay(500);
}

// 随机按钮连接到Arduino的8号引脚
#define buttonPin 8
#define buttongndPin 9

void setup()
{

  // 设置电机的转速：每分钟为90步
  stepper.setSpeed(90);

  // 初始化串口，用于调试输出信息
  Serial.begin(115200);

  // 初始化随机按键
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttongndPin, OUTPUT);
  digitalWrite(buttongndPin, LOW);

  // 初始化灯按键
  pinMode(lightbutton, INPUT_PULLUP);
  pinMode(lightgndbutton, OUTPUT);
  digitalWrite(lightgndbutton, LOW);
  attachInterrupt(1, change, FALLING); // 下降沿触发中断1，调用change函数

  // 初始化灯
  lightstate = 0;
  pinMode(light1, OUTPUT);
  digitalWrite(light1, lightstate);

  pinMode(light2, OUTPUT);
  digitalWrite(light2, lightstate);

  pinMode(light1gnd, OUTPUT);
  digitalWrite(light1gnd, LOW);
  pinMode(light2gnd, OUTPUT);
  digitalWrite(light2gnd, LOW);
}

void loop()
{
  Serial.println(lightstate);

  if (digitalRead(buttonPin) == LOW)
  {            // 检测到按键初次按下
    delay(10); // 等待10ms
    // 检查按钮状态是否仍然为LOW（消抖）
    if (digitalRead(buttonPin) == LOW)
    {
      int num = random(1, 7);
      run(num);
    }
  }
}
