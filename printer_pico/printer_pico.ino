#include <Adafruit_NeoPixel.h>
#include <stdlib.h>
#include <stdint.h>

//LED strip constants
#define R_PIN 17 //led strip pins
#define G_PIN 16
#define B_PIN 18


//front panel constants
#define BTN_PIN 14 //power button
#define LED0_PIN 19 //power button LED
#define LED1_PIN 5 //disk LED
#define POT_PIN A2 //potentiometer pin

//neopixel constants
#define NEO_0 19 //neopixel pins
#define LED_COUNT 8 //8 LEDS per group
#define BRIGHT_WHITE 0xFFFFFFFF //colors, 1 byte each GRBW
#define GREEN 0xFF000000
#define RED 0x00FF0000
#define BLUE 0x0000FF00
#define WHITE 0x000000FF 
#define CYAN 0xFF00FF00
#define MAGENTA 0x00FFFF00
#define YELLOW 0xFFFF0000

//general constants
#define PWM_FREQ 1000 //pwm frequency

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

//neopixels
Adafruit_NeoPixel neo_0(LED_COUNT, NEO_0, NEO_WRGB + NEO_KHZ800);

//general variables
uint16_t red, green, blue; //for rgb duty cycles
uint16_t pot_read; //color pot read
volatile uint8_t on_button; //button interrupt flag
uint8_t lights_on;
uint32_t debounce;
uint8_t f_led0, f_led1; //status of front case button and case LEDS


void setup() {
  //begin serial console
  Serial.begin();

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
  neo_0.fill(YELLOW);
  neo_0.show();


  while(1){ //main()

    //update LED color
    pot_read = analogRead(POT_PIN); //read from pot
    red = LED_colors[pot_read][0]; //set input channels appropriately
    green = LED_colors[pot_read][1];
    blue = LED_colors[pot_read][2];

    if(on_button){//button debounce and handle
      on_button = 0;
      if(millis() > (debounce + 500)){
        lights_on = lights_on ^ 1;
        debounce = millis();
      }
    }

    if(lights_on){//LED strip controlled by front panel power button
      digitalWrite(LED0_PIN, HIGH);
      analogWrite(R_PIN, red); //write value to PWM
      analogWrite(G_PIN, green);
      analogWrite(B_PIN, blue);
    }
    else{//off if button off
      digitalWrite(LED0_PIN, LOW);
      digitalWrite(R_PIN, LOW);
      digitalWrite(G_PIN, LOW);
      digitalWrite(B_PIN, LOW);
    }

  }
}

void loop() {
  //unused
  return;
}

void button_handler(){
  on_button = 1; //set button interrupt flag
}
