#ifndef __SENSORES_SPI
#define __SENSORES_SPI

#include <stdio.h>
#include <wiringPi.h>
#include <mcp3004.h>

#define V_REF		3.3
#define MAX_VALUE_MCP	1024.0

#define SPI_PIN_BASE	100
#define SPI_CHANNEL	  0

#define GP2XXX_1_CH	100
#define GP2XXX_2_CH	101
#define CNY70_1_CH	102
#define CNY70_2_CH	103

#define UNDEFINED_DIST	-1
#define UNDEFINED_VOLT	-1

int gp2xxx_volt_to_dist(float voltage);
float gp2xxx_dist_to_volt(int distance);
float getVoltage(int channel);
float getMediumVoltage(int channel);
PI_THREAD (show_channels_data);

#endif
