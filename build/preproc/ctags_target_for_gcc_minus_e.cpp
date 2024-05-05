# 1 "E:\\win_code_git\\task_for_arduino_5_1_\\task5_TreeProtect\\task5_TreeProtect.ino"
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
# 12 "E:\\win_code_git\\task_for_arduino_5_1_\\task5_TreeProtect\\task5_TreeProtect.ino"
/* -------------------------------------------------------------------------- */
/*                                   烟雾传感器部分                                  */
/* -------------------------------------------------------------------------- */

float sensorValue; // variable to store sensor value

/* -------------------------------- 土壤湿度传感器部分 ------------------------------- */

/* Change these values based on your calibration values */



const int LED1 = 13;
const int LED2 = 12;

// Sensor pins


/* ---------------------------------- 蜂鸣器部分 --------------------------------- */
const int buzzerPin = 3;
const int buzzerPinGND = 2;

int fre;
void setup()
{
    pinMode(buzzerPinGND, 0x1);
    pinMode(buzzerPin, 0x1);
    digitalWrite(buzzerPin, 0x0);
    digitalWrite(buzzerPinGND, 0x0);

    pinMode(7, 0x1);
    pinMode(LED1, 0x1);
    pinMode(LED2, 0x1);

    // Initially keep the sensor OFF
    digitalWrite(7, 0x0);
    digitalWrite(LED1, 0x0);
    digitalWrite(LED2, 0x0);

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
    if (moisture < 500 /* Define max value we consider soil 'wet'*/)
    {
        Serial.println("Status: Soil is too wet");
        digitalWrite(LED1, 0);
        digitalWrite(LED2, 1);
    }
    else if (moisture >= 500 /* Define max value we consider soil 'wet'*/ && moisture < 750 /* Define min value we consider soil 'dry'*/)
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
    sensorValue = analogRead(A2); // read analog input pin 0

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
    digitalWrite(7, 0x1); // Turn the sensor ON
    delay(10); // Allow power to settle
    int val = analogRead(A0); // Read the analog value form sensor
    digitalWrite(7, 0x0); // Turn the sensor OFF
    return val; // Return analog moisture value
}
