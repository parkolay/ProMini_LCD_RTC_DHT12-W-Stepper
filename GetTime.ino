void GetTime()
{
  DateTime now = RTC.now();         //grab the date and time from RTC

  lcd.setCursor(0, 0);              // set the cursor (column, line)
  //    lcd.print(now.year(), DEC);
  //    lcd.print('/');
  //    lcd.print(now.month(), DEC);
  //    lcd.print('/');
  //    lcd.print(now.day(), DEC);
  //    lcd.print(' ');
 
  if (now.hour() <= 9)              //add a space if hour is less than or equal to 9
  {
    lcd.print(' ');
  }
  lcd.print(now.hour(), DEC);       //send hour to LCD
  //lcd.setCursor(2, 0);              // set the cursor (column, line)
  lcd.print(':');                   //send : to LCD
  //lcd.setCursor(3, 0);              // set the cursor (column, line)
  
  if (now.minute() <= 9)            //add a 0 if minute is less than or equal to 9
  {
    lcd.print('0');
  }
  lcd.print(now.minute(), DEC);     //send minute to LCD
  //lcd.setCursor(5, 0);              // set the cursor (column, line)
  lcd.print(':');                   //send : to LCD
  //lcd.setCursor(6, 0);              // set the cursor (column, line)
  if (now.second() <= 9)            //add a 0 if second is less than or equal to 9
  {
    lcd.print('0');
  }
  lcd.print(now.second(), DEC);     //send second to LCD
}//end void GetTime()

