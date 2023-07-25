#ifndef _EXTERNAL_H_
#define _EXTERNAL_H_

#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <stdlib.h>
#include <stdint.h>

//functions
void poll_temp(float* temp, DHT temp_sensor, uint8_t print = 0);

void set_rgb(uint16_t* rgb, uint8_t lights_on);


#endif