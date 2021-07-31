#include <stdio.h>
#include <msp430.h> 
#include "driverlib.h"
#include "systime.h" //请在这里设置系统时钟
#include "HardwareSerial.h"
#include "car.h"
#include "pwm.h"

void setup()
{
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    //Serialint(uart1, 9600);
    //goFront(50);
}

void loop()
{
    int m = 0;
    for (m = 0; m <= 100; m++)
    {
        goFront(m);
        delay(50);
    }

    for (m = 100; m >= 0; m--)
    {
        goFront(m);
        delay(50);
    }
}

int main(void)
{
    WDT_A_hold(WDT_A_BASE); //关闭看门狗
    ClockInit();
    printf("SMCLK:%ldHz\r\n", UCS_getSMCLK());
    setup();
    for (;;)
        loop();
}

