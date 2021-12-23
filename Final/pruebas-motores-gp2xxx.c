#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <limits.h>

#include "motores.h"
#include "sensores-spi.h"

#define BOOL int

#define GP2XXX_1_THR 0
#define GP2XXX_2_THR 1

#define READ_DELAY 50

float gp2xxx_1_value;
float gp2xxx_2_value;


PI_THREAD (gp2xxx_1_loop)
{
 for(;;)
 {
  piLock(GP2XXX_1_THR);
  gp2xxx_1_value = getVoltage(GP2XXX_1_CH);
  piUnlock(GP2XXX_1_THR);
  delay(READ_DELAY);
 }
}

PI_THREAD (gp2xxx_2_loop)
{
 for(;;)
 {
  piLock(GP2XXX_2_THR);
  gp2xxx_2_value = getVoltage(GP2XXX_2_CH);
  piUnlock(GP2XXX_2_THR);
  delay(READ_DELAY);
 }
}


void setup(void) {
  wiringPiSetup();
  mcp3004Setup(SPI_PIN_BASE, SPI_CHANNEL);
  softPwmCreate(SERVO1, 0, RANGE);
  softPwmCreate(SERVO2, 0, RANGE);
}

// return: distancia en centímetros
void getDistanceAsString(char* str, float voltage) {
 int dist = gp2xxx_volt_to_dist(voltage);
 if(dist == -1)
  str = "???";
 else
  sprintf(str, "%d", dist);
}

// main thread
int main (int argc, char** argv)
{
  setup();

  piThreadCreate(gp2xxx_1_loop);
  piThreadCreate(gp2xxx_2_loop);
  piThreadCreate(show_channels_data);
  printf("\n");
  adelante();

  for (;;)
  {
    int dist1, dist2;
    piLock(GP2XXX_1_THR);
    dist1 = gp2xxx_volt_to_dist(gp2xxx_1_value);
    piUnlock(GP2XXX_1_THR);

    piLock(GP2XXX_2_THR);
    dist2 = gp2xxx_volt_to_dist(gp2xxx_2_value);
    piUnlock(GP2XXX_2_THR);

    if ((dist1 >= 0 && dist1 < 20) || (dist2 >= 0 && dist2 < 20))
      break;

    delay(10*READ_DELAY);
  }
  parar();
  return 0;
}
