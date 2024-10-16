/*
 The circuit:
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

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalBlink
*/

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

bool checkMove2 = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("wait ...");
}

void loop() {
    if (Serial.available() > 0) {
      lcd.clear();
      
      // Проверяем первый байт, если
      // 0 - строка на дисплее стоит на месте
      // 1 - строка на дисплее будет двигаться влево
      char checkMove = Serial.read();
      Serial.print(checkMove);
      Serial.print(' ');
      delay(2);

      if (checkMove == '0') {
        checkMove2 = false;
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
        checkMove2 = true;
        char string[30];
        
        // delay(2);
        // char f = Serial.read();
        // Serial.print(f);
        // delay(2);
        // char s = Serial.read();
        // Serial.print(s);
        // Serial.print(' ');
        // delay(2);

        // int size = (int(f - '0')) * 10 + int(s - '0');
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
/*
        // scroll 13 positions (string length) to the left
        // to move it offscreen left:
        for (int positionCounter = 0; positionCounter < size; positionCounter++) {
          // scroll one position left:
          lcd.scrollDisplayLeft();
          // wait a bit:
          delay(500);
        }*/

      // delay at the end of the full loop:
      }
      delay(1000);  
  } else if(checkMove2) {
  lcd.scrollDisplayLeft();
  delay(500);
}

  /*
если чек = 1 то сделать сдвиг
  */


}


