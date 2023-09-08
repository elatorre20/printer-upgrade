#include "../../inc/MarlinConfig.h"

#include "../gcode.h"
#include "../queue.h"
#include "../parser.h"
#include "../../feature/twibus.h"

#define BOARD_ADDR 0x63
/**
 * M5002: I2C communcation with case board
 * 
 * M5002 L toggle lights
 * M5002 F<0-2> set case fan mode, 0:off 1:on 2:auto
 * M5002 T report ambient temperature and humidity
 */

void GcodeSuite::M5002() {

    i2c.address(BOARD_ADDR);

    switch(parser.intval('F')){
        case 0 :
            i2c.addbytes({'F',(char)0}, 2);
            i2c.send();
            SERIAL_ECHOLNPGM("Fan off");
            break;
        case 1 :
            i2c.addbytes({'F',(char)0}, 2);
            i2c.send();
            SERIAL_ECHOLNPGM("Fan on");
            break;
        case 2 :
            i2c.addbytes({'F',(char)0}, 2);
            i2c.send();
            SERIAL_ECHOLNPGM("Fan set to auto");
            break;
        default : 
            break;
    }
  
}
