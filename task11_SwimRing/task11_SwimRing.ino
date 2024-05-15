#define controlpin 10                       // 定义开关信号线
#define controlgndpin 8                     //定义开关地线
#define controlvccpin 9                     //定义开关vcc线
#define ledpin 13                     //定义板载LED

void setup()
{
    Serial.begin(115200);
    pinMode(controlpin, INPUT);
    pinMode(controlgndpin, OUTPUT);   
    pinMode(controlvccpin, OUTPUT);
    pinMode(ledpin, OUTPUT);    
}

void loop()
{
    digitalWrite(controlgndpin, LOW); 
    digitalWrite(controlvccpin, HIGH);
    if(digitalRead(controlpin) == 0)
    {
        digitalWrite(ledpin, HIGH);
    }
    else
    {
        digitalWrite(ledpin, LOW);
    }
}