#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <stdlib.h>
#include <stdint.h>

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
Adafruit_NeoPixel neo_0(LED_COUNT, NEO_0, NEO_WRGB + NEO_KHZ400);

//temp humidity sensor
DHT temp_sensor(TEMP_PIN, TEMP_TYPE);

//general variables
float amb[2]; //for temperature and humidity
float case_temp; //case temp from onboard thermometer
uint16_t RGB[3]; //for rgb duty cycles
uint16_t pot_read; //color pot read
volatile uint8_t on_button; //button interrupt flag
uint8_t lights_on; //whether RGB lights should be on
uint32_t debounce;

void poll_temp(float* temp, uint8_t print = 0){//reads from temperature sensor
  temp[0] = temp_sensor.readTemperature();
  temp[1] = temp_sensor.readHumidity();
}

void set_rgb(uint16_t* rgb, )

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

    //read temp and humidity
    poll_temp(amb);

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

