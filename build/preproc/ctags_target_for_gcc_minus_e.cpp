# 1 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino"
# 2 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino" 2
# 3 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino" 2
# 4 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino" 2
# 5 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino" 2







Adafruit_SSD1306 display(128, 64, &Wire, 4);

Servo myservo; // 创建 Servo 对象

// 课表
char list[7][20] = {"A1", "B2", "C3", "D4", "E5", "F6", "G7"};

void setup()
{
  Serial.begin(9600);
  pinMode(9 /* 超声波传感器的 trig 引脚*/, 0x1);
  pinMode(10 /* 超声波传感器的 echo 引脚*/, 0x0);
  myservo.attach(6 /* 舵机的控制引脚*/); // 附加舵机到指定引脚
}

void loop() {
  long duration, distance;
  digitalWrite(9 /* 超声波传感器的 trig 引脚*/, 0x0); // 发送低电平信号给 trig 引脚
  delayMicroseconds(2); // 等待2微秒
  digitalWrite(9 /* 超声波传感器的 trig 引脚*/, 0x1); // 发送高电平信号给 trig 引脚
  delayMicroseconds(10); // 等待10微秒
  digitalWrite(9 /* 超声波传感器的 trig 引脚*/, 0x0); // 再次发送低电平信号给 trig 引脚

  duration = pulseIn(10 /* 超声波传感器的 echo 引脚*/, 0x1); // 读取 echo 引脚的脉冲宽度
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
