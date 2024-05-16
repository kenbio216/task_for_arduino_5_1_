#define controlpin 10    // 定义开关信号线
#define controlgndpin 12 // 定义开关地线
#define controlvccpin 11 // 定义开关vcc线

#define modepin 2 // 模式切换按钮
int mode = 0;     // 0为自动，1为手动
// 模式切换函数，按下按钮为自动，松开按钮为手动
void modechange()
{
    if (digitalRead(modepin) == LOW)
    {
        mode = 0;
    }
    else
    {
        mode = 1;
    }
    Serial.print("the mode is ");
    Serial.println(mode);
}

// 报警按钮
#define buttonin 3  // 报警按钮输入引脚
#define buttongnd 4 // 报警按钮接地端引脚

// 蜂鸣器
#define buzzerpin 8 // 定义蜂鸣器
#define buzzer_gndpin 6
void buzzer_ring05s()
{
    tone(buzzerpin, 1000); // 发出1000Hz的声音
    delay(250);            // 0.25秒
    noTone(buzzerpin);     // 停止发声
    delay(250);            // 0.25秒
}

// 自动时倾斜开关检测到一定时间的倾斜后报警
int flag = 0; 
unsigned long startTime;
void autojudge()
{
    if (mode == 0)
    {
        if (digitalRead(controlpin) == LOW && flag == 0 && mode == 0)
        {
            // 开始计时
            startTime = millis();
            flag = 1;
        }
        if (digitalRead(controlpin) == LOW && flag == 1 && mode == 0)
        {
            
            Serial.print("the lasttime is ");
            Serial.println((millis() - startTime) / 1000);
            if (millis() - startTime >= 5000 && mode == 0)
            {
                buzzer_ring05s();
                modechange();
                buzzer_ring05s();
            }
        }
        else
        {
            flag = 0;
        }
    }
    else
    {
        flag = 0;
    }
}

// 手动时按下按钮报警
void mannualjudge()
{
    if (mode == 1)
    {
        if (digitalRead(buttonin) == HIGH && mode == 1)
        {
            Serial.println("buzzer start to ring");
            buzzer_ring05s();
            modechange();
        }
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(buttonin, INPUT_PULLUP);
    pinMode(buttongnd, OUTPUT);
    digitalWrite(buttongnd, LOW);

    pinMode(controlpin, INPUT);
    pinMode(controlgndpin, OUTPUT);
    digitalWrite(controlgndpin, LOW);
    pinMode(controlvccpin, OUTPUT);
    digitalWrite(controlvccpin, HIGH);

    pinMode(modepin, INPUT_PULLUP);

    pinMode(buzzerpin, OUTPUT);
    pinMode(buzzer_gndpin, OUTPUT);
    digitalWrite(buzzer_gndpin, LOW);
}

void loop()
{
    modechange();
    autojudge();
    mannualjudge();
}