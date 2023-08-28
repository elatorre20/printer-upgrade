#ifndef CONSTANTS_H
#define CONSTANTS_H

//scheduling periods in MS
#define SCHED_0 10 
#define SCHED_1 100 
#define SCHED_2 500
#define SCHED_3 1000

//timer constants
// #define TIMER_INTERRUPT_DEBUG         1
// #define _TIMERINTERRUPT_LOGLEVEL_     4
#define TIMER0_INTERVAL_US    1000 //timer interval in microseconds, 1000=1ms

//LED strip constants
#define R_PIN 17 //led strip pins
#define G_PIN 16
#define B_PIN 18
#define PWM_FREQ 1000 //pwm frequency


//front panel constants
#define BTN_PIN 20 //power button
#define LED0_PIN 21 //power button LED
#define RED_PIN 14 //disk red LED
#define GREEN_PIN 15 //disk green LED
#define POT_PIN A2 //potentiometer pin

//neopixel constants
#define NEO_0 2 //neopixel pins
#define NEO_1 11
#define NEO_2 12
#define NEO_3 13
#define LED_COUNT 8 //8 LEDS per group
#define BRIGHT_WHITE 0xFFFFFFFF //colors, 1 byte each GRBW
#define GREEN 0xFF000000
#define RED 0x00FF0000
#define BLUE 0x0000FF00
#define WHITE 0x000000FF 
#define CYAN 0xFF00FF00
#define MAGENTA 0x00FFFF00
#define YELLOW 0xFFFF0000

//temp/humidity constants
#define TEMP_PIN 19
#define TEMP_TYPE DHT11
#define COOLING_TEMP 25 //temperature to turn on case fan
#define FAN_PIN 22
#define TEMP_VREF 3.2f //correction factor for package temperature

//I2C constants
#define SCL 1
#define SDA 0
#define ADDR 0x63 //target address


#endif