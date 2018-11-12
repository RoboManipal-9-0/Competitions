#define MOTOR1_PWM 
#define MOTOR1_DIR
#define MOTOR2_PWM 
#define MOTOR2_DIR

#define LIMIT_1
#define LIMIT_2
#define LIMIT_3

#define LOCK_PIECE 0
#define UNLOCK_PIECE 1
#define MOUNT 2


void ActivateMotorTill(int action)
{
	if(action == LOCK_PIECE)
	{
		digitalWrite(MOTOR2_DIR, HIGH);
		while(!digitalRead(LIMIT_3))
			analogWrite(MOTOR2_PWM, 40);
		delay(300);
		analogWrite(MOTOR2_PWM, 0);
	}

	if(action == UNLOCK_PIECE)
	{
		digitalWrite(MOTOR2_DIR, LOW);
		analogWrite(MOTOR2_PWM, 40);
		delay(1000);
		analogWrite(MOTOR2_PWM, 0);
	}

	if(action == MOUNT)
	{
		ActivateMotorTill(LOCK_PIECE);
		digitalWrite(MOTOR1_DIR, HIGH);
		while(!digitalRead(LIMIT_2))
			analogWrite(MOTOR1_PWM, 40);
		delay(300);
		analogWrite(MOTOR2_PWM,0);
		ActivateMotorTill(UNLOCK_PIECE);	
		digitalWrite(MOTOR1_DIR, LOW);
		while(!digitalRead(LIMIT_1))
			analogWrite(MOTOR1_PWM, 40);
		delay(300);
		analogWrite(MOTOR2_PWM,0);
	}	
}

void setup()
{
	pinMode(LIMIT_1,INPUT);
	pinMode(LIMIT_2,INPUT);
	pinMode(LIMIT_3,INPUT);

	pinMode(MOTOR1_DIR,OUTPUT);
	pinMode(MOTOR1_PWM,OUTPUT);
	pinMode(MOTOR2_DIR,OUTPUT);
	pinMode(MOTOR2_PWM,OUTPUT);
}

void loop()
{
	
}