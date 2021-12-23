#include <math.h>
#include "sensores-spi.h"

// Tiempo que se debería esperar entre cada lectura del sensor GP2XXX
#define GP2XXX_DELAY 32

// GP2XXX: array para pasar de una distancia en cm a un voltaje en voltios.
// Valores susceptibles a errores, aunque deberían ser pequeños.
#define MAX_DISTANCE 30
// Para evitar ambiguedades a la hora de pasar de voltaje a distancia
// (un voltaje bajo puede querer decir que un objeto está o muy cerca o
// bastante lejos) solo usaremos el tramo entre 3cm y 30cm por ser una
// función  monótomamente decreciente.
#define MIN_DISTANCE 3
const float gp2xxx_dist_to_volt_arr[MAX_DISTANCE] = { 0.00,
 2.50, 2.54, 3.01, 2.61, 2.16, 1.87, 1.65, 1.45, 1.28, 1.16,
 1.08, 0.99, 0.93, 0.86, 0.81, 0.76, 0.71, 0.66, 0.63, 0.60,
 0.57, 0.54, 0.51, 0.48, 0.47, 0.45, 0.43, 0.40, 0.39 };

int gp2xxx_volt_to_dist(float voltage) {
 return 11.4193 * pow(voltage, -1.05356);
}

float gp2xxx_dist_to_volt(int distance) {
 if(distance > MAX_DISTANCE || distance < 0)
   return UNDEFINED_VOLT;
 else
   return gp2xxx_dist_to_volt_arr[distance];
}

float getVoltage(int channel){
 int x = analogRead(channel);
 return (x / MAX_VALUE_MCP) * V_REF;
}

PI_THREAD (show_channels_data) {
 printf("\n");

 for(;;){
  float gp2_1 = getVoltage(GP2XXX_1_CH);
  float gp2_2 = getVoltage(GP2XXX_2_CH);
  float cny70_1 = getVoltage(CNY70_1_CH);
  float cny70_2 = getVoltage(CNY70_2_CH);

  // Para reescribir la última línea
  printf("\033[1A");
  printf("\033[K");
  printf("\rgp2xxx_1: %.2f\t gp2xxx_2: %.2f\t cny70_1: %.2f\t cny70_2: %.2f\t max value: %.2f\n",
   gp2_1, gp2_2, cny70_1, cny70_2, V_REF);
  delay(200);
 }
 return 0;
}

