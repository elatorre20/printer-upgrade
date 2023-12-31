#ifndef _BABYSTEP_CONTROL_H_
#define _BABYSTEP_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Set current babystep value
void babystepSetValue(float value);

// Get current babystep value
float babystepGetValue(void);

// Reset babystep value to default value
float babystepResetValue(void);

// Update babystep value
float babystepUpdateValue(float unit);

#ifdef __cplusplus
}
#endif

#endif
