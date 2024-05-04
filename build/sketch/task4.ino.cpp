#include <Arduino.h>
#line 1 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define BUTTON 3    // 定义按键
#define trigPin 9 // 超声波传感器的 trig 引脚
#define echoPin 10 // 超声波传感器的 echo 引脚
#define servoPin 6 // 舵机的控制引脚

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

Servo myservo; // 创建 Servo 对象

// 课表
char list[7][20] = {"A1", "B2", "C3", "D4", "E5", "F6", "G7"};

#line 19 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino"
void setup();
#line 27 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino"
void loop();
#line 19 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino"
void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoPin); // 附加舵机到指定引脚
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); // 发送低电平信号给 trig 引脚
  delayMicroseconds(2); // 等待2微秒
  digitalWrite(trigPin, HIGH); // 发送高电平信号给 trig 引脚
  delayMicroseconds(10); // 等待10微秒
  digitalWrite(trigPin, LOW); // 再次发送低电平信号给 trig 引脚

  duration = pulseIn(echoPin, HIGH); // 读取 echo 引脚的脉冲宽度
  distance = duration * 0.034 / 2; // 将脉冲宽度转换为距离（单位：厘米）

  Serial.print("Distance: ");
  Serial.println(distance);

  // 根据距离控制舵机位置
  if (distance <= 10) {
    myservo.write(0); // 将舵机转到 0 度位置
  } else if (distance > 10 && distance <= 20) {
    myservo.write(90); // 将舵机转到 90 度位置
  } else {
    myservo.write(180); // 将舵机转到 180 度位置
  }

  delay(100); // 等待一段时间后再次检测
}


