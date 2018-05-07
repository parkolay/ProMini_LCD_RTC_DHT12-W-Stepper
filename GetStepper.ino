
void UpdateStepper()
{
    int nextPos = (TempInF *10);
  // the motor only moves when you call update
  
  motor1.setPosition(nextPos);
  motor1.updateBlocking(); 
  
}//end UpdateStepper()
