#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

uint8_t servonum = 4;
String msg;
int angle;
void setup() {
  Serial.begin(9600);
  pwm.begin(); 
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

// the code inside loop() has been updated by Robojax
void loop() {
  //Reading data from Serial
  while(Serial.available() > 0){
    msg = Serial.readString();
    if(msg.startsWith("s1")){
      msg.replace("s1,", "");
      angle = msg.toInt();
      pwm.setPWM(1, 0, angleToPulse(angle));
    } else if(msg.startsWith("s2")){
      msg.replace("s2,", "");
      angle = msg.toInt();
      pwm.setPWM(2, 0, angleToPulse(angle));
    }else if(msg.startsWith("s3")){
      msg.replace("s3,", "");
      angle = msg.toInt();
      pwm.setPWM(3, 0, angleToPulse(angle));
    }else if(msg.startsWith("s4")){
      msg.replace("s4,", "");
      angle = msg.toInt();
      pwm.setPWM(4, 0, angleToPulse(angle));
    } else{
      Serial.println("ERROR@!");
    }
  }
  
  delay(1000);
 
}


int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);       //Debug data
   Serial.print(" pulse: ");Serial.println(pulse);  //Debug data
   return pulse;
}
