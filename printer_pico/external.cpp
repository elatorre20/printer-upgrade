#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <stdlib.h>
#include <stdint.h>
#include "constants.h"



void poll_temp(float* temp, DHT temp_sensor, uint8_t print = 0){//reads from temperature sensor
  temp[0] = temp_sensor.readTemperature();
  temp[1] = temp_sensor.readHumidity();
}

//RGB strip colors
uint8_t LED_colors[16][3] = {
  {255,255,255}, //white
  {255,40,40}, //red
  {40,255,40}, //green
  {40,40,255}, //blue
  {255,255,40}, //yellow
  {40,255,255}, //cyan
  {255,40,255}, //magenta
  {40,40,40}, //off
  {0,0,0}, //unused for now
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

void set_rgb(uint16_t* rgb, uint8_t lights_on){ //update LED color
    uint16_t pot_read = analogRead(POT_PIN); //read from pot
    rgb[0] = LED_colors[pot_read][0]; //set input channels appropriately
    rgb[1] = LED_colors[pot_read][1];
    rgb[2] = LED_colors[pot_read][2];

    if(lights_on){//LED strip controlled by front panel power button
      digitalWrite(LED0_PIN, HIGH);
      analogWrite(R_PIN, rgb[0]); //write value to PWM
      analogWrite(G_PIN, rgb[1]);
      analogWrite(B_PIN, rgb[2]);
    }
    else{//off if button off
      digitalWrite(LED0_PIN, LOW);
      digitalWrite(R_PIN, LOW);
      digitalWrite(G_PIN, LOW);
      digitalWrite(B_PIN, LOW);
    }
}