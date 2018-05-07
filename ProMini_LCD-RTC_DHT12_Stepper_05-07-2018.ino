
/*
 * The RTC (DS1307) and DHT12 Circuit
 * Connected to I2C pins (A4, A5) power and GND
  * 
 *The LCD circuit:
 * LCD RS pin to digital pin 4
 * LCD Enable pin to digital pin 5
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 7
 * LCD D6 pin to digital pin 8
 * LCD D7 pin to digital pin 9
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * 
 * Stepper circuit 
 * PINs 10,11,12,13

Libraries;
 RTC:                 by Limor Fried (http://www.ladyada.net
 Stepper:             <SwitecX25.h>see https://guy.carpenter.id.au
 LCD Stolen from here  http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

#include <Wire.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <SwitecX25.h>

//initialize the DHT12 Temp/%RH sensor
const int DHT12 = 0x5C;     //datasheet says 0xB8 but I saw a write up that says they saw 0x5C when scanning the I2C bus
char DHT12Data[5];    //setup array for data read from DHT12
float DHT12_Humidity = 0;
float DHT12_Temp = 0;
float TempInF = 0;

// initialize the RTC library and setup calendar
RTC_DS1307 RTC;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
bool ClearScreen = 1;


//initialize the stepper motor
// standard X25.168 range 315 degrees at 1/3 degree steps
// For motors connected to pins 10,11,12,13
#define STEPS (315*3)
SwitecX25 motor1(STEPS,10,11,12,13);  


void setup()
{
  Serial.begin(57600);  //setup the serial port
  Wire.begin();         //setup I2C
  RTC.begin();          //setup RTC
  lcd.begin(16, 2);     // set up the LCD's number of columns and rows:
  GetClearScreen();     // clear screen on startup (and save function for later)

 // run the motor against the stops
 // start moving towards the center of the range
  motor1.zero();
  motor1.setPosition((STEPS/3)*2);

  if (! RTC.isrunning())  
  {
    //remember that this ONLY runs if the RTC is not set/ not running
    lcd.print("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); //-->with battery installed this should not be necessary
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  } //end if (! RTC.isrunning())
}//end void setup()

void loop()
{
  if (! RTC.isrunning())
  {
    lcd.setCursor(0,0);
    //lcd.print("!RTC has issues!");
   
    lcd.setCursor(0,1);
    GetDHT12Data();
  }//end if (! RTC.isrunning())

  else
  {
    GetTime();                         
    GetDHT12Data();
    UpdateStepper();

    delay(1000);                       //wait before for the next update
  }
}//end void loop()
