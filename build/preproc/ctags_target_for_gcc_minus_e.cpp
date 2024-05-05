# 1 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino"
# 2 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino" 2
# 3 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino" 2
# 4 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino" 2
# 5 "D:\\Works\\task_arduino_5_1_\\task4\\task4.ino" 2



int state = 0x0;
uint16_t get_distence(void)
{

    long duration, distance;
    digitalWrite(9 /* 超声波传感器的 trig 引脚*/, 0x0); // 发送低电平信号给 trig 引脚
    delayMicroseconds(2); // 等待2微秒
    digitalWrite(9 /* 超声波传感器的 trig 引脚*/, 0x1); // 发送高电平信号给 trig 引脚
    delayMicroseconds(10); // 等待10微秒
    digitalWrite(9 /* 超声波传感器的 trig 引脚*/, 0x0); // 再次发送低电平信号给 trig 引脚

    duration = pulseIn(10 /* 超声波传感器的 echo 引脚*/, 0x1); // 读取 echo 引脚的脉冲宽度
    distance = duration * 0.034 / 2; // 将脉冲宽度转换为距离（单位：厘米）
    return distance;
}


Servo myservo; // 创建 Servo 对象


// 课表
char list[7][20] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

Adafruit_SSD1306 display(128, 64, &Wire, 4);




void oled_showlist(int index)
{

    display.begin(0x02 /*|< Gen. display voltage from 3.3V*/, 0x3C);
    display.setTextColor(1 /*|< Draw 'on' pixels*/ /*|< Draw 'on' pixels*/); // 开像素点发光

    display.clearDisplay(); // 清屏
    display.setTextSize(2); // 设置字体大小
    display.setCursor(0, 0); // 设置显示位置
    display.println("-NameList-");
    display.setCursor(0, 16); // 设置显示位置
    display.println(list[index]);
    display.display(); // 开显示
}


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
        debounceFlag = true; // 设置去抖标志位
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



void setup()
{
    Serial.begin(9600);

    pinMode(9 /* 超声波传感器的 trig 引脚*/, 0x1); // 设置超声波传感器
    pinMode(10 /* 超声波传感器的 echo 引脚*/, 0x0);

    pinMode(3 /* 定义按键*/, 0x2);
    attachInterrupt(1, change, 3); // 上升沿触发中断1，调用change函数

    myservo.attach(6 /* 舵机的控制引脚*/); // 附加舵机到指定引脚
}

void loop()
{
    Serial.print("Distance: ");
    Serial.println(get_distence());


    if (flag == 1)
    {
        oled_showlist(i);
        flag = 0;
        debounceFlag = false; // 重置去抖标志位
    }

    // 根据距离控制舵机位置
    if (get_distence() <= 10)
    {
        myservo.write(0); // 将舵机转到 0 度位置
    }
    else if (get_distence() > 10 && get_distence() <= 20)
    {
        myservo.write(90); // 将舵机转到 90 度位置
    }
    else
    {
        myservo.write(180); // 将舵机转到 180 度位置
    }
}
