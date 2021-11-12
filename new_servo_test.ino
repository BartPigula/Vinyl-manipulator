#include <SoftwareSerial.h>
#include <Servo.h>

//maximum speed of 360 servo 0.183333 seconds/60 degrees
//0.00306 second for 1 degree
//#define speed 0.00306
#define speed 0.183333

//defining servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//array to store command
char command[7];

//position to set
int servo1Pos, servo2Pos, servo3Pos, servo4Pos; 

//dt set for delta angle = 1, [ms]
int dt=100;

void setup() {
  //attaching servos
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);

  //initial position, should be vertical, to change in future
  servo1Pos = 90;
  servo1.write(90);
  servo2Pos = 90;
  servo2.write(servo2Pos);
  servo3Pos = 90;
  servo3.write(servo3Pos);
  servo4Pos = 90;
  servo4.write(servo4Pos);

  //connecting serial
  Serial.begin(9600);
  Serial.println("Type desired position as: servo's number_servo's angle");
  Serial.println("0_0 prints actual position");
}

void loop() { 
//In case of command steering instead of manual steering
if (Serial.available()){
  //read command and overwrite \n with null
  byte size=Serial.readBytes(command,7);
  command[size]=0;
  //find position of separator in typed command
  char* separator = strchr(command, '_');
  if (separator != 0){
    //replace _ with null
    *separator = 0;
    int servoID = atoi(command);
    ++separator;
    int angle = atoi(separator);
    //check whether command is correct
    if (servoID < 0 || servoID > 4) Serial.println("invalid servo ID");
    else {
      if (servoID==0) {
         Serial.print("Current position: ");
         Serial.print(servo1Pos);
         Serial.print("\t");
         Serial.print(servo2Pos);
         Serial.print("\t");
         Serial.print(servo3Pos);
         Serial.print("\t");
         Serial.print(servo4Pos);
         Serial.print("\n");
      }
      //in case of servo 1 0 is max speed clockwise, 180 is max speed counterclockwise
//      else if (servoID==1) {
//        if (angle<0) angle=0;
//        if (angle>360) angle=360;
//        if (servo1Pos < angle){
//          servo1.write(0);
//          delay(speed*angle*1000/60);
//          servo1.write(90);
//          servo1Pos=angle;
//        }
//        else if (servo1Pos > angle) {
//          servo1.write(180);
//          delay(speed*angle*1000/60);
//          servo1.write(90);
//          servo1Pos=angle;
//        }
//      }
      else if (servoID==1) {
        if (angle<0) angle=0;
        if (angle>180) angle=180;
        if (servo1Pos < angle){
          while (servo1Pos < angle){
            servo1Pos++;
            servo1.write(servo1Pos);
            delay(dt);
          }
        }
        else if (servo1Pos > angle) {
          while (servo1Pos > angle){
            servo1Pos--;
            servo1.write(servo1Pos);
            delay(dt);
          }
        }
      }
      else if (servoID==2) {
        if (angle<0) angle=0;
        if (angle>180) angle=180;
        if (servo2Pos < angle){
          while (servo2Pos < angle){
            servo2Pos++;
            servo2.write(servo2Pos);
            delay(dt);
          }
        }
        else if (servo2Pos > angle) {
          while (servo2Pos > angle){
            servo2Pos--;
            servo2.write(servo2Pos);
            delay(dt);
          }
        }
      }
      else if (servoID==3) {
        if (angle<0) angle=0;
        if (angle>180) angle=180;
        if (servo3Pos < angle){
          while (servo3Pos < angle){
            servo3Pos++;
            servo3.write(servo3Pos);
            delay(dt);
          }
        }
        else if (servo3Pos > angle) {
          while (servo3Pos > angle){
            servo3Pos--;
            servo3.write(servo3Pos);
            delay(dt);
          }
        } 
      }
      else if (servoID==4) {
        if (angle<0) angle=0;
        if (angle>180) angle=180;
        if (servo4Pos < angle){
          while (servo4Pos < angle){
            servo4Pos++;
            servo4.write(servo4Pos);
            delay(dt);
          }
        }
        else if (servo4Pos > angle) {
          while (servo4Pos > angle){
            servo4Pos--;
            servo4.write(servo4Pos);
            delay(dt);
          }
        }
      }
      else Serial.println("unexpected error");
    }
  }
 }
}
