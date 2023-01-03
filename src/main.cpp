#include "main.h"

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  _mgr.Loop();
}

void setup() {
  // put your setup code here, to run once:

  _mgr = Manager();
  _mgr.Setup();
 
}