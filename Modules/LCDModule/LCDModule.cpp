
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDModule.h>
LiquidCrystal_I2C lcd(0x27,20,4);
void initialLcd(){
    lcd.init();
    lcd.backlight();
}

void lcdPrint(int x, int y, String z )
{
  if(x != 0 && y != 19)
  {
      lcd.setCursor(x-1,x);
      lcd.print(" ");
      lcd.setCursor(y,y+1);
      lcd.print(" ");
  }
  else if (x == 0 && y != 19)
  {
     lcd.setCursor(y,y+1);
     lcd.print(" ");
  }
  else if (y == 19 && x != 0)
  {
      lcd.setCursor(x-1,x);
      lcd.print(" ");
  }
  lcd.setCursor(x,y);
  lcd.print(z);
}

void offLcd(int GND)
{
    digitalWrite(GND,1);
}