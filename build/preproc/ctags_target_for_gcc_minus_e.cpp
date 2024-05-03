# 1 "E:\\win_code_git\\task_for_arduino_5_1_\\test_for_UNO\\test_for_UNO.ino"
/*

 * @Author: xuyang

 * @Date: 2024-05-03 15:47:20

 * @LastEditors: xuyang

 * @LastEditTime: 2024-05-03 15:47:50

 * @FilePath: \task_for_arduino_5_1_\test_for_UNO\test_for_UNO.ino

 * @Description: 

 * 

 * Copyright (c) 2024 by xuyang, All Rights Reserved 

 */
# 11 "E:\\win_code_git\\task_for_arduino_5_1_\\test_for_UNO\\test_for_UNO.ino"
void setup() {
  pinMode(13, 0x1); // 将数字引脚13设置为输出模式
}

void loop() {
  digitalWrite(13, 0x1); // 将数字引脚13设置为高电平（点亮LED）
  delay(1000); // 等待1秒钟
  digitalWrite(13, 0x0); // 将数字引脚13设置为低电平（熄灭LED）
  delay(1000); // 等待1秒钟
}
