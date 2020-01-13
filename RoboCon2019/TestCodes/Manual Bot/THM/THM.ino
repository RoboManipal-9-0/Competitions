#define DIRECT_SOLENOID 0
#define SECONDARY_SOLENOID 1

#define FAST_UP 0
#define FAST_DOWN 1
#define SLOW_UP 2
#define SLOW_DOWN 3

#define DIRECT_SOLENOID_PIN 5
#define SECONDARY_SOLENOID_PIN 6


// Activating Individual Solenoid
void ActivateSolenoid(int solenoid, int value)
{
  if (solenoid == DIRECT_SOLENOID)
  {
    digitalWrite(DIRECT_SOLENOID_PIN, value);
    Serial.print("Right Solenoid: ");
    Serial.println(value);
  }

  else if (solenoid == SECONDARY_SOLENOID)
  {
    digitalWrite(SECONDARY_SOLENOID_PIN, value);
    Serial.print("Left Solenoid Activated");
    Serial.println(value);
  }
}

// Set Piston Position
void AdjustPiston(int cmd)
{
  if (cmd == FAST_UP)
  {
    ActivateSolenoid(SECONDARY_SOLENOID, HIGH);
    delay(100);
    ActivateSolenoid(DIRECT_SOLENOID, HIGH);
  }

  else if (cmd == FAST_DOWN)
  {
    ActivateSolenoid(DIRECT_SOLENOID, LOW);
    delay(50);
    ActivateSolenoid(SECONDARY_SOLENOID, LOW);
  }

  else if (cmd == SLOW_UP)
  {
    ActivateSolenoid(DIRECT_SOLENOID, HIGH);
    delay(200);
    ActivateSolenoid(SECONDARY_SOLENOID, HIGH);
  }

  else if (cmd == SLOW_DOWN)
  {
    ActivateSolenoid(DIRECT_SOLENOID, HIGH);
    delay(100);
    ActivateSolenoid(SECONDARY_SOLENOID, LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(SECONDARY_SOLENOID_PIN, OUTPUT);
  pinMode(DIRECT_SOLENOID_PIN, OUTPUT);
}

void loop()
{
  AdjustPiston(SLOW_UP);
  delay(4000);
  AdjustPiston(FAST_DOWN);
  delay(4000);
}
