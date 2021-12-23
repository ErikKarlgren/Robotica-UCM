#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#include "motores.h"
#include "sensores-spi.h"

#define BOOL int

#define CNY70_1_THR 0
#define CNY70_2_THR 1

#define READ_DELAY 40

#define THRESHOLD	2.0f

float cny70_1_value;
float cny70_2_value;


PI_THREAD (cny70_1_loop)
{
 for(;;)
 {
  piLock(CNY70_1_THR);
  cny70_1_value = getVoltage(CNY70_2_CH);
  piUnlock(CNY70_1_THR);
  //delay(READ_DELAY);
 }
}

PI_THREAD (cny70_2_loop)
{
 for(;;)
 {
  piLock(CNY70_2_THR);
  cny70_2_value = getVoltage(CNY70_1_CH);
  piUnlock(CNY70_2_THR);
  //delay(READ_DELAY);
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
  //piThreadCreate(show_channels_data);

  for(;;)
  {
	// 1 is on the right, 2 on the left
	piLock(CNY70_1_THR);
	piLock(CNY70_2_THR);

	// both white
	if (cny70_1_value > THRESHOLD && cny70_2_value > THRESHOLD){
		adelante();
	}
	// left is white, right is black
	else if (cny70_1_value <= THRESHOLD && cny70_2_value > THRESHOLD){
		// turn right
		derAtras();
		//derParar();
		izdAdelante();
	}
	// left is black, right is white
	else if (cny70_1_value > THRESHOLD && cny70_2_value <= THRESHOLD) {
		// turn left
		izdAtras();
		//izdParar();
		derAdelante();
	}
	// both black
	else {
		printf(">>> Both sensors detect black!\n");
		//adelante();
		atras();
		piUnlock(CNY70_1_THR);
		piUnlock(CNY70_2_THR);
		delay(500);
	}

	piUnlock(CNY70_1_THR);
	piUnlock(CNY70_2_THR);

	delay(READ_DELAY);
  }

  return 0 ;
}
