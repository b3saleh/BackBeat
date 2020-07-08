#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

File root;

TMRpcm tmrpcm;

unsigned long TapTimes[30];
bool Pad1Tap[30];
bool Pad2Tap[30];
bool Pad3Tap[30];
bool Pad4Tap[30];
unsigned long StartTime = 0;
int counter;
int startedflag = 0;
unsigned long timeMeasurement = 0;
bool Pad0Flag = false;
bool Pad1Flag = false;
bool Pad2Flag = false;
bool Pad3Flag = false;
bool Pad4Flag = false;
bool ledON = false;
unsigned long testTime = 0;

void setup(){
  Serial.begin(9600);
  tmrpcm.speakerPin = 9; //Define Speaker Pin
  Serial.println("System is Setting Up");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  
  tmrpcm.volume(7);
}

void loop(){
  int A0reading;
  int A0maximum = 0;
  int A1reading;
  int A1maximum = 0;
  int A2reading;
  int A2maximum = 0;
  int A3reading;
  int A3maximum = 0;
  int A4reading;
  int A4maximum = 0;
  for(int i = 0; i < 50; i++){
    A0reading = analogRead(A0);
    A0maximum = max(A0maximum, A0reading);
    A1reading = analogRead(A1);
    A1maximum = max(A1maximum, A1reading);
    A2reading = analogRead(A2);
    A2maximum = max(A2maximum, A2reading);
    A3reading = analogRead(A3);
    A3maximum = max(A3maximum, A3reading);
    A4reading = analogRead(A4);
    A4maximum = max(A4maximum, A4reading);
  }
  if(A0maximum == 1023 && !Pad0Flag){
    Pad0Flag = true;
    if(startedflag){
      TapTimes[counter] = millis();
      Serial.println("End Button Pressed");
      while(1){
        for(int i = 0; i <= counter; i++){
//          Serial.print("i = ");
//          Serial.print(i);
//          Serial.print("| StartTime = ");
//          Serial.print(StartTime);
//          Serial.print("| TapTimes = ");
//          Serial.print(TapTimes[i]);
//          Serial.print("| Pad1Tap = ");
//          Serial.print(Pad1Tap[i]);
//          Serial.print("| Pad2Tap = ");
//          Serial.print(Pad2Tap[i]);
//          Serial.print("| Pad3Tap = ");
//          Serial.print(Pad3Tap[i]);
//          Serial.print("| Pad4Tap = ");
//          Serial.println(Pad4Tap[i]);
            
          if(i == 0){
            delay(TapTimes[i] - StartTime);
          }
          else{
            delay(TapTimes[i] - TapTimes[i-1] - 10);
          }
          if(Pad1Tap[i]) {
            Serial.println("Replaying Kick (1)");
            tmrpcm.play("/Samples/K.wav");
          }
          if(Pad2Tap[i]) {
            Serial.println("Replaying CHH (2)");
            tmrpcm.play("/Samples/CHH.wav");
          }
          if(Pad3Tap[i]) {
            Serial.println("Replaying Snare (3)");
            tmrpcm.play("/Samples/S.wav");
          }
          if(Pad4Tap[i]) {
            Serial.println("Replaying OHH (4)");
            tmrpcm.play("/Samples/OHH.wav");         
          }
        }
      }
    }
    else{
      Serial.println("Start Button Pressed");
      StartTime = millis();
      counter = 0;
      startedflag = 1;
    }
  }
  else if(A0maximum == 0){
    Pad0Flag = false;
  }
  timeMeasurement = millis();
  if(A1maximum == 1023 && !Pad1Flag){
    Serial.println("Pad 1 Pressed");
    TapTimes[counter] = timeMeasurement;
    Pad1Tap[counter] = true;
    tmrpcm.play("/Samples/K.wav");
    ledON = true;
    Pad1Flag = true;
  }
  else if(A1maximum == 0){
    Pad1Tap[counter] = false;
    Pad1Flag = false;
  }
  else{
    Pad1Tap[counter] = false;
  }
  if(A2maximum == 1023 && !Pad2Flag){
    Serial.println("Pad 2 Pressed");
    TapTimes[counter] = timeMeasurement;
    Pad2Tap[counter] = true;
    tmrpcm.play("/Samples/CHH.wav");
    ledON = true;
    Pad2Flag = true;
  }
  else if(A2maximum == 0){
    Pad2Tap[counter] = false;
    Pad2Flag = false;
  }
  else{
    Pad2Tap[counter] = false;
  }
  if(A3maximum == 1023 && !Pad3Flag){
    Serial.println("Pad 3 Pressed");
    TapTimes[counter] = timeMeasurement;
    Pad3Tap[counter] = true;
    tmrpcm.play("/Samples/S.wav");
    ledON = true;
    Pad3Flag = true;
  }
  else if(A3maximum == 0){
    Pad3Tap[counter] = false;
    Pad3Flag = false;
  }
  else{
    Pad3Tap[counter] = false;
  }
  if(A4maximum == 1023 && !Pad4Flag){
    Serial.println("Pad 4 Pressed");
    TapTimes[counter] = timeMeasurement;
    Pad4Tap[counter] = true;
    tmrpcm.play("/Samples/OHH.wav");
    ledON = true;
    Pad4Flag = true;
  }
  else if(A4maximum == 0){
    Pad4Tap[counter] = false;
    Pad4Flag = false;
  }
  else{
    Pad4Tap[counter] = false;
  }
  if(ledON){
    ledON = false;
    counter++;
  }
}
