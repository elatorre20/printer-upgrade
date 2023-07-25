#ifndef CONSTANTS_H
#define CONSTANTS_H

//LED strip constants
#define R_PIN 17 //led strip pins
#define G_PIN 16
#define B_PIN 18
#define PWM_FREQ 1000 //pwm frequency


//front panel constants
#define BTN_PIN 20 //power button
#define LED0_PIN 21 //power button LED
#define LED1_PIN 2 //disk red LED
#define LED2_PIN 3 //disk green LED
#define POT_PIN A2 //potentiometer pin

//neopixel constants
#define NEO_0 10 //neopixel pins
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

//serial constants
#define RX 1
#define TX 0
#define BAUD 9600

#endif