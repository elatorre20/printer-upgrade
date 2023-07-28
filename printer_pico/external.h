#ifndef _EXTERNAL_H_
#define _EXTERNAL_H_

#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <stdlib.h>
#include <stdint.h>

//functions
void sched_handle(uint16_t sched_time, uint8_t* sched_flags, uint8_t deb_print = 0);

void poll_temp(float* temp, DHT temp_sensor, uint8_t deb_print = 0);

void set_rgb(uint16_t* rgb, uint8_t lights_on, uint8_t deb_print = 0);

void set_fan(uint8_t deb_print = 0);

void set_led(uint8_t RG, uint8_t deb_print);

#endif