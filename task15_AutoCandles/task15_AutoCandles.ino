// 引脚定义
int motorPin1 = 2; // IN1连接到Arduino的2号引脚
int motorPin2 = 3; // IN2连接到Arduino的3号引脚
int motorPin3 = 4; // IN3连接到Arduino的4号引脚
int motorPin4 = 5; // IN4连接到Arduino的5号引脚
int buttonPin = 6; // 按钮连接到Arduino的6号引脚
int ledPin = 13;   // 板载LED连接到13号引脚

// 变量
bool ledState = false; // LED状态追踪

// 步进电机的步进序列
int steps[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}};

void setup()
{
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    // 读取按钮状态
    if (digitalRead(buttonPin) == LOW)
    {              // 检测到按键初次按下
        delay(10); // 等待10ms
        // 检查按钮状态是否仍然为LOW（消抖）
        if (digitalRead(buttonPin) == LOW)
        {
            while (digitalRead(buttonPin) == LOW)
                ; // 等待按键释放，防止重复触发

            ledState = !ledState;           // 切换LED状态
            digitalWrite(ledPin, ledState); // 更新LED状态
            rotateMotorTwoTurns();          // 步进电机旋转两圈
        }
    }
}

// 控制步进电机旋转两圈
void rotateMotorTwoTurns()
{
    for (int i = 0; i < 1024; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            setMotorPins(j);
            delay(2);
        }
    }
}

// 设置步进电机的引脚状态
void setMotorPins(int step)
{
    digitalWrite(motorPin1, steps[step][0]);
    digitalWrite(motorPin2, steps[step][1]);
    digitalWrite(motorPin3, steps[step][2]);
    digitalWrite(motorPin4, steps[step][3]);
}
