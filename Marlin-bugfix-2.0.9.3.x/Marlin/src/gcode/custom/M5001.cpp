#include "../../inc/MarlinConfig.h"


/**
 * M5001: Activate front panel LED by Gcode
 */


void GcodeSuite::M5001() {
  SERIAL_ECHOPGM(MSG_OK);
  SERIAL_ECHOLNPGM("M5001 called successfully!");
}

// void GcodeSuite::M42() {
//   const int pin_index = PARSED_PIN_INDEX('P', GET_PIN_MAP_INDEX(LED_PIN));
//   if (pin_index < 0) return;

//   const pin_t pin = GET_PIN_MAP_PIN(pin_index);

//   if (!parser.boolval('I') && pin_is_protected(pin)) return protected_pin_err();

//   bool avoidWrite = false;
//   if (parser.seenval('T')) {
//     switch (parser.value_byte()) {
//       case 0: pinMode(pin, INPUT); avoidWrite = true; break;
//       case 1: pinMode(pin, OUTPUT); break;
//       case 2: pinMode(pin, INPUT_PULLUP); avoidWrite = true; break;
//       #ifdef INPUT_PULLDOWN
//         case 3: pinMode(pin, INPUT_PULLDOWN); avoidWrite = true; break;
//       #endif
//       #ifdef INPUT_ANALOG
//         case 4: pinMode(pin, INPUT_ANALOG); avoidWrite = true; break;
//       #endif
//       #ifdef OUTPUT_OPEN_DRAIN
//         case 5: pinMode(pin, OUTPUT_OPEN_DRAIN); break;
//       #endif
//       default: SERIAL_ECHOLNPGM("Invalid Pin Mode"); return;
//     }
//   }

//   if (!parser.seenval('S')) return;
//   const byte pin_status = parser.value_byte();

//   #if HAS_FAN
//     switch (pin) {
//       #if HAS_FAN0
//         case FAN0_PIN: thermalManager.fan_speed[0] = pin_status; return;
//       #endif
//       #if HAS_FAN1
//         case FAN1_PIN: thermalManager.fan_speed[1] = pin_status; return;
//       #endif
//       #if HAS_FAN2
//         case FAN2_PIN: thermalManager.fan_speed[2] = pin_status; return;
//       #endif
//       #if HAS_FAN3
//         case FAN3_PIN: thermalManager.fan_speed[3] = pin_status; return;
//       #endif
//       #if HAS_FAN4
//         case FAN4_PIN: thermalManager.fan_speed[4] = pin_status; return;
//       #endif
//       #if HAS_FAN5
//         case FAN5_PIN: thermalManager.fan_speed[5] = pin_status; return;
//       #endif
//       #if HAS_FAN6
//         case FAN6_PIN: thermalManager.fan_speed[6] = pin_status; return;
//       #endif
//       #if HAS_FAN7
//         case FAN7_PIN: thermalManager.fan_speed[7] = pin_status; return;
//       #endif
//     }
//   #endif

//   if (avoidWrite) {
//     SERIAL_ECHOLNPGM("?Cannot write to INPUT");
//     return;
//   }

//   // An OUTPUT_OPEN_DRAIN should not be changed to normal OUTPUT (STM32)
//   // Use M42 Px M1/5 S0/1 to set the output type and then set value
//   #ifndef OUTPUT_OPEN_DRAIN
//     pinMode(pin, OUTPUT);
//   #endif
//   extDigitalWrite(pin, pin_status);

//   #ifdef ARDUINO_ARCH_STM32
//     // A simple I/O will be set to 0 by hal.set_pwm_duty()
//     if (pin_status <= 1 && !PWM_PIN(pin)) return;
//   #endif
//   hal.set_pwm_duty(pin, pin_status);
// }
