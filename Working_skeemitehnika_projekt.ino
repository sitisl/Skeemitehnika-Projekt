#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <LcdBarGraphRobojax.h>

#define READ_PIN A0
#define MAX_ANALOG_READ 700
#define MAX_LED_VAL 750
#define GRAPH_LENGTH 8
                        //16x2 ekraan
                        //Ühel real 2 filtrit
                        //16/2 = 8 veergu ühe filtri jaoks

byte lcdNumCols = 16;

LiquidCrystal_I2C lcd(0x27,20,2);  // LCD aadress 0x27, 0x20 = 16 veergu, 2 rida 

LcdBarGraphRobojax filterLP(&lcd, GRAPH_LENGTH, 0, 0);      //Low-pass.            Up/left

LcdBarGraphRobojax filterBP_L(&lcd, GRAPH_LENGTH, 8, 0);    //Band-pass low freq.  Up/right

LcdBarGraphRobojax filterBP_H(&lcd, GRAPH_LENGTH, 0, 1);    //Band-pass high freq. Down/right

LcdBarGraphRobojax filterHP(&lcd, GRAPH_LENGTH, 8, 1);      //High-pass            Down/left
void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.init();
  lcd.clear();
  delay(50);
  
  lcd.backlight();
  lcd.print("");
  delay(100);
  lcd.clear();
}

int inputSafe(int a, int b, int c, int d){
  if(a >= MAX_ANALOG_READ || b >= MAX_ANALOG_READ || c >= MAX_ANALOG_READ || d >= MAX_ANALOG_READ){
    digitalWrite(LED_BUILTIN, HIGH);
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Lower volume");
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    lcd.clear();
    return 0;
  }
  return 1;
}

void loop(){
  
  int LP = analogRead(A2);
  int BP_L = analogRead(A3);
  int HP = analogRead(A1);
  int BP_H = analogRead(A0);
  
  if(inputSafe(LP, BP_L, HP, BP_H)){
    filterLP.drawValue(LP, MAX_LED_VAL);
    filterHP.drawValue(HP,MAX_LED_VAL);
    filterBP_L.drawValue(BP_L,MAX_LED_VAL);
    filterBP_H.drawValue(BP_H,MAX_LED_VAL);
   }
}
