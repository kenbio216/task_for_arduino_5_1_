
#include <Servo.h> //舵机头文件

#define trigPin 9  // 超声波传感器的 trig 引脚
#define echoPin 10 // 超声波传感器的 echo 引脚
int state = LOW;
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

#define servoPin 11 // 舵机的控制引脚
Servo myservo;     // 创建 Servo 对象

#define buzzerPin 7 // 将蜂鸣器连接到Arduino的数字引脚 8
#define buzzergndPin 4 // 将蜂鸣器连接到Arduino的数字引脚 
void buzzer_ring05s()
{
    tone(buzzerPin, 1000); // 发出1000Hz的声音
    delay(250);            // 0.25秒
    noTone(buzzerPin);     // 停止发声
    delay(250);            // 0.25秒
}

void setup()
{
    Serial.begin(9600);

    pinMode(buzzerPin, OUTPUT); // 设置蜂鸣器
    pinMode(buzzergndPin, OUTPUT); // 设置蜂鸣器
    digitalWrite(buzzergndPin, LOW);
    

    pinMode(trigPin, OUTPUT); // 设置超声波传感器
    pinMode(echoPin, INPUT);

    myservo.attach(servoPin); // 附加舵机到指定引脚
    myservo.write(90);        // 舵机不动
}
void loop()
{
    Serial.print("Distance: ");
    Serial.println(get_distence());

    // 根据距离控制蜂鸣器，距离近蜂鸣器报警，且舵机转动打掉遮挡物
    if (get_distence() <= 20)
    {
        myservo.write(180); // 舵机旋转
        buzzer_ring05s();
    }
    else
    {
        myservo.write(90); // 舵机不动
        noTone(buzzerPin); // 停止发声
    }
}
