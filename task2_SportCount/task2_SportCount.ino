#include <LiquidCrystal.h>
#include <LCDKeypad.h>

LCDKeypad lcd;

int leftScore = 0;
int rightScore = 0;

void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("   00 : 00");
}

void loop()
{
    int buttonPressed = waitButton();

    if (buttonPressed == KEYPAD_UP && leftScore < 99)
    {
        leftScore++;
    }
    else if (buttonPressed == KEYPAD_DOWN && leftScore < 99)
    {
        leftScore--;
    }
    else if (buttonPressed == KEYPAD_LEFT && rightScore < 99)
    {
        rightScore++;
    }
    else if (buttonPressed == KEYPAD_RIGHT && rightScore < 99)
    {
        rightScore--;
    }

    updateDisplay();
}

void updateDisplay()
{
    lcd.setCursor(3, 0);
    if (leftScore < 10)
    {
        lcd.print("0");
    }
    lcd.print(leftScore);
    lcd.print(" : ");

    if (rightScore < 10)
    {
        lcd.print("0");
    }
    lcd.print(rightScore);
}

int waitButton()
{
    int buttonPressed;
    waitReleaseButton();
    lcd.blink();
    while ((buttonPressed = lcd.button()) == KEYPAD_NONE)
    {
    }
    delay(50);
    lcd.noBlink();
    return buttonPressed;
}

void waitReleaseButton()
{
    delay(50);
    while (lcd.button() != KEYPAD_NONE)
    {
    }
    delay(50);
}
