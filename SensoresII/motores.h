#ifndef __MOTORES
#define __MOTORES

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <softPwm.h>

// #define	NUM_LEDS	  8

#define RANGE		100
#define SERVO1		  1 // gpio 18, servo de la izquierda
#define SERVO2		  4 // gpio 23, servo de la derecha

#define CW_SPEED	  1
#define CCW_SPEED	  40
#define STOP		  0

#define S1_FWD	 CCW_SPEED
#define S1_BWD	 CW_SPEED

#define S2_FWD	 CW_SPEED
#define S2_BWD	 CCW_SPEED

void adelante(void);
void atras(void);
void parar(void);

void izdAdelante(void);
void izdAtras(void);
void izdParar(void);

void derAdelante(void);
void derAtras(void);
void derParar(void);

#endif
