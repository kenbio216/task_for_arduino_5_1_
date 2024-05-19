#include <Servo.h> //舵机头文件
#define servoPin 7 // 舵机的控制引脚
Servo myservo;     // 创建 Servo 对象
int posClosed = 0; // 关闭时舵机位置
int posOpen = 90;  // 开启时舵机位置
void openDoor()
{
    Serial.println("door open!");
    myservo.write(posOpen);
}

#define trigPin 5           // 超声波传感器的 trig 引脚
#define echoPin 6           // 超声波传感器的 echo 引脚
#define gndPin 4            // 超声波传感器的 gnd 引脚
uint16_t get_distence(void) // 获得距离
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

#define buzzerPin 3    // 蜂鸣器
#define buzzergndPin 2 // 蜂鸣器地端
void buzzer_ring1s()   // 蜂鸣器鸣叫1s
{
    Serial.println("buzzeer ring1s");
    tone(buzzerPin, 1000); // 发出1000Hz的声音
    delay(250);            // 0.25秒
    noTone(buzzerPin);     // 停止发声
    delay(250);            // 0.25秒
    tone(buzzerPin, 1000); // 发出1000Hz的声音
    delay(250);            // 0.25秒
    noTone(buzzerPin);     // 停止发声
    delay(250);            // 0.25秒
}

/*------------------------------------------------密码输入----------------------------------------*/
#define buttonPin1 8      // 1按键引脚
#define buttonPin2 9      // 2按键引脚
#define buttonPin3 10     // 3按键引脚
#define buttonPin4 11     // 4按键引脚
#define enterbuttonPin 12 // 确认按键引脚

int buttonState1;     // 第一个按键状态
int buttonState2;     // 第二个按键状态
int buttonState3;     // 第三个按键状态
int buttonState4;     // 第四个按键状态
int enterbuttonState; // 确认按键状态

int correctPassword[] = {1, 1, 1, 0}; // 正确密码(按下为1，松开为0)
int enteredPassword[4];               // 用户输入的密码

int attempts = 0; // 尝试次数

bool checkPassword() // 检查密码是否正确
{
    for (int i = 0; i < 4; i++)
    {
        if (enteredPassword[i] != correctPassword[i])
        {
            return false;
        }
    }
    return true;
}
/*---------------------------------------主函数-----------------------------------------------------*/
int exist = 0; // 是否有外卖
void setup()
{
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT); // 设置超声波传感器
    pinMode(echoPin, INPUT);
    pinMode(gndPin, OUTPUT);
    digitalWrite(gndPin, LOW);

    myservo.attach(servoPin); // 附加舵机到指定引脚
    myservo.write(posOpen);   // 默认为开门状态

    pinMode(buzzerPin, OUTPUT); // 设置蜂鸣器
    pinMode(buzzergndPin, OUTPUT);
    digitalWrite(buzzergndPin, LOW);

    pinMode(buttonPin1, INPUT_PULLUP); // 设置按键
    pinMode(buttonPin2, INPUT_PULLUP);
    pinMode(buttonPin3, INPUT_PULLUP);
    pinMode(buttonPin4, INPUT_PULLUP);
    pinMode(enterbuttonPin, INPUT_PULLUP);
    enterbuttonState = digitalRead(enterbuttonPin);
}

void loop()
{
    Serial.print("Distance: ");
    Serial.println(get_distence());

    // 根据距离控制蜂鸣器，距离近持续3s以上蜂鸣器报警
    if (get_distence() <= 10 && exist == 0)
    {
        int Timeout = 3;
        while (get_distence() <= 10 && Timeout > 0)
        {
            Serial.print("Distance: ");
            Serial.println(get_distence());
            Timeout--;
            delay(1000);
        }
        // 3s后舵机转动关门，蜂鸣器报警3s
        if (Timeout == 0)
        {
            Serial.println("door close!");
            myservo.write(posClosed);
            for (int i = 0; i < 3; i++)
            {
                buzzer_ring1s();
                exist = 1;
            }
        }
    }

    // 读取按键状态
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);

    // 保存用户输入的密码
    enteredPassword[0] = buttonState1;
    enteredPassword[1] = buttonState2;
    enteredPassword[2] = buttonState3;
    enteredPassword[3] = buttonState4;

    // 按下enter检查密码是否正确
    if (digitalRead(enterbuttonPin) != enterbuttonState)
    {
        enterbuttonState = digitalRead(enterbuttonPin);
        if (checkPassword())
        {
            openDoor();
            attempts = 0;
            exist = 0;
        }
        else
        {
            attempts++;
            Serial.print("Attempt is ");
            Serial.println(attempts);
            if (attempts >= 3)
            {
                buzzer_ring1s();
                buzzer_ring1s();
                buzzer_ring1s();
                attempts = 0;
            }
        }
        delay(200);
    }
}
