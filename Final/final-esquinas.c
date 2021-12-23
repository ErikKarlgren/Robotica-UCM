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

#define GO_BACK_DELAY		700
#define TURN_DELAY		1200
#define MIN_DISTANCE		20
#define CRITICAL_DISTANCE	10

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

void readDistance1(int * dist){
    piLock(GP2XXX_1_THR);
    (*dist) = gp2xxx_volt_to_dist(gp2xxx_1_value);
    piUnlock(GP2XXX_1_THR);
}

void readDistance2(int * dist){
    piLock(GP2XXX_2_THR);
    (*dist) = gp2xxx_volt_to_dist(gp2xxx_2_value);
    piUnlock(GP2XXX_2_THR);
}

// mide la distancia n veces y retorna la media
void getMediumDistances(int *dist1, int *dist2){
	const int n=5;
	int i, aux1=0, aux2=0;

	for(i=0; i < n; i++){
		int d;
		readDistance1(&d);
		aux1 += d;
		readDistance2(&d);
		aux2 += d;
		delay(READ_DELAY);
	}
	(*dist1) = aux1 / n;
	(*dist2) = aux2 / n;
}

// turn right 90 degrees
void turnRight(){
  int dist1, dist2;
  derAtras();
  izdAdelante();

  do {
	getMediumDistances(&dist1, &dist2);
  } while ((dist1 < MIN_DISTANCE || dist2 < MIN_DISTANCE) || dist1 < CRITICAL_DISTANCE || dist2 < CRITICAL_DISTANCE);

  parar();
}

void turnLeft(){
  int dist1, dist2;
  izdAtras();
  derAdelante();

  do {
	getMediumDistances(&dist1, &dist2);
  } while ((dist1 < MIN_DISTANCE || dist2 < MIN_DISTANCE) || dist1 < CRITICAL_DISTANCE || dist2 < CRITICAL_DISTANCE);


  parar();
}


// main thread
int main (int argc, char** argv)
{
  setup();

  piThreadCreate(gp2xxx_1_loop);
  piThreadCreate(gp2xxx_2_loop);
  printf("\n");
  adelante();

  for (;;)
  {
    int dist1, dist2;
    getMediumDistances(&dist1, &dist2);

    if(dist1 < CRITICAL_DISTANCE){
	atras();
	delay(GO_BACK_DELAY);
	turnLeft();
	adelante();
    }
    else if (dist2 < CRITICAL_DISTANCE){
	atras();
	delay(GO_BACK_DELAY);
	turnRight();
	adelante();
    }

    // obstaculo proximo
    else if ((dist1 >= 0 && dist1 < MIN_DISTANCE) || (dist2 >= 0 && dist2 < MIN_DISTANCE))
    {
	if (dist1 < dist2)
		turnLeft();
		//turnRight();
	else
		//turnLeft();
		turnRight();
	adelante();
    }
  }
  parar();
  return 0;
}
