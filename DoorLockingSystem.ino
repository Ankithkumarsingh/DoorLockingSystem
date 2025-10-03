#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

Servo servo1;
const byte row = 4;
const byte col = 4;
char hexakeys[row][col] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};

byte rowPins[row] = {13, 12, 11, 10};
byte colPins[col] = {9, 8, 7, 6};
Keypad custompad = Keypad(makeKeymap(hexakeys), rowPins, colPins, 4, 4);

const int RS = 5, E = A0, D4 = A1, D5 = A2, D6 = A3, D7 = A4;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

String password = "1234";
String input = "";

void setup()
{
  servo1.attach(A5);
  servo1.write(0); 
  lcd.begin(16, 2);
  lcd.print("ENTER PASS:");
}

void loop()
{
  char key = custompad.getKey();

  if (key) {
    if (key == '#') {   
      if (input == password) {
        lcd.setCursor(0, 1);
        lcd.print("Correct!      ");
        servo1.write(180);   
        delay(5000);
        servo1.write(0);     
      } else {
        lcd.setCursor(0, 1);
        lcd.print("Wrong!        ");
      }
      delay(2000);
      lcd.clear();
      lcd.print("ENTER PASS:");
      input = ""; 
    }
    else if (key == '*') {  
      input = "";
      lcd.setCursor(0, 1);
      lcd.print("                "); 
    }
    else {
      input += key; 
      lcd.setCursor(0, 1);
      lcd.print(input);  
    }
  }
}
