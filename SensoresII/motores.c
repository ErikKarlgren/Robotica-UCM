#include "motores.h"

void adelante(void)
{
  printf("Adelante\n");
  softPwmWrite(SERVO1, S1_FWD);
  softPwmWrite(SERVO2, S2_FWD);
}
void atras(void)
{
    printf("Atras\n");
    softPwmWrite(SERVO1, S1_BWD);
    softPwmWrite(SERVO2, S2_BWD);
}
void parar(void)
{
    printf("Parar\n");
    softPwmWrite(SERVO1, STOP);
    softPwmWrite(SERVO2, STOP);
}


void izdAdelante(void) { softPwmWrite(SERVO1, S1_FWD); }
void izdAtras(void) { softPwmWrite(SERVO1, S1_BWD); }
void izdParar(void) { softPwmWrite(SERVO1, STOP); }

void derAdelante(void) { softPwmWrite(SERVO2, S2_FWD); }
void derAtras(void) { softPwmWrite(SERVO2, S2_BWD); }
void derParar(void) { softPwmWrite(SERVO2, STOP); }
