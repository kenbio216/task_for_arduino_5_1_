#include <Servo.h>

Servo myServo;                      // 创建舵机控制对象
const int buttonPin1 = 4;           // 按键的一个引脚
const int buttonPin2 = 5;           // 按键的另一个引脚
const int servoPin = 7;             // 舵机的信号引脚
const int ledPin = 13;              // 板载LED灯连接的引脚
int buttonState = LOW;              // 用于保存按键的稳定状态
int lastButtonState = LOW;          // 上一次按键的读取状态
unsigned long lastDebounceTime = 0; // 上次状态改变的时间点
unsigned long debounceDelay = 50;   // 消抖延时阈值，单位毫秒
bool ledState = LOW;                // LED的当前状态

void setup()
{
    Serial.begin(115200);              // 初始化串口通信，波特率设置为115200
    pinMode(buttonPin1, OUTPUT);       // 设置buttonPin1为输出模式
    pinMode(buttonPin2, INPUT);        // 设置buttonPin2为输入模式
    digitalWrite(buttonPin1, LOW);     // 将buttonPin1设置为低电平
    pinMode(ledPin, OUTPUT);           // 设置LED引脚为输出模式
    digitalWrite(ledPin, ledState);    // 初始化LED状态
    myServo.attach(servoPin);          // 将舵机连接到指定的引脚
    Serial.println("Setup complete!"); // 打印初始化完成信息
}

void loop()
{
    int reading = digitalRead(buttonPin2); // 读取buttonPin2的当前值
    Serial.print("Button reading: ");      // 打印当前按钮读数
    Serial.println(reading);

    // 检查按钮状态是否改变
    if (reading != lastButtonState)
    {
        lastDebounceTime = millis(); // 重置去抖时间
        Serial.println("Button state changed!");
    }

    // 只有在足够的时间过后，才确认按钮状态
    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        // 如果按钮状态已经稳定
        if (reading != buttonState)
        {
            buttonState = reading;
            Serial.print("Debounced button state: ");
            Serial.println(buttonState);

            // 按钮从未按下到按下的状态变化
            if (buttonState == HIGH)
            {
                myServo.write(180); // 舵机转到180度
                delay(1000);        // 等待1秒
                myServo.write(0);   // 舵机回到0度
                Serial.println("Servo moved to 180 degrees and returned to 0 degrees");

                // 切换LED状态
                ledState = !ledState;           // 改变LED的当前状态
                digitalWrite(ledPin, ledState); // 应用新的LED状态
                Serial.print("LED state switched to: ");
                Serial.println(ledState);
            }
        }
    }

    lastButtonState = reading; // 更新上一次读取的按钮状态
    delay(10);                 // 稍微延迟以避免过快的处理速度
}
