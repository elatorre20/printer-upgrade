#include "../../inc/MarlinConfig.h"

#include "../gcode.h"
#include "../queue.h"
#include "../parser.h"

/**
 * M5000: test custom commands
 */

void GcodeSuite::M5000() {
  SERIAL_ECHOLNPGM("M5000 called successfully!");
}

