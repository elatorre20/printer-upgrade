#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <Wire.h>
#include <stdlib.h>
#include <stdint.h>
#include <RPi_Pico_TimerInterrupt.h>
#include "external.h"
#include "constants.h"

//debug logging settings, set to 1 to log on USB serial
#define DEBUG_SCHED 0 //set for scheduling algorithm debugging, really clogs the serial 
#define DEBUG_100 0 //set for debugging of functions in each of the scheduling classes
#define DEBUG_500 0
#define DEBUG_1000 0 


//neopixels
Adafruit_NeoPixel neo_0(LED_COUNT, NEO_0, NEO_WRGB + NEO_KHZ400);

//temp humidity sensor
DHT temp_sensor(TEMP_PIN, TEMP_TYPE);

//scheduling
RPI_PICO_Timer ITimer0(1);
volatile uint16_t timer_ms = 0; //used for scheduling
volatile uint8_t on_button, timer_period; //interrupt flags
uint8_t sched_flags[4]; //flags for the scheduling periods

//I2C communcation variables
char I2CString[23] = "\nAmbient temperature: ";
char I2CRecv[32];

//general variables
float amb[2]; //for temperature and humidity
uint16_t rgb[3]; //for rgb duty cycles
uint8_t lights_on[1]; //whether RGB lights should be on
uint8_t printing[1]; //for controlling front panel LEDS
uint8_t fan_state[1]; //for debouncing fan readings


void setup() {
  //begin serial console
  Serial.begin();

  //setup I2C target to communicate with screen/mobo
  Wire.setSDA(SDA);
  Wire.setSCL(SCL);
  Wire.begin(ADDR);
  Wire.onReceive(I2C_RXHandler);
  Wire.onRequest(I2C_TXHandler);

  //setup outputs
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(LED0_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(25, OUTPUT);
  //setup inputs
  pinMode(POT_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  
  //setup analog IO
  analogWriteFreq(PWM_FREQ);//set PWM freq
  analogReadResolution(10);

  //button interrupt handler
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_handler, RISING);

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
      set_rgb(rgb, lights_on[0], DEBUG_100);
      //handle I2C messages
      if(I2CRecv[0] != 0){
        Serial.println(I2CRecv);
        memset(I2CRecv,0,sizeof(I2CRecv));
      }
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
        if(DEBUG_500){
          Serial.println("button pressed");
        }
      }
    }
    if(sched_flags[3]){//1000ms scheduling
      sched_flags[3] = 0;
      if(DEBUG_1000){
        Serial.println("1000ms");
      }
      //read temp and humidity
      poll_temp(amb, temp_sensor, DEBUG_1000);
      //set case LED
      set_led(printing[0], DEBUG_1000);
      //set case fan
      set_fan(fan_state, DEBUG_1000);
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

void I2C_RXHandler(int numRecv){
  uint8_t count = 0;
  while(Wire.available()){
    I2CRecv[count] = Wire.read();
    count++;
  }
}

void I2C_TXHandler(void){
  Wire.write(I2CString, 23);
  int temp = (int)amb[0];
  Wire.write((char)temp);
}
