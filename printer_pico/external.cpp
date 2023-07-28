#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <stdlib.h>
#include <stdint.h>
#include "constants.h"


void sched_handle(uint16_t sched_ms, uint8_t* sched_flags, uint8_t deb_print = 0){
  if((sched_ms % SCHED_0) == 0){
    sched_flags[0] = 1; //flag period 1
    if(0){
      Serial.println("Period 0");
    }
  }
  if((sched_ms % SCHED_1) == 0){
    sched_flags[1] = 1; //flag period 1
    if(deb_print){
      Serial.println("Period 1");
    }
  }
  if((sched_ms % SCHED_2) == 0){
    sched_flags[2] = 1; //flag period 2
    if(deb_print){
      Serial.print("Period 2 ");
    }
  }
  if((sched_ms % SCHED_3) == 0){
    sched_flags[3] = 1; //flag period 3
    if(deb_print){
      Serial.println("Period 3");
    }
  }
}


void poll_temp(float* temp, DHT temp_sensor, uint8_t deb_print = 0){//reads from temperature sensor
  temp[0] = temp_sensor.readTemperature();
  temp[1] = temp_sensor.readHumidity();

  if(deb_print){
    Serial.print("Humidity: ");
    Serial.print(temp[1]);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp[0]);
    Serial.println(" *C");
  }
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

void set_rgb(uint16_t* rgb, uint8_t lights_on, uint8_t deb_print = 0){ //update LED color
  uint16_t pot_read = analogRead(POT_PIN); //read from pot
  pot_read = pot_read >> 7; //only need to select from 8 options
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

  if(deb_print){
    Serial.print("lights: ");
    Serial.print(lights_on);
    Serial.print(" R: ");
    Serial.print(rgb[0]);
    Serial.print(" G: ");
    Serial.print(rgb[1]);
    Serial.print(" B: ");
    Serial.println(rgb[2]);
  }
}

void set_fan(uint8_t deb_print = 0){
  uint8_t state = 0;
  float t = analogReadTemp();
  if(t > COOLING_TEMP){
    digitalWrite(FAN_PIN, HIGH);
    state = 1;
  }
  else{
    digitalWrite(FAN_PIN, LOW);
  }
  if(deb_print){
    Serial.print("board temp: ");
    Serial.print(t);
    Serial.print(" Fan: ");
    Serial.println(state);
  }
}