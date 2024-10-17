/*
* The circuit:
* LCD RS pin to digital pin 12
* LCD Enable pin to digital pin 11
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)
*/

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Если checkScroll равен true, то LCD будет делать
// бегущую строку, это требуется для длинных сообщений
// Если checkScroll равен false, то LCD просто строку без сдвигов
bool checkScroll = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
    if (Serial.available() > 0) {
      lcd.clear();
      
      // Проверяем первый байт, если
      // 0 - строка на дисплее стоит на месте
      // 1 - строка на дисплее будет двигаться влево
      char firstByte = Serial.read();
      delay(2);

      if (firstByte == '0') {
        checkScroll = false;
        char string[16];

        for (int i = 0; i < 16; i++)
        {
          delay(2);
          string[i] = Serial.read();
          if(int(string[i]) == -1) {
            string[i] = 0;
          }

          Serial.print(char(string[i]));
        }
        string[16] = 0;
        lcd.setCursor(0, 0);
        lcd.print(string);
      } else {
        checkScroll = true;
        char string[30];

        for (int i = 0; i < 30; i++)
        {
          delay(2);
          string[i] = Serial.read();
          if(int(string[i]) == -1) {
            string[i] = 0;
          }

          Serial.print(char(string[i]));
        }

        string[30] = 0;
        lcd.setCursor(0, 0);
        lcd.print(string);
      }
      delay(1000);  
  } else if(checkScroll) {
    lcd.scrollDisplayLeft();
    delay(500);
  }
}