/*
 * Usart.h
 * Created on: 2021Äê7ÔÂ21ÈÕ
 * Author: liujiaqi
 */

#ifndef HARDWARESERIAL_H_
#define HARDWARESERIAL_H_
#include <msp430.h>
#include <stdio.h>
#include "driverlib.h"
#define  uart1  USCI_A1_BASE
#define  uart0  USCI_A0_BASE
bool Serialint(uint16_t baseAddress, uint32_t BaudRate);
void send_buf(uint16_t baseAddress, unsigned char *ptr);
#endif

