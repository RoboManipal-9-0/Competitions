#include<DebuggerSerial.h>
#include<LSA08.h>

#define LSAMODE 's'

#define LSASerial Serial2

#define LEFT 0
#define FRONT 1
#define RIGHT 2

#define LSA_ACTIVE_STATE true

int LSA_pins[] = {22,24,26};
bool LSA_active_states[] = {LSA_ACTIVE_STATE, LSA_ACTIVE_STATE, LSA_ACTIVE_STATE};


// Class Objects -

LSA08 L[3];
DebuggerSerial debugger;

void setup()
{
  Serial.begin(9600);  // Setup the serial for the debugger
  debugger.Initialize("Default", &Serial);
  debugger.print("Starting Setup ", INFO);

  Serial2.begin(38400);
  //############### LSA #######################
  if (LSAMODE == 's')
  {
    for (int i = 0; i < 3; i++)
      L[i].Initialize('s', LSA_active_states[i], &LSASerial,  LSA_pins[i]);
  }
  else
  {
    for (int i = 0; i < 3; i++)
      L[i].Initialize('a', LSA_pins[i]);
  }
  debugger.print("Going into loop ....", INFO);
  debugger.print("\n", DEBUG);
  debugger.disableDebugger();
}

void loop()
{
  String msg = "LSA Values- LEFT: ";
  msg.concat(L[LEFT].ReadLSA(true));
  msg.concat("\t FRONT: ");
  msg.concat(L[FRONT].ReadLSA(true));
  msg.concat("\t RIGHT: ");
  msg.concat(L[RIGHT].ReadLSA(true));
  Serial.println(msg);
}
