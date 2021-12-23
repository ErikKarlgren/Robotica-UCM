#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#include "motores.h"
#include "sensores-spi.h"

#define BOOL int

#define CNY70_1_THR 0
#define CNY70_2_THR 1

#define READ_DELAY 50

float cny70_1_value;
float cny70_2_value;


PI_THREAD (cny70_1_loop)
{
 for(;;)
 {
  piLock(CNY70_1_THR);
  cny70_1_value = getVoltage(CNY70_1_CH);
  piUnlock(CNY70_1_THR);
  delay(READ_DELAY);
 }
}

PI_THREAD (cny70_2_loop)
{
 for(;;)
 {
  piLock(CNY70_2_THR);
  cny70_2_value = getVoltage(CNY70_2_CH);
  piUnlock(CNY70_2_THR);
  delay(READ_DELAY);
 }
}


void setup(void){
  wiringPiSetup();
  mcp3004Setup(SPI_PIN_BASE, SPI_CHANNEL);
  softPwmCreate(SERVO1, 0, RANGE);
  softPwmCreate(SERVO2, 0, RANGE);
}

// main thread
int main (int argc, char** argv)
{
  setup();

  piThreadCreate(cny70_1_loop);
  piThreadCreate(cny70_2_loop);
  piThreadCreate(show_channels_data);

  for (;;)
  {
    piLock(CNY70_1_THR);
    if (cny70_1_value > 0.1)
      derParar();
    else
      derAdelante();
    piUnlock(CNY70_1_THR);

    piLock(CNY70_2_THR);
    if (cny70_2_value > 0.1)
      izdParar();
    else
      izdAdelante();
    piUnlock(CNY70_2_THR);

    delay(READ_DELAY);
  }
  return 0 ;
}
