#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <LcdBarGraphRobojax.h>

#define READ_PIN A0
#define GRAPH_LENGTH 8

byte lcdNumCols = 16;

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
LcdBarGraphRobojax filter1(&lcd, GRAPH_LENGTH, 0, 0);
LcdBarGraphRobojax filter2(&lcd, GRAPH_LENGTH, 0, 1);
LcdBarGraphRobojax filter3(&lcd, GRAPH_LENGTH, 8, 0);
LcdBarGraphRobojax filter4(&lcd, GRAPH_LENGTH, 8, 1);
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  delay(50);
  
  lcd.backlight();
  lcd.print("HALLO");
  delay(100);
  lcd.clear();
}






void loop()
{
  int reading = analogRead(A0);
  int reading2 = analogRead(A1);
  int reading3 = analogRead(A2);
  int reading4 = analogRead(A3);
  filter1.drawValue(reading, 750);
  filter2.drawValue(reading2,750);
  filter3.drawValue(reading3,750);
  filter4.drawValue(reading4,750);
}
