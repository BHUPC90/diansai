#ifndef CAR_H_
#define CAR_H_
#include "driverlib.h"
#include "pwm.h"
#include <stdio.h>

void goFront(uint16_t speed);
void goBack(uint16_t speed);
void goLeft(uint16_t speed);
void goRight(uint16_t speed);
void goStop();

#endif
