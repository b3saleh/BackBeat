int led0 = 6;
int led1 = 5;
int led2 = 4;
int led3 = 3;
int led4 = 2;

void setup(){
  Serial.begin(9600);
  Serial.println("System is Setting Up");
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
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
  if(A0maximum == 1023){
    Serial.println("Start/End Button Pressed");
    digitalWrite(led0, HIGH);
    delay(10);
    digitalWrite(led0, LOW);
  }
  if(A1maximum == 1023){
    Serial.println("Pad 1 Pressed");
    digitalWrite(led1, HIGH);
    delay(10);
    digitalWrite(led1, LOW);
  }
  if(A2maximum == 1023){
    Serial.println("Pad 2 Pressed");
    digitalWrite(led2, HIGH);
    delay(10);
    digitalWrite(led2, LOW);
  }
  if(A3maximum == 1023){
    Serial.println("Pad 3 Pressed");
    digitalWrite(led3, HIGH);
    delay(10);
    digitalWrite(led3, LOW);
  }
  if(A4maximum == 1023){
    Serial.println("Pad 4 Pressed");
    digitalWrite(led4, HIGH);
    delay(10);
    digitalWrite(led4, LOW);
  }
}
