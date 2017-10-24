/*--------------------------------------------------
include file function
--------------------------------------------------*/
void headRight(void)
{ 
  myservo.write(80);      // Servo auf 80 Grad Drehwinkel setzen
  delay(500);             // 500ms warten
}

void headLeft(void)
{
  myservo.write(220);     // Servo auf 220 Grad Drehwinkel setzen
  delay(500);             // 500ms warten
}

void headCenter(void)     
{
  myservo.write(130);     // Servo auf 130 Grad Drehwinkel setzen
  delay(500);             // 500ms warten
}

void center(void)
{ 
  myservo.write(130);     // Setzt den Servo auf Mittelstellung
  delay(500);             // 500ms warten
  Serial.println(F("Hallo !!!"));
  Serial.println(F("Der Servo ist jetzt in Mittenstellung..."));
  for (;;);
}

void sound(void)
{
  //melodyjka - optional
  tone(Buzzer, 647);          //  E start of power up tone! 432HZ
  delay(150);
  tone(Buzzer, 770);          //  g
  delay(100);
  tone(Buzzer, 1295);          // High E
  delay(100);
  tone(Buzzer, 1027);          // c
  delay(100);
  tone(Buzzer, 1153);          // d
  delay(150);
  tone(Buzzer, 1539);          // High G
  delay(100);
  noTone(Buzzer);
}

void redySound(void)
{

  //sound
  tone(Buzzer, 1027); // c
  delay(200);
  tone(Buzzer, 647); // e
  delay(200);
  tone(Buzzer, 770); //  g
  delay(200);
  tone(Buzzer, 1027); // c
  delay(200);
  noTone(Buzzer);

}

void lowBatSound(void)
{
  for (;;)
  {
    //melodyjka - optional
    tone(Buzzer, 647);
    delay(150);
    tone(Buzzer, 1295);
    delay(100);
  }
}

int distMes(void)
{
  // Ping Utrasonic Sensor to find obstacles within distance in cm
  int duration;
  int distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

float voltMes(void)
{
  // read the input on analog
   int sensorValue = analogRead(voltagePin);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
   float voltage = sensorValue * (5.0 / 1023.0);
   voltage = voltage * 2; // voltage divaider 1 / 2
  // print out the value you read:
   return voltage;
}

void motorStop(void)
{
  //Motors Coast
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void motorForward()
{
  //Move Forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    analogWrite(enA, 255);
    analogWrite(enB, 210);
  }

void motorHalt()
{
    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
  
void motorBack(byte backlenght)
{
  //Move Backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 210);
  delay(backlenght);
  motorStop();
}

void motorLeft(void)

{
  //Motors Turn Left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 255);
  analogWrite(enB, 210);
  delay(500);
  motorStop();
}

void motorRight(void)

{
  //Motors Turn Right
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 210);
  delay(500);
  motorStop();
}
