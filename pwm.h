#ifndef PWM_H_
#define PWM_H_
#include "driverlib.h"
#include <stdio.h>

void PwmIntA(uint16_t baseAddress, uint16_t compareRegister,
             uint8_t selectedPort, uint16_t selectedPins, uint16_t timerPeriod,
             uint16_t dutyCycle);
#endif
