#include <SoftwareSerial.h>
#include <Servo.h>

//defining servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//buttons pins used to define desired position
const int s1Up=22;
const int s1Down=23;
const int s2Up=24;
const int s2Down=25;
const int s3Up=26;
const int s3Down=27;
const int s4Up=28;
const int s4Down=29;
const int savePos=30;
const int reset=31;

//array to store command
char command[7];

//position to set
int servo1Pos, servo2Pos, servo3Pos, servo4Pos; 

//variables used to detect rising edge
int s1UpState;
int s1DownState;
int s2UpState;
int s2DownState;
int s3UpState;
int s3DownState;
int s4UpState;
int s4DownState;
int resetState;
int saveState;

int lastS1UpState=LOW;
int lastS1DownState=LOW;
int lastS2UpState=LOW;
int lastS2DownState=LOW;
int lastS3UpState=LOW;
int lastS3DownState=LOW;
int lastS4UpState=LOW;
int lastS4DownState=LOW;
int lastResetState=LOW;
int lastSaveState=LOW;

//arrays to store saved positions
int servo1Set[50];
int servo2Set[50];
int servo3Set[50];
int servo4Set[50];
int setPointsCounter=0;

//variables used for debouncing, both in milliseconds
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;

//dt set for delta angle = 1, [ms]
int dt=100;

void setup() {
  //setting buttons
  pinMode(s1Up,INPUT);
  pinMode(s1Down,INPUT);
  pinMode(s2Up,INPUT);
  pinMode(s2Down,INPUT);
  pinMode(s3Up,INPUT);
  pinMode(s3Down,INPUT);
  pinMode(s4Up,INPUT);
  pinMode(s4Down,INPUT);
  pinMode(savePos,INPUT);
  pinMode(reset,INPUT);

  //attaching servos
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(7);
  servo4.attach(6);

  //initial position, should be vertical, to change in future
  servo1Pos = 180;
  servo1.write(servo1Pos);
  servo2Pos = 90;
  servo2.write(servo2Pos);
  servo3Pos = 90;
  servo3.write(servo3Pos);
  servo4Pos = 35;
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
			if (angle<0) angle=0;
			if (angle>180) angle=180;
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
      else if (servoID==1) {
        if (servo1Pos < angle){
          while (servo1Pos < angle){
            servo1Pos++;
            servo1.write(servo1Pos);
            delay(dt);
            printPosition();
          }
        }
        else if (servo1Pos > angle) {
          while (servo1Pos > angle){
            servo1Pos--;
            servo1.write(servo1Pos);
            delay(dt);
            printPosition();
          }
        }
      }
			else if (servoID==2) {
        if (servo2Pos < angle){
          while (servo2Pos < angle){
            servo2Pos++;
            servo2.write(servo2Pos);
            delay(dt);
            printPosition();
          }
        }
        else if (servo2Pos > angle) {
          while (servo2Pos > angle){
            servo2Pos--;
            servo2.write(servo2Pos);
            delay(dt);
            printPosition();
          }
        }
			}
			else if (servoID==3) {
        if (servo3Pos < angle){
          while (servo3Pos < angle){
            servo3Pos++;
            servo3.write(servo3Pos);
            delay(dt);
            printPosition();
          }
        }
        else if (servo3Pos > angle) {
          while (servo3Pos > angle){
            servo3Pos--;
            servo3.write(servo3Pos);
            delay(dt);
            printPosition();
          }
        } 
			}
			else if (servoID==4) {
        if (servo4Pos < angle){
          while (servo4Pos < angle){
            servo4Pos++;
            servo4.write(servo4Pos);
            delay(dt);
            printPosition();
          }
        }
        else if (servo4Pos > angle) {
          while (servo4Pos > angle){
            servo4Pos--;
            servo4.write(servo4Pos);
            delay(dt);
            printPosition();
          }
        }
			}
			else Serial.println("unexpected error");
		}
	}
 }

/////MANUAL STEER
//SERVO1
// increasing Servo's 1 angle
    int reading=digitalRead(s1Up);
    //debouncing and checking positive edge
    if (reading != lastS1UpState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != s1UpState) {
       s1UpState=reading;
       if (s1UpState == HIGH && servo1Pos < 180) {
      servo1Pos=servo1Pos+1;
      servo1.write(servo1Pos);
      delay(50);
       }
  }
    }
    lastS1UpState=reading;

// decreasing Servo's 1 angle
    reading=digitalRead(s1Down);
    //debouncing and checking positive edge
    if (reading != lastS1DownState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != s1DownState) {
       s1DownState=reading;
       if (s1DownState == HIGH && servo1Pos > 0) {
      servo1Pos=servo1Pos-1;
      servo1.write(servo1Pos);
      delay(50);
       }
  }
    }
    lastS1DownState=reading;


