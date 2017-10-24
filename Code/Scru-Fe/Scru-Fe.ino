/*--------------------------------------------------
SCRU-FE by ZExtrude
www.ZExtrude.com for notes and tutorials on SCRU-FE
initial written by Ryan Theiss 2015
written for SCRU-FE on Thingiverse.com assembled with an Arduino UNO and Keyes_L298P motor shield

* Eisbaeeer 20171020
- added comments in german
- changed some subroutines

--------------------------------------------------*/


#include <Servo.h>

// Definition der Pins

// Motor Treiber L298N
  // motor one  
    int enA = 10;
    int in1 = 9;
    int in2 = 8;
  // motor two  
    int enB = 5;
    int in3 = 7;
    int in4 = 6;
    
// Servo
    #define servo A4  // Servo Pin
    #define Buzzer A5 // Piezo Signalgeber

    #define centerServoBtn 4 // Jumper für Servo Mittelstellung

// Ultraschallmodul HC-SR04
    #define trigPin 3 // Trigger Pin vom Ultraschallmodul
    #define echoPin A2 // Echo Pin vom Ultraschallmodul

    #define voltagePin A3 // Batterie Spannung

// Konstanten festlegen
    const uint8_t MIN_DIST = 30; // Mindestabstand zur Richtungsänderung
    const float MIN_VOLT = 4.7; // Untere Spannungsgrenze

    int distance;   // Variable für Abstand
    Servo myservo;
    
void setup() {
// serial
    Serial.begin(9600);   // mit 9600 Baud auf die serielle Schnittstelle ausgeben
    delay(20);            // 20 ms warten
// servo
    pinMode(servo, OUTPUT);   // Servo Pin auf output
    myservo.attach(servo);    // Library initialisieren

// Funktion der Pins des Arduino definieren 
  // Motorpins    
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
// Konfiguration Ultraschallmodul
    pinMode(trigPin, OUTPUT);             // Pin als Ausgang deklarieren
    pinMode(echoPin, INPUT);              // Pin als Eingang deklarieren
// Hier kann der Servo mittels Jumper Zentriert werden
    pinMode(centerServoBtn, INPUT);       // Pin als Eingang deklarieren
    digitalWrite(centerServoBtn, HIGH);   // Eingang mittels internem Pullup auf High setzen

// Routine für das zentrieren des Servos
  
    if (digitalRead(centerServoBtn) == LOW)   // Wenn der Pin "cernterServoBtn" LOW ist, wird der Servo auf die Mitte justiert
    {
      center(); // setzte Servo auf Mitte 
    }
    else
      headCenter();  // bewege Servo in die Mitte

    Serial.println(F("Hallo !!!"));
    Serial.println(F("Scru-Fe ist bereit..."));

    delay(500);      // 1 Sekunde warten
    redySound();      // Ton für Fertig ausgeben
    delay(1000);      // 2 Sekunden warten
    }

void loop()         // Hauptprogrammschleife
    {

    float batLevel = voltMes();     // Batteriespannung der Variablen batLevel zuordnen
    Serial.print(batLevel);         // Ausgabe der Spannung auf die serielle Schnittstelle
    Serial.println("V");            // Ausgabe von der Einheit "Volt" auf die Serielle Schnittstelle

    if (batLevel < MIN_VOLT)        // Wenn die Batteriespannung kleiner als "MIN_VOLT", dann ...
    {
      Serial.println(F("Low battery..."));  // Ausgabe von "Low battery..." auf die Serielle Schnittstelle
    //Coast
    motorStop();                    // Motor abschalten
    lowBatSound();                  // Warnton ausgeben
    }

    headCenter();                 //Drehe den Servo in die Mitte
    distance = distMes();         // Messe die Distanz mit dem Ultraschallmodul. Ergebnis in der Variablen in cm

// Reagiere auf die gemessene Entfernung
    if (distance >= MIN_DIST || distance <= 0)    // Wenn die Entfernung größer, gleich Mindestenfernung ist oder die Entfernung kleiner, gleich Null, dann...
    {
      Serial.println(F("motorForward"));
      motorForward();          // Motor vorwärts
    }
    else
    {
      Serial.println(F("motorHalt"));
      motorHalt();
      sound();                    // Ton ausgeben
      headRight();                // Servo nach rechts drehen
      distance = distMes();       // Messe die Distanz mit dem Ultraschallmodul. Ergebnis in der Variablen in cm

      if (distance >= MIN_DIST || distance <= 0) // Wenn die Entfernung größer, gleich Mindestenfernung ist oder die Entfernung kleiner, gleich Null, dann...
    {
      Serial.println(F("motorRight"));
      motorRight();             // Rechts drehen
      motorBack(300);           // Rückwärts fahren für Zeit in ms
    }

    else
    {
      headLeft();               // Servo nach links drehen
      motorLeft();              // Links drehen
      Serial.println(F("motorLeft"));
      motorBack(300);           // Rückwärts fahren für Zeit in ms 
    }
  }
}
