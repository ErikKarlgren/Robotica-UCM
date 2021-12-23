#include "motores.h"

int main ()
{
  wiringPiSetup();
  softPwmCreate(SERVO1, 0, RANGE);
  softPwmCreate(SERVO2, 0, RANGE);

  parar();
  delay(1000);
  printf("Start\n");

  for(;;)
  {
    adelante();
    delay(10000);

    parar();
    delay(2000);
    break;
  }
  return 0;
}
