#include "../../inc/MarlinConfig.h"

#include "../gcode.h"
#include "../queue.h"
#include "../parser.h"


/**
 * M5001: Go to leveling points
 * 
 * M5001 P0 home and move off board for probe attachment
 * M5001 P<1-5> probe points 1-5
 */
char *cmd0 = (char*)"G28\nG90\nG0 Z20\n";
char *cmd1 = (char*)"G91\nG0 Z10\nG90\nG0 X60 Y60\nG0 Z7.1\n";
char *cmd2 = (char*)"G91\nG0 Z10\nG90\nG0 X260 Y60\nG0 Z7.1\n";
char *cmd3 = (char*)"G91\nG0 Z10\nG90\nG0 X260 Y260\nG0 Z7.1\n";
char *cmd4 = (char*)"G91\nG0 Z10\nG90\nG0 X60 Y260\nG0 Z7.1\n";
char *cmd5 = (char*)"G91\nG0 Z10\nG90\nG0 X160 Y160\nG0 Z7.1\n";

void GcodeSuite::M5001() {

  switch(parser.intval('P')){
    case 0 :
      process_subcommands_now(cmd0);
      SERIAL_ECHOLNPGM("Ready for probe attachment/removal");
      break;
    case 1 :
      process_subcommands_now(cmd1);
      SERIAL_ECHOLNPGM("Probing point -x, -y");
      break;
    case 2 :
      process_subcommands_now(cmd2);
      SERIAL_ECHOLNPGM("Probing point +x, -y");
      break;
    case 3 :
      process_subcommands_now(cmd3);
      SERIAL_ECHOLNPGM("Probing point +x, +y");
      break;
    case 4 :
      process_subcommands_now(cmd4);
      SERIAL_ECHOLNPGM("Probing point -x, +y");
      break;
    case 5 :
      process_subcommands_now(cmd5);
      SERIAL_ECHOLNPGM("Probing bed center");
      break;
    default : 
      break;
  }
  
}
