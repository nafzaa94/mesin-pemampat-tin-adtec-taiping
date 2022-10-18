// library 
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

Servo myservo;

// sensor
int sensorTin = 2;
int irSensor1 = 3;
int irSensor2 = 4;

// value sensor
int valuesensorTin = 0;
int valueirsensor1 = 0;
int valueirsensor2 = 0;

// driver motor
int driverMotorIn = 5;
int driverMotorOut = 6;

// limit suis
int limitsuis = 7;

// value
int valuelimitsuis = 0;

int Var = 0;
int state = 0;
int count = 0;



void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(sensorTin, INPUT);
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(driverMotorIn, OUTPUT);
  pinMode(driverMotorOut, OUTPUT);
  pinMode(limitsuis, INPUT_PULLUP);
  myservo.attach(11);

  myservo.write(0);
  digitalWrite(driverMotorIn, LOW);
  digitalWrite(driverMotorOut, LOW);

}

void loop() {

   valuesensorTin = digitalRead(sensorTin); // 0 1 LOW HIGH
   valueirsensor1 = digitalRead(irSensor1); 
   valueirsensor2 = digitalRead(irSensor2);
   valuelimitsuis = digitalRead(limitsuis);

   if (valueirsensor2 == LOW && state == 0){
    count++;
    // antar sms
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+60xxxxxxxxxx\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("Tin Penuh......");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
     delay(1000);

    // stop sms
    if (count == 2){
      state == 1;
      }
    }
    else {
      state == 0;
      }
  
    switch (Var) {
    case 0:
      // sensor tin detect
      if (valuesensorTin == LOW){
        Var = 1;
        }
      break;
    case 1:
      // servo bukak
      myservo.write(90);
      delay(2000); // 2 sec
      myservo.write(0);
      Var = 2;
      break;  
    case 2:
      // ir sensor kesan tin
      if (valueirsensor1 == LOW){
        Var = 3;
        }
      break; 
    case 3:
      // motor jalan
      digitalWrite(driverMotorIn, HIGH);
      digitalWrite(driverMotorOut, LOW);

      if (valuelimitsuis == LOW){
        digitalWrite(driverMotorIn, LOW);
        digitalWrite(driverMotorOut, HIGH);
        Var = 0;
        }
      break; 
   }

}
