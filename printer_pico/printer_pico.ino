#include <stdlib.h>
#include <stdint.h>

//LED strip constants
#define R_PIN 0 //led strip pins
#define G_PIN 1
#define B_PIN 2
#define R_MASK 14 //bit masks for accessing color portions of potentiometer reading
#define G_MASK 112
#define B_MASK 896
#define POT_PIN 31 //potentiometer pin

//front panel constants
#define BTN_PIN 3
#define LED0_PIN 4
#define LED1_PIN 5

//general constants
#define PWM_FREQ 1000 //pwm frequency

uint16_t red, green, blue; //for rgb duty cycles
uint16_t pot_read; //color pot read
volatile uint8_t on_button;
uint8_t f_led0, f_led1; //status of front case button and case LEDS


void setup() {
  //setup io modes
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(BTN_PIN, INPUT);
  pinMode(LED0_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);

  analogWriteFreq(PWM_FREQ);//set PWM freq


  while(1){ //main()

    //update LED color
    pot_read = analogRead(POT_PIN); //read from pot
    red = ((pot_read & R_MASK)>>12); //mask and shift value to high order bits
    green = ((pot_read & G_MASK)>>9);
    blue = ((pot_read & B_MASK)>>6);
    if(on_button){//LED strip controlled by front panel power button
      analogWrite(R_PIN, red); //write value to PWM
      analogWrite(G_PIN, green);
      analogWrite(B_PIN, blue);
    }
    else{//off if button off
      digitalwrite(R_PIN, LOW);
      digitalwrite(G_PIN, LOW);
      digitalwrite(B_PIN, LOW);
    }
    


  }
}

void loop() {
  //unused
  return;
}

void button_handler(){
  on_button = on_button ^ 1;
}