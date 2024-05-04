#include <DHT.h>

#define DHTPIN 2      // DHT传感器数据引脚连接到Arduino的数字引脚2
#define DHTTYPE DHT11 // DHT类型为DHT11
#define buzzerPin 7   // 将无源蜂鸣器连接到Arduino的数字引脚 7
#define FANPIN 12      // 定义风扇引脚
int redPin = 9;       // 将红色LED连接到引脚9
int greenPin = 10;    // 将绿色LED连接到引脚10
int bluePin = 11;     // 将蓝色LED连接到引脚11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(FANPIN, OUTPUT);

  pinMode(buzzerPin, OUTPUT); // 设置蜂鸣器引脚为输出模式

  Serial.begin(115200);
  Serial.println("DHTxx test!");
  dht.begin();
}

void loop()
{
  digitalWrite(8, 0);

  float temperature = dht.readTemperature(); // 读取温度（摄氏度）
  float humidity = dht.readHumidity();       // 读取湿度

  if (temperature <= 28)
  {
    // 蓝色
    setColor(0, 0, 100);
    Serial.println("蓝色");
    digitalWrite(FANPIN, LOW);
    delay(1000);
  }
  else if (temperature >= 29)
  {
    // 红色
    setColor(0, 100, 0);
    Serial.println("红色");
    digitalWrite(FANPIN, HIGH);
    delay(1000);
  }
  else
  {
    // 绿色
    setColor(100, 0, 0);
    Serial.println("绿色");
    digitalWrite(FANPIN, LOW);
    tone(buzzerPin, 1000); // 发出1000Hz的声音
    delay(250); // 0.25秒
    noTone(buzzerPin); // 停止发声
    delay(250); // 0.25秒
    tone(buzzerPin, 1000); // 发出1000Hz的声音
    delay(250); // 0.25秒
    noTone(buzzerPin); // 停止发声
    delay(250); // 0.25秒
    // delay(1000);
  }

  Serial.print("温度：");
  Serial.print(temperature);
  Serial.print("°C, 湿度：");
  Serial.print(humidity);
  Serial.println("%");
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
