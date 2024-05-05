#include <Arduino.h>
#line 1 "E:\\win_code_git\\task_for_arduino_5_1_\\task5_TreeProtect\\task5_TreeProtect.ino"
/*
 * @Author: xuyang
 * @Date: 2024-05-04 20:30:46
 * @LastEditors: xuyang
 * @LastEditTime: 2024-05-05 14:22:12
 * @FilePath: \task_for_arduino_5_1_\task5_TreeProtect\task5_TreeProtect.ino
 * @Description:
 *
 * Copyright (c) 2024 by xuyang, All Rights Reserved
 */

/* -------------------------------------------------------------------------- */
/*                                   烟雾传感器部分                                  */
/* -------------------------------------------------------------------------- */
#define MQ2pin A2
float sensorValue; // variable to store sensor value

/* -------------------------------- 土壤湿度传感器部分 ------------------------------- */

/* Change these values based on your calibration values */
#define soilWet 500 // Define max value we consider soil 'wet'
#define soilDry 750 // Define min value we consider soil 'dry'

const int LED1 = 13;
const int LED2 = 12;

// Sensor pins
#define sensorPower 7
#define sensorPin A0
/* ---------------------------------- 蜂鸣器部分 --------------------------------- */
const int buzzerPin = 3;
const int buzzerPinGND = 2;

int fre;
#line 35 "E:\\win_code_git\\task_for_arduino_5_1_\\task5_TreeProtect\\task5_TreeProtect.ino"
void setup();
#line 57 "E:\\win_code_git\\task_for_arduino_5_1_\\task5_TreeProtect\\task5_TreeProtect.ino"
void loop();
#line 108 "E:\\win_code_git\\task_for_arduino_5_1_\\task5_TreeProtect\\task5_TreeProtect.ino"
int readSensor();
#line 35 "E:\\win_code_git\\task_for_arduino_5_1_\\task5_TreeProtect\\task5_TreeProtect.ino"
void setup()
{
    pinMode(buzzerPinGND, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(buzzerPinGND, LOW);

    pinMode(sensorPower, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    // Initially keep the sensor OFF
    digitalWrite(sensorPower, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);

    Serial.begin(115200);

    Serial.println("Gas sensor warming up!");
    // delay(20000); // allow the MQ-6 to warm up
}

void loop()
{
    /* --------------------------------- 土壤湿度传感器 -------------------------------- */
    // get the reading from the function below and print it
    int moisture = readSensor();
    Serial.print("Analog Output: ");
    Serial.println(moisture);
    // Determine status of our soil
    if (moisture < soilWet)
    {
        Serial.println("Status: Soil is too wet");
        digitalWrite(LED1, 0);
        digitalWrite(LED2, 1);
    }
    else if (moisture >= soilWet && moisture < soilDry)
    {
        Serial.println("Status: Soil moisture is perfect");
        digitalWrite(LED1, 1);
        digitalWrite(LED2, 0);
    }
    else
    {
        Serial.println("Status: Soil is too dry - time to water!");
        digitalWrite(LED1, 1);
        digitalWrite(LED2, 1);
    }
    /* ---------------------------------- 烟雾传感器 --------------------------------- */
    sensorValue = analogRead(MQ2pin); // read analog input pin 0

    Serial.print("Sensor Value: ");
    Serial.print(sensorValue);

    if (sensorValue > 300)
    {
        Serial.print(" | Smoke detected!");
        // 频率从200到800
        for (int i = 200; i <= 800; i++)
        {
            tone(7, i);
            delay(5);
        }
    }

    Serial.println("");
    delay(2000); // wait 2s for next reading
                 /* ---------------------------------- 延长时间 ---------------------------------- */
    delay(1000); // Take a reading every second for testing
                 // Normally you should take reading perhaps once or twice a day
    Serial.println();
}
//  This function returns the analog soil moisture measurement
int readSensor()
{
    digitalWrite(sensorPower, HIGH); // Turn the sensor ON
    delay(10);                       // Allow power to settle
    int val = analogRead(sensorPin); // Read the analog value form sensor
    digitalWrite(sensorPower, LOW);  // Turn the sensor OFF
    return val;                      // Return analog moisture value
}
