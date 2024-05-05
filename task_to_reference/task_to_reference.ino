/*
 * @Author: xuyang
 * @Date: 2024-05-05 11:49:10
 * @LastEditors: xuyang
 * @LastEditTime: 2024-05-05 13:46:48
 * @FilePath: \task_for_arduino_5_1_\task_to_reference\task_to_reference.ino
 * @Description:
 *
 * Copyright (c) 2024 by xuyang, All Rights Reserved
 */

#define u8 uint8_t
/* ---------------------------------- 按键部分 ---------------------------------- */
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5
struct Key
{
    uint8_t key_sta;
    uint8_t judge_sta;
    uint8_t short_flag;
};

Key key[4] = {
    {!digitalRead(BUTTON1), 0, 0},
    {!digitalRead(BUTTON2), 0, 0},
    {!digitalRead(BUTTON3), 0, 0},
    {!digitalRead(BUTTON4), 0, 0}};

void key_scan()
{
    key[0].key_sta = !digitalRead(BUTTON1);
    key[1].key_sta = !digitalRead(BUTTON2);
    key[2].key_sta = !digitalRead(BUTTON3);
    key[3].key_sta = !digitalRead(BUTTON4);
    for (u8 i = 0; i < 4; i++)
    {
        switch (key[i].judge_sta)
        {
        case 0:
            if (key[i].key_sta == 0)
            {
                key[i].judge_sta = 1;
            }

            break;
        case 1:
            if (key[i].key_sta == 0)
                key[i].judge_sta = 2;
            else
                key[i].judge_sta = 0;
            break;
        case 2:
            if (key[i].key_sta == 1)
            {
                key[i].judge_sta = 0;
                key[i].short_flag = 1;
            }
            else
            {
                key[i].judge_sta = 0;
            }
        }
    }
}