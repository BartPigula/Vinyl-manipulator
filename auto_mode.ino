#include <SoftwareSerial.h>
#include <Servo.h>
#include <SPI.h>
#include <SD.h>

//defining servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//file located on sd card
File file;
String fileName = "data2.txt";

//variables used for debouncing, both in milliseconds
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;

//position to set
int servo1Pos, servo2Pos, servo3Pos, servo4Pos;

//default positions of servos
const int neutral1 = 180;
const int neutral2 = 90;
const int neutral3 = 90;
const int neutral4 = 35;

//arm detector
const int detector=38;
int lastDetectorState=HIGH;
int detectorState=HIGH;
int reading;
int armCounter=0;

//dt set for delta angle = 1, [ms]
int dt = 100;
//dt set for time between positions
int posDelay = 100; //200

//to store command
char command[7];
//array with final positions, 70 steps maximum
int positions[250][4];
int lineAdded=0;


String readFile(String fileName) {
  String output = "";
  char letter;
  if (SD.begin(53)) {
    file = SD.open(fileName);
    if (file) {
      while (file.available()) {
        letter = char(file.read());
        output += letter;
      }
      Serial.println("Done");
    }
    else {
      Serial.println("No file found");
    }
    file.close();
  }
  else {
    Serial.println("No SD card connected");
  }
  return output;
}

void setPosition(int pos1,int pos2,int pos3,int pos4){
//adjusting servo1Pos
  if (pos1>=0 && pos1<=180){
    while(servo1Pos<pos1){
      servo1Pos++;
      servo1.write(servo1Pos);
      delay(dt);
    }

    while(servo1Pos>pos1){
      servo1Pos--;
      servo1.write(servo1Pos);
      delay(dt);
    }
  }
  else {
    Serial.println("Wrong pos1");
  }

//adjusting servo2Pos
  if (pos2>=0 && pos2<=180){
    while(servo2Pos<pos2){
      servo2Pos++;
      servo2.write(servo2Pos);
      delay(dt);
    }

    while(servo2Pos>pos2){
      servo2Pos--;
      servo2.write(servo2Pos);
      delay(dt);
    }
  }
  else {
    Serial.println("Wrong pos2");
  }

//adjusting servo3Pos
  if (pos3>=0 && pos3<=180){
    while(servo3Pos<pos3){
      servo3Pos++;
      servo3.write(servo3Pos);
      delay(dt);
    }

    while(servo3Pos>pos3){
      servo3Pos--;
      servo3.write(servo3Pos);
      delay(dt);
    }
  }
  else {
    Serial.println("Wrong pos3");
  }

//adjusting servo4Pos
  if (pos4>=0 && pos4<=180){
    while(servo4Pos<pos4){
      servo4Pos++;
      servo4.write(servo4Pos);
      delay(dt);
    }

    while(servo4Pos>pos4){
      servo4Pos--;
      servo4.write(servo4Pos);
      delay(dt);
    }
  }
  else {
    Serial.println("Wrong pos4");
  }
}

void resetPosition(){
  setPosition(neutral1,neutral2,neutral3,neutral4);
}


int getNumber(char tab[],int num){
  int occurCounter=0;
  int beg=0;
  int ending,iter;
  String tmp="";
  int out=0;
  for (iter=0;iter<15;iter++){
    if (tab[iter]>=48 && tab[iter]<=57){
      tmp+=tab[iter];
    }
    else if (tab[iter]==' '){
      out=tmp.toInt();
      tmp="";
      occurCounter++;
    }
    
    if (occurCounter==num){
      break;
    }
  }
  return out;
}


void setup() {
  //attaching servos
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(7);
  servo4.attach(6);

  //defining detector as input
  pinMode(detector,INPUT);

  //initial position, should be vertical, to change in future
  servo1Pos = neutral1;
  servo1.write(servo1Pos);
  servo2Pos = neutral2;
  servo2.write(servo2Pos);
  servo3Pos = neutral3;
  servo3.write(servo3Pos);
  servo4Pos = neutral4;
  servo4.write(servo4Pos);

  Serial.begin(9600);
  delay(3000);

  //getting data from SD card
  String data;
  data = readFile(fileName);
//  Serial.println(data);
  int fileSize = data.length();
//  Serial.print(fileSize);
  char dataSplit[fileSize];
  data.toCharArray(dataSplit, fileSize);
  //Serial.write(dataSplit,strlen(dataSplit));

  int lineCounter = 0;
  int tmp[4];
  char delim = '\n';
  char line[15];
  int begIdx=0;
  int endIdx;
  int i,j,k;
  j=0;
  lineAdded=0;

  for (i = 0; i < fileSize; i++) {
    if (data[i] == delim) {
      j=0;
      positions[lineAdded][0]=getNumber(line,1);
      positions[lineAdded][1]=getNumber(line,2);
      positions[lineAdded][2]=getNumber(line,3);
      positions[lineAdded][3]=getNumber(line,4);
      lineAdded++;
      for (k=0;k<15;k++){
//        if (line[k]>=32 && line[k]<=57){
//          Serial.print(line[k]);
//        }
        line[k]=' ';
      }
      endIdx=i;
//      Serial.println(line);
      begIdx=endIdx+1;
    }
    else {
      line[j]=data[i];
      j++;
    }
  }

  Serial.print(lineAdded);
  Serial.println(" lines");


//  for (i=0;i<lineAdded;i++){
//    for (j=0;j<4;j++){
//      Serial.print(positions[i][j]);
//      Serial.print(' ');
//    }
//    Serial.print('\n');
//  }
}


void loop() {
  reading=digitalRead(detector);
  //debouncing and checking positive edge
  if (reading != lastDetectorState) {
    lastDebounceTime=millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != detectorState) {
      detectorState=reading;
      if (detectorState == HIGH) {
        if (armCounter==0){  
          delay(8000);
          for (int i=0;i<lineAdded;i++){
            setPosition(positions[i][0],positions[i][1],positions[i][2],positions[i][3]);
            delay(posDelay);
          }
          armCounter++;
        }
        else {
          armCounter=0;
        }
      }
    }
  }
  lastDetectorState=reading;
}
