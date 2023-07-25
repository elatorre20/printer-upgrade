#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <stdlib.h>
#include <stdint.h>
#include "external.h"
#include "constants.h"


//neopixels
Adafruit_NeoPixel neo_0(LED_COUNT, NEO_0, NEO_WRGB + NEO_KHZ400);

//temp humidity sensor
DHT temp_sensor(TEMP_PIN, TEMP_TYPE);

//general variables
float amb[2]; //for temperature and humidity
float case_temp; //case temp from onboard thermometer
uint16_t rgb[3]; //for rgb duty cycles
volatile uint8_t on_button; //button interrupt flag
uint8_t lights_on; //whether RGB lights should be on
uint32_t debounce;

void setup() {
  //begin serial console
  Serial.begin();

  //setup UART to communicate with screen/mobo
  Serial1.setRX(RX);
  Serial1.setTX(TX);
  Serial1.begin(BAUD);

  //setup outputs
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(LED0_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  //setup inputs
  pinMode(POT_PIN, INPUT);
  pinMode(BTN_PIN, INPUT);
  
  //setup analog IO
  analogWriteFreq(PWM_FREQ);//set PWM freq
  analogReadResolution(3);

  //button interrupt handler
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_handler, FALLING);

  //setup neopixels
  neo_0.begin();
  neo_0.clear();
  neo_0.show();

  //setup temperature sensor
  temp_sensor.begin();


  while(1){ //main()

    if(on_button){//button debounce and handle
      on_button = 0;
      if(millis() > (debounce + 500)){
        lights_on = lights_on ^ 1;
        debounce = millis();
      }
    }

    //update LED color
    set_rgb(rgb, lights_on);

    //RGB debug block
    Serial.print("R: ");
    Serial.print(rgb[0]);
    Serial.print(" G: ");
    Serial.print(rgb[1]);
    Serial.print(" B: ");
    Serial.println(rgb[2]);

    //read temp and humidity
    poll_temp(amb, temp_sensor);

    //temp sensor debug block
    Serial.print("Humidity: ");
    Serial.print(amb[1]);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(amb[0]);
    Serial.println(" *C");
    delay(1000); //for debugging temperature sensor only

  }
}

void loop() {
  //unused
  return;
}


//interrupt/event related functions
void button_handler(){
  on_button = 1; //set button interrupt flag
}

// void serialEvent1() {//triggered when characters are available on serial 
//   while (Serial.available()) {
//     // get the new byte:
//     char inChar = (char)Serial.read();
//     // add it to the inputString:
//     inputString += inChar;
//     // if the incoming character is a newline, set a flag so the main loop can
//     // do something about it:
//     if (inChar == '\n') {
//       stringComplete = true;
//     }
//   }
// }

