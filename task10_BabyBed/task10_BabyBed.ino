#include <Servo.h> //舵机头文件

#define buzzerPin 2 // 将蜂鸣器连接到Arduino的数字引脚 2
#define vcc2Pin 3   // 蜂鸣器的 vcc 引脚
#define gnd2Pin 4   // 蜂鸣器的 gnd 引脚

#define min_distence 5 // 定义最小的距离
#define vccPin 11      // 超声波传感器的 vcc 引脚
#define gndPin 8       // 超声波传感器的 gnd 引脚
#define trigPin 9      // 超声波传感器的 trig 引脚
#define echoPin 10     // 超声波传感器的 echo 引脚
uint16_t get_distence(void)
{
    long duration, distance;
    digitalWrite(trigPin, LOW);  // 发送低电平信号给 trig 引脚
    delayMicroseconds(2);        // 等待2微秒
    digitalWrite(trigPin, HIGH); // 发送高电平信号给 trig 引脚
    delayMicroseconds(10);       // 等待10微秒
    digitalWrite(trigPin, LOW);  // 再次发送低电平信号给 trig 引脚

    duration = pulseIn(echoPin, HIGH); // 读取 echo 引脚的脉冲宽度
    distance = duration * 0.034 / 2;   // 将脉冲宽度转换为距离（单位：厘米）
    return distance;
}

#define servoPin 6 // 舵机的控制引脚
Servo myservo;     // 创建 Servo 对象

int the_distence;

void setup()
{
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT); // 设置超声波传感器
    pinMode(echoPin, INPUT);
    pinMode(gndPin, OUTPUT);
    pinMode(vccPin, OUTPUT);
    pinMode(gnd2Pin, OUTPUT);
    pinMode(vcc2Pin, OUTPUT);

    myservo.attach(servoPin); // 附加舵机到指定引脚
}
void loop()
{
    digitalWrite(gndPin, LOW);
    digitalWrite(vccPin, HIGH);
    digitalWrite(gnd2Pin, LOW);
    digitalWrite(vcc2Pin, HIGH);
    the_distence = get_distence();

    Serial.print("Distance: ");
    Serial.println(the_distence);

    // 根据距离控制舵机位置
    if (the_distence <= min_distence)
    {
        myservo.write(0); // 将舵机转到 0 度位置
        noTone(buzzerPin);
        delay(250);
        tone(buzzerPin, 1000);
        delay(500);
        noTone(buzzerPin);
        delay(500);
    }
    else
    {
        myservo.write(90); // 将舵机转到 90 度位置
        noTone(buzzerPin);
        delay(500);
    }
}