//SERVO2
// increasing Servo's 2 angle
    reading=digitalRead(s2Up);
    //debouncing and checking positive edge
    if (reading != lastS2UpState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != s2UpState) {
       s2UpState=reading;
       if (s2UpState == HIGH && servo2Pos < 180) {
      servo2Pos=servo2Pos+1;
      servo2.write(servo2Pos);
      delay(50);
       }
  }
    }
    lastS2UpState=reading;

// decreasing Servo's 2 angle
    reading=digitalRead(s2Down);
    //debouncing and checking positive edge
    if (reading != lastS2DownState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != s2DownState) {
       s2DownState=reading;
       if (s2DownState == HIGH && servo2Pos > 0) {
      servo2Pos=servo2Pos-1;
      servo2.write(servo2Pos);
      delay(50);
       }
  }
    }
    lastS2DownState=reading;


//SERVO3
// increasing Servo's 3 angle
    reading=digitalRead(s3Up);
    //debouncing and checking positive edge
    if (reading != lastS3UpState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != s3UpState) {
       s3UpState=reading;
       if (s3UpState == HIGH && servo3Pos < 180) {
      servo3Pos=servo3Pos+1;
      servo3.write(servo3Pos);
      delay(50);
       }
  }
    }
    lastS3UpState=reading;

// decreasing Servo's 3 angle
    reading=digitalRead(s3Down);
    //debouncing and checking positive edge
    if (reading != lastS3DownState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != s3DownState) {
       s3DownState=reading;
       if (s3DownState == HIGH && servo3Pos > 0) {
      servo3Pos=servo3Pos-1;
      servo3.write(servo3Pos);
      delay(50);
       }
  }
    }
    lastS3DownState=reading;


//SERVO4
// increasing Servo's 4 angle
    reading=digitalRead(s4Up);
    //debouncing and checking positive edge
    if (reading != lastS4UpState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != s4UpState) {
       s4UpState=reading;
       if (s4UpState == HIGH && servo4Pos < 180) {
      servo4Pos=servo4Pos+1;
      servo4.write(servo4Pos);
      delay(50);
       }
  }
    }
    lastS4UpState=reading;

// decreasing Servo's 4 angle
    reading=digitalRead(s4Down);
    //debouncing and checking positive edge
    if (reading != lastS4DownState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != s4DownState) {
       s4DownState=reading;
       if (s4DownState == HIGH && servo4Pos > 0) {
      servo4Pos=servo4Pos-1;
      servo4.write(servo4Pos);
      delay(50);
       }
  }
    }
    lastS4DownState=reading;

//RESET POSITION
    reading=digitalRead(reset);
    //debouncing and checking positive edge
    if (reading != lastResetState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != resetState) {
       resetState=reading;
       if (resetState == HIGH) {
      while (servo1Pos != 90) {
          if (servo1Pos < 90) {
          servo1Pos=servo1Pos+1;
          }
          else if (servo1Pos > 90) {
          servo1Pos=servo1Pos-1;
          }
      servo1.write(servo1Pos);
    delay(30);
    }

      while (servo2Pos != 130) {
          if (servo2Pos < 130) {
          servo2Pos=servo2Pos+1;
          }
          else if (servo2Pos > 130) {
          servo2Pos=servo2Pos-1;
          }
      servo2.write(servo2Pos);
    delay(30);
    }

      while (servo3Pos != 70) {
          if (servo3Pos < 70) {
          servo3Pos=servo3Pos+1;
          }
          else if (servo3Pos > 70) {
          servo3Pos=servo3Pos-1;
          }
      servo3.write(servo3Pos);
    delay(30);
    }

      while (servo4Pos != 90) {
          if (servo4Pos < 90) {
          servo4Pos=servo4Pos+1;
          }
          else if (servo4Pos > 90) {
          servo4Pos=servo4Pos-1;
          }
      servo4.write(servo4Pos);
    delay(30);
    }
       }
  }
    }
    lastResetState=reading;

//SAVING CURRENT POSITION
    reading=digitalRead(savePos);
    //debouncing and checking positive edge
    if (reading != lastSaveState) {
      lastDebounceTime=millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
  if (reading != saveState) {
       saveState=reading;
       if (saveState == HIGH) {
       servo1Set[setPointsCounter]=servo1Pos;
       servo2Set[setPointsCounter]=servo2Pos;
       servo3Set[setPointsCounter]=servo3Pos;
       servo4Set[setPointsCounter]=servo4Pos;
       setPointsCounter=setPointsCounter+1;
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
  }
    }
    lastSaveState=reading;
}

void printPosition(){
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
