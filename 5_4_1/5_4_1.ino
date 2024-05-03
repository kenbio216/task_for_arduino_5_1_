#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//超声波定义
const int TrigPin = 4;
const int EchoPin = 5;  
//指示灯接口定义
int led_button= 14;
int distance;
const char* ssid = "Mi11LE";//替换自己的WIFI
const char* password = "Gqw415319";//替换自己的WIFI
const char* mqtt_server = "192.168.91.220";//替换自己的MQTT服务器IP地址
int ledgan;
char buffer[50];
//下面是一系列变量定义及初始化
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;//用来保存上一次接收TOPIC的时间
char msg[50];//用来存放ESP8266将要PUBLISH到服务器的消息
int value = 0;//这个变量假装自己是温度值，在后面的程序中每秒钟累计加1
int key_flag=1;//这个变量用来和KEY端口读过来的值做比较
char ms[50];//用来存放ESP8266将要PUBLISH到服务器的消息
void ult_test(){
  digitalWrite(TrigPin, LOW);     
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW); 
  int distance = pulseIn(EchoPin, HIGH);   
  distance= distance/58;
//  Serial.print("距离实时值：");
//  Serial.print(distance);
//  Serial.println(" cm");
}
//让ESP8266开发板能够接入WiFi网络
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("童卓 2022030233 罗子丹 2022020584 Connecting to ");
  Serial.println(ssid);//串口显示提示文字Connecting to ssid

  WiFi.begin(ssid, password);//开始连接ssid网络

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }//如果未连接上WiFi，串口每半分钟打印一个.

  randomSeed(micros());//根据当前时间产生随机数种子

  Serial.println("");
  Serial.println("童卓 2022030233 罗子丹 2022020584 WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());//如果连接上WiFi，串口显示WiFi connected以及ESP8266开发板的IP地址
}

//开发板自己接受信息函数
//处理MQTT服务器虚拟客户端PUBLISH的TOPIC
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("童卓 2022030233 罗子丹 2022020584 Message arrived [");
  Serial.print(topic);
  Serial.print("] ");//串口显示Message arrived [topic]，主题（topic）是led 亮度传感器数值信息
// 将字节数组中的每个字节依次左移并累加到 edgan 中
  snprintf(buffer, sizeof(buffer), "%s", payload);

  // 使用 atoi 将字符串转换为整数
  ledgan = atoi(buffer);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);

  }//payload是具体的消息，比如Hello World；length是消息长度；payload是个字符串，因此这里将字符串的每个字符依次打印出来
  Serial.println();
  //开发板端口蓝灯控制

    if ((char)payload[0] == '1'&&(char)payload[1] == '1') {
    digitalWrite(0, LOW);   
  }//读取payload的第1个字符，如果这个字符是1，就开BUILTIN_LED灯
  if ((char)payload[0] == '1'&&(char)payload[1] == '0'){
    digitalWrite(0, HIGH);  
  }//读取payload的第1个字符，如果这个字符是0，就关BUILTIN_LED灯
  //结束
    
 
  
}


//让ESP8266开发板能够接入MQTT服务器
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("童卓 2022030233 罗子丹 2022020584 Attempting MQTT connection...");//如果ESP8266开发板还没有连上MQTT服务器，串口输出Attempting MQTT connection...
    // Create a random client ID
    String clientId = "ESP8266Client-";//给ESP8266开发板随机生成一个客户端ID号，在它连上MQTT服务器后，我们在MQTT服务器网页上能够查看到
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("童卓 2022030233 罗子丹 2022020584 connected");//如果ESP8266开发板连上了MQTT服务器，串口输出connected
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");//同时ESP8266开发板向MQTT服务器PUBLISH一个主题为outTopic内容为hello world的消息
      // ... and resubscribe
      client.subscribe("inTopic");//同时ESP8266开发板从MQTT服务器SUBSCRIBE一个主题inTopic
    } else {
      Serial.print("童卓 2022030233 罗子丹 2022020584 failed, rc=");//如果ESP8266开发板还是没有连上了MQTT服务器，串口输出failed, rc=
      Serial.print(client.state());//串口输出错误代码
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


//Arduino初始化命令，写在setup函数中的命令只执行1次
void setup() {
  pinMode(EchoPin, INPUT);      //设置EchoPin为输入模式
  pinMode(TrigPin, OUTPUT);     //设置超声波数字IO脚模式，OUTPUT为输出
  pinMode(led_button,OUTPUT);//指示灯引脚
  pinMode(0, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);//初始化串口波特率为115200
  //以下依次调用连接WiFi、设置MQTT服务器、回调（接收并处理来自MQTT服务器的消息）、连接MQTT服务器等函数
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  reconnect();
  //如果没有成功订阅主题为led内容为0的消息，串口输出订阅失败;尝试重新订阅！，并在0.3秒后重新订阅
 //以下为接受函数名字的名称定义
 //订阅开发板2的指示灯，接受信息
  while(!client.subscribe("1led",0))
  {Serial.println("童卓 2022030233 罗子丹 2022020584 订阅失败;尝试重新订阅！");
   client.subscribe("1led",0);
   delay(300);
  }
  //如果成功订阅主题led，串口输出订阅成功~~~
  Serial.println("童卓 2022030233 罗子丹 2022020584 订阅成功~~~");
 //订阅开发板2的亮度传感器数值信息,接受信息
  while(!client.subscribe("ledgan",0))
  {Serial.println("童卓 2022030233 罗子丹 2022020584 订阅失败;尝试重新订阅！");
   client.subscribe("ledgan",0);
   delay(300);
  }
  //如果成功订阅主题led，串口输出订阅成功~~~
  Serial.println("童卓 2022030233 罗子丹 2022020584 订阅成功~~~");
}

//Arduino循环执行命令，写在loop函数中的命令循环执行
void loop() {
  //如果ESP8266开发板没有连接上MQTT服务器，重新建立连接 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

//  //如果读取的KEY值不等于key_flag，串口输出：开关状态改变；Publish message: door:读取的KEY值
//  if(digitalRead(KEY)!=key_flag)
//    {
//    Serial.println("童卓 2022030233 罗子丹 2022020584 开关状态改变");
//    Serial.print("Publish message: door:");
//    Serial.println(digitalRead(KEY));
//    //准备将msg作为消息体PUBLISH，msg必须是字符串格式
//    //下面将读取的KEY值（digitalRead(KEY)）按照整型值（%d）的格式格式化为字符串并将其拷贝到msg中，字符串长度10
//    snprintf (msg, 10, "%d", digitalRead(KEY));
//    client.publish("door", msg);//ESP8266开发板PUBLISH一个主题为door内容为msg的消息
//    }
//    key_flag = digitalRead(KEY);

//以下为开发板自己发布信息函数
  long now = millis();//读取当前时间
  if (now - lastMsg > 5000) {
    lastMsg = now;
    //读取超声波传感器
  digitalWrite(TrigPin, LOW);     
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW); 
  int distance = pulseIn(EchoPin, HIGH);   
  distance= distance/58;
  //向MQTT传输distance的值
    snprintf (msg, 50, "%d", distance);//如果已经过了2秒，更新lastMsg，value值加1。准备将value值发布到MQTT服务器，像上面的KEY值一样处理成字符串
    Serial.print("童卓 2022030233 罗子丹 2022020584 distance: ");
    Serial.println(msg);
    client.publish("distance", msg);//ESP8266开发板PUBLISH一个主题为distance内容为msg的消息
  }
if(ledgan>150)
{
digitalWrite(14, LOW);
}
if(ledgan<=150&&ledgan>1)
digitalWrite(14, HIGH);
}
