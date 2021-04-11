//****** FileHeader of: Main.cpp  Date: 09.04.2021  Author: Christian G ***** 
//**** Compiler: Platform IO with Ardurino Framework
//**** Controler: EPS32 Board: ESP32 Dev Kit C 
//**** Function: RGB Led PWM fading and Control with Serial Kommunikation ****
#include <Arduino.h>
#include<string>
//RGB Led Pins (GPIO):
#define Green_Led 18
#define Blue_Led 19
#define Red_Led 5
//PWM Settings:
#define freq 5000     //frequenzy
#define ledChannel_Green 0  //Use Timer 0 for green
#define ledChannel_Red 1  //Timer 1
#define ledchannel_Blue 2 //Timer 2
#define resolution 8  //8 Bit PWM 
//Serial Communications
#define Boudrate 9600
//For RGB Control:
bool ledStatus[3]; //Led State Array of RGB [R=0, G=1, B=2]

void setup() {
  //pinMode(Green_Led,OUTPUT);
  //pinMode(Red_Led,OUTPUT);
  //pinMode(Blue_Led,OUTPUT);

Serial.begin(9600);
//Rote LED:
ledcSetup(ledChannel_Red, freq, resolution);
ledcAttachPin(Red_Led, ledChannel_Red);
//Blaue LED:
ledcSetup(ledchannel_Blue, freq, resolution);
ledcAttachPin(Blue_Led, ledchannel_Blue);
//Green LED:
ledcSetup(ledChannel_Green, freq, resolution);
ledcAttachPin(Green_Led, ledChannel_Green);
}

bool DimLed(char Led,int val)
{
  if(Led=='K'||Led=='k')
  {
    ledcWrite(ledChannel_Red, 0);
    ledcWrite(ledChannel_Green, 0);
    ledcWrite(ledchannel_Blue, 0);
  }
  //Eingabe Fehler abfangen:
  if(val>255)
  {
      return false;
  }
   if(Led=='R'||Led=='r')
  {
    ledcWrite(ledChannel_Red, val);
    return true;
  }
  if(Led=='G'||Led=='g')
  {
    ledcWrite(ledChannel_Green, val);
    return true;
  }
  if(Led=='B'||Led=='b')
  {
    ledcWrite(ledchannel_Blue, val);
    return true;
  }
  else 
  {
    return false;
  }
}

void loop() 
{
    if(Serial.available())
  {
    //Serial.println("RGB Led ansteuern mit Led_Spezifier + Wert\nZwischen 0 bis 255 (Led_Spezifier= R Rot B Blau G Green)");
    Serial.print("\nIhre Eingabe: ");
    char Led_Spezi=Serial.read();
    int Led_Helligkeit= Serial.parseInt();
    Serial.print(Led_Spezi);
    Serial.print(Led_Helligkeit);
    Serial.print('\n');
    DimLed(Led_Spezi,Led_Helligkeit);
  }
}

