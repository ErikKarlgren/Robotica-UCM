#include <stdio.h>
#include <wiringPi.h>
#include "sensores-spi.h"

#define READ_DELAY 50

void setup(void){
  wiringPiSetup();
  mcp3004Setup(SPI_PIN_BASE, SPI_CHANNEL);
}

// main thread
int main (int argc, char** argv)
{
  setup();
//  delay(2000);
//  printf("Measuring medium value of each sensor for 2.5 seconds\n");

  piThreadCreate(show_channels_data);

  for(;;);
/*
//  for (;;){
    float cny70_1=0, cny70_2=0, gp2xxx_1=0, gp2xxx_2=0;
    int i;

    for(i=0;i<50;i++){
      cny70_1 += getVoltage(CNY70_1_CH);
      cny70_2 += getVoltage(CNY70_2_CH);
      gp2xxx_1 += getVoltage(GP2XXX_1_CH);
      gp2xxx_2 += getVoltage(GP2XXX_2_CH);
      delay(50);
    }
    cny70_1 /= i;
    cny70_2 /= i;
    gp2xxx_1 /= i;
    gp2xxx_2 /= i;

    printf("cny70_1: %.2f\t cny70_2: %.2f\t gp2xxx_1: %.2f\t gp2xxx_2: %.2f\n",
	  cny70_1, cny70_2, gp2xxx_1, gp2xxx_2);
  //}
*/  return 0;
}
