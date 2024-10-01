/*
  LiquidCrystal Library - Blink

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and makes the
 cursor block blink.

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

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalBlink

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.print("wait ...");
}

void loop() {
    if (Serial.available() > 0) {
      lcd.clear();
      char check = '1';
      check = Serial.read();

      char string[50];
      if (check == '0') {
        for (int i = 0; i < 16; i++)
        {
          delay(2);
          string[i] = Serial.read();
          if(int(string[i]) == -1) {
            string[i] = ' ';
          }

          Serial.print(char(string[i]));
        }
        string[16] = 0;
        lcd.setCursor(0, 0);
        lcd.print(string);

      } else {
        delay(2);
        char f = Serial.read();
        delay(2);
        char s = Serial.read();
        delay(2);

        int size = (int(f - '0')) * 10 + int(s - '0');
        for (int i = 0; i < size; i++)
        {
          delay(2);
          string[i] = Serial.read();
          if(int(string[i]) == -1) {
            string[i] = ' ';
          }

          Serial.print(char(string[i]));
        }

        string[size] = 0;
        lcd.setCursor(0, 0);
        lcd.print(string);

        // scroll 13 positions (string length) to the left
        // to move it offscreen left:
        for (int positionCounter = 0; positionCounter < size; positionCounter++) {
          // scroll one position left:
          lcd.scrollDisplayLeft();
          // wait a bit:
          delay(500);
        }

      // delay at the end of the full loop:
      delay(1000);
      }
  }
}


