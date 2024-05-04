# 1 "D:\\Works\\task_arduino_5_1_\\test_cup\\test_cup.ino"
# 2 "D:\\Works\\task_arduino_5_1_\\test_cup\\test_cup.ino" 2
# 3 "D:\\Works\\task_arduino_5_1_\\test_cup\\test_cup.ino" 2
# 4 "D:\\Works\\task_arduino_5_1_\\test_cup\\test_cup.ino" 2
# 5 "D:\\Works\\task_arduino_5_1_\\test_cup\\test_cup.ino" 2

// 值日表：小一、小二、小明、小四、小五、小六、小七
char list[7][20] = {"A1", "B2", "C3", "D4", "E5", "F6", "G7"};


Adafruit_SSD1306 display(128, 64, &Wire, 4);



int i = 0;

namespace
{

  const int kCePin = 5; // Chip Enable
  const int kIoPin = 6; // Input/Output
  const int kSclkPin = 7; // Serial Clock

  DS1302 rtc(kCePin, kIoPin, kSclkPin);

  String dayAsString(const Time::Day day)
  {
    switch (day)
    {
    case Time::kSunday:
      return "Sunday";
    case Time::kMonday:
      return "Monday";
    case Time::kTuesday:
      return "Tuesday";
    case Time::kWednesday:
      return "Wednesday";
    case Time::kThursday:
      return "Thursday";
    case Time::kFriday:
      return "Friday";
    case Time::kSaturday:
      return "Saturday";
    }
    return "(unknown day)";
  }

  void printTime()
  {
    Time t = rtc.time();

    const String day = dayAsString(t.day);

    char buf[50];
    snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
             day.c_str(),
             t.yr, t.mon, t.date,
             t.hr, t.min, t.sec);

    Serial.println(buf);
  }

  void title()
  {
    display.begin(0x02 /*|< Gen. display voltage from 3.3V*/, 0x3C);
    display.setTextColor(1 /*|< Draw 'on' pixels*/ /*|< Draw 'on' pixels*/); // 开像素点发光
    display.clearDisplay(); // 清屏

    display.setTextSize(2); // 设置字体大小
    display.setCursor(1, 1); // 设置显示位置
    display.println("-NameList-");

    display.display(); // 开显示
  }
} // namespace

void setup()
{
  Serial.begin(9600);
  title();
  pinMode(2 /* 定义按键*/, 0x2);
  attachInterrupt(0, change, 2);//下降沿触发中断0，调用change函数

  // 再次上传时屏蔽此代码
  // rtc.writeProtect(false);
  // rtc.halt(false);
  // Time t(2024, 5, 1, 00, 00, 00, Time::kWednesday);
  // rtc.time(t);
}

// Loop and print the time every second.
void loop()
{
  printTime();
  delay(1000);
}

void change()
{
    if (i <= 7)
    {

      display.setTextSize(2); // 设置字体大小
      display.setCursor(15, 30); // 设置显示位置

      display.println(list[i]);
      display.display(); // 开显示
      i++;
    }
    else
    {
      i = 1;

      display.setTextSize(2); // 设置字体大小
      display.setCursor(15, 30); // 设置显示位置

      display.println(list[0]);
      display.display(); // 开显示
    }
}