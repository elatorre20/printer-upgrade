#include "../../inc/MarlinConfig.h"

#include "../gcode.h"
#include "../queue.h"
#include "../parser.h"


/**
 * M5001: Go to leveling points
 * 
 * M5001 P0 home and move off board for probe attachment
 * M5001 P<1-5> probe points 1-5
 * M5001 Z<f>   set probing height, default 7.1 (removed)
 */
char *cmd0 = (char*)"G28 X Y\nG28 Z\nG90\nG0 Z20";
char *cmd1 = (char*)"G91\nG0 Z10\nG90\nG0 X60 Y60\nG0 Z7.15";
char *cmd2 = (char*)"G91\nG0 Z10\nG90\nG0 X260 Y60\nG0 Z7.15";
char *cmd3 = (char*)"G91\nG0 Z10\nG90\nG0 X260 Y260\nG0 Z7.15";
char *cmd4 = (char*)"G91\nG0 Z10\nG90\nG0 X60 Y260\nG0 Z7.15";
char *cmd5 = (char*)"G91\nG0 Z10\nG90\nG0 X160 Y160\nG0 Z7.15";
// char cmd_height[16] = "G90\nG0 Z7.1";

void GcodeSuite::M5001() {

  // if(parser.seenval('Z')){ //set probing height as passed in
  //   float height = parser.floatval('Z');
  //   SERIAL_ECHO("Probing height = ");
  //   SERIAL_ECHO_F(height, 2);
  //   memset(cmd_height, 0, 16);
  //   snprintf(cmd_height, 15, "G90\nG0 Z%f", height);
  // }

  switch(parser.intval('P')){
    case 0 :
      process_subcommands_now(cmd0);
      SERIAL_ECHOLN("Ready for probe attachment/removal");
      break;
    case 1 :
      process_subcommands_now(cmd1);
      // process_subcommands_now(cmd_height);
      SERIAL_ECHOLN("Probing point -x, -y");
      break;
    case 2 :
      process_subcommands_now(cmd2);
      // process_subcommands_now(cmd_height);
      SERIAL_ECHOLN("Probing point +x, -y");
      break;
    case 3 :
      process_subcommands_now(cmd3);
      // process_subcommands_now(cmd_height);
      SERIAL_ECHOLN("Probing point +x, +y");
      break;
    case 4 :
      process_subcommands_now(cmd4);
      // process_subcommands_now(cmd_height);
      SERIAL_ECHOLN("Probing point -x, +y");
      break;
    case 5 :
      process_subcommands_now(cmd5);
      // process_subcommands_now(cmd_height);
      SERIAL_ECHOLN("Probing bed center");
      break;
    default : 
      break;
  }
  
}
