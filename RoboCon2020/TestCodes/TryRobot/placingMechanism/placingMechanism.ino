void flushSerial(){
  while(Serial.available())
    Serial.read();  
}

bool DEBUGGERS_ON = false;

int pwmPin = 7;
int dirPin = 5;

int pwm = 0;
long t = 0;

void test(int pwm, int t){
  if(pwm<0)
    digitalWrite(DIR,LOW);
  else
    digitalWrite(DIR,HIGH);
  analogWrite(PWM,pwm);
  delay(t);
  analogWrite(PWM,0);  
} 

void setup() {
  Serial.begin(115200);
  pinMode(PWM,OUTPUT);
  pinMode(DIR,OUTPUT);
}

void loop() {
  if(Serial.available()){
    pwm = Serial.parseInt();
    t = Serial.parseInt();
    if(DEBUGGERS_ON)
      Serial.print("PWM: "); Serial.print(pwm); Serial.print(" Time: "); Serial.println(t);
    flushSerial();
    test(pwm,t);
  }
}
