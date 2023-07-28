#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <stdlib.h>
#include <stdint.h>
#include <RPi_Pico_TimerInterrupt.h>
#include "external.h"
#include "constants.h"

//debug logging settings, set to 1 to log on USB serial
#define DEBUG_SCHED 1 //set for scheduling algorithm debugging, really clogs the serial 
#define DEBUG_100 1 //set for debugging of functions in each of the scheduling classes
#define DEBUG_500 1
#define DEBUG_1000 1 


//neopixels
Adafruit_NeoPixel neo_0(LED_COUNT, NEO_0, NEO_WRGB + NEO_KHZ400);

//temp humidity sensor
DHT temp_sensor(TEMP_PIN, TEMP_TYPE);

//scheduling timer
RPI_PICO_Timer ITimer0(1);

//general variables
float amb[2]; //for temperature and humidity
uint16_t rgb[3]; //for rgb duty cycles
volatile uint8_t on_button, timer_period; //interrupt flags
uint8_t lights_on; //whether RGB lights should be on
uint32_t debounce;
volatile uint16_t timer_ms = 0; //used for scheduling
uint8_t sched_flags[4]; //flags for the scheduling periods

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
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  //setup inputs
  pinMode(POT_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  
  //setup analog IO
  analogWriteFreq(PWM_FREQ);//set PWM freq
  analogReadResolution(10);

  //button interrupt handler
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_handler, FALLING);

  //setup neopixels
  neo_0.begin();
  neo_0.clear();
  neo_0.show();

  //setup temperature sensor
  temp_sensor.begin();

  //begin scheduling timer
  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_US, TimerHandler0);

  while(1){ //main()

    //update scheduling
    if(timer_period){//to ensure that tasks are not repeated if they finish in less than 1ms
      sched_handle(timer_ms, sched_flags, DEBUG_SCHED);
      timer_period = 0;
    }
    if(sched_flags[0]){//10ms scheduling
      sched_flags[0] = 0;
    }
    if(sched_flags[1]){//100ms scheduling
      sched_flags[1] = 0;
      if(DEBUG_100){
        Serial.println("100ms");
      }
      //update RGB color
      set_rgb(rgb, lights_on, DEBUG_100);
    }
    if(sched_flags[2]){//500ms scheduling
      sched_flags[2] = 0;
      if(DEBUG_500){
        Serial.println("500ms");
      }
      //button debounce
      if(on_button){
        on_button = 0;
        lights_on = lights_on ^ 1;
      }
      //set case fan
      set_fan(DEBUG_500);
    }
    if(sched_flags[3]){//1000ms scheduling
      sched_flags[3] = 0;
      if(DEBUG_1000){
        Serial.println("1000ms");
      }
      //read temp and humidity
      poll_temp(amb, temp_sensor, DEBUG_1000); //have to work out some scheduling for this
    }
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

bool TimerHandler0(struct repeating_timer *t){ //timer interrupt handler
  (void) t;
  timer_period = 1;
  timer_ms++;
  if(timer_ms == 1001){
    timer_ms = 0;
  }
  return true;
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

