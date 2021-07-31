/*
 * systime.h
 * https://blog.csdn.net/qq_42796406/article/details/108474066
 * XT1Ƶ��Ϊ32.768kHz��XT2Ƶ��Ϊ4MHz
 * ACLKΪ4MHz��XT2ֱ���ṩ����SMCLK��MCLK����40MHz��XT2 10��Ƶ�ṩ��
 *  Created on: 2021��7��21��
 *      Author: liujiaqi
 */

#ifndef SYSTEMTIME_H_
#define SYSTEMTIME_H_
#include <driverlib.h>

//*****************************************************************************
//
//Desired Timeout for XT1 initialization
//��ʼ�� XT1 ����ĳ�ʱʱ��
//
//*****************************************************************************
#define UCS_XT1_TIMEOUT 50000

//*****************************************************************************
//
//Desired Timeout for XT2 initialization
//��ʼ�� XT2 ����ĳ�ʱʱ��
//
//*****************************************************************************
#define UCS_XT2_TIMEOUT 50000

//*****************************************************************************
//
//XT1 Crystal Frequency being used
//XT1 ����Ƶ��
//
//*****************************************************************************
#define UCS_XT1_CRYSTAL_FREQUENCY    32768

//*****************************************************************************
//
//XT2 Crystal Frequency being used
//XT2 ����Ƶ��
//
//*****************************************************************************
#define UCS_XT2_CRYSTAL_FREQUENCY   4000000

//*****************************************************************************
//
//Target frequency for MCLK in kHz
//ϵͳ��ʱ��  MCLK ��Ŀ��Ƶ�� (kHz)
//
//*****************************************************************************
#define UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ   40000

//*****************************************************************************
//
//MCLK/FLLRef Ratio XT2 10��Ƶ
//
//*****************************************************************************
#define UCS_MCLK_FLLREF_RATIO   10

//*****************************************************************************
//
//Variable to store current clock values
//���ڴ洢��ǰʱ��ֵ�ı���
//
//*****************************************************************************
uint32_t clockValue;

//*****************************************************************************
//
//Variable to store status of Oscillator fault flags
//�洢�������ϱ�־״̬�ı���
//
//*****************************************************************************
uint16_t status;

//*****************************************************************************
//
//Variable to store returned STATUS_SUCCESS or STATUS_FAIL
//�洢���ص� STATUS_SUCCESS �� STATUS_FAIL �ı���
//
//*****************************************************************************
uint8_t returnValue = 0;
void ClockInit(void)
{
    //���ú��ĵ�ѹΪ3��
    PMM_setVCore(PMM_CORE_LEVEL_3);

    //��ʼ������ʹ�õ� XT1 �� XT2 ����Ƶ��
    UCS_setExternalClockSource(UCS_XT1_CRYSTAL_FREQUENCY,
                               UCS_XT2_CRYSTAL_FREQUENCY);

    //��ʼ�� XT1�� �����ʼ���ɹ����򷵻� STATUS_SUCCESS
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN4 + GPIO_PIN5);
    returnValue = UCS_turnOnLFXT1WithTimeout(UCS_XT1_DRIVE_0, UCS_XCAP_3, UCS_XT1_TIMEOUT);
    //���� HF XT2 ���� �˿�ѡ�� XT2
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN2 + GPIO_PIN3);

    //��ʼ�� XT2�� �����ʼ���ɹ����򷵻� STATUS_SUCCESS
    returnValue = UCS_turnOnXT2WithTimeout(UCS_XT2_DRIVE_4MHZ_8MHZ, UCS_XT2_TIMEOUT);

    //���� DCO FLL �ο� = REFO
    UCS_initClockSignal(UCS_FLLREF, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //���ñ��ʺ������ MCLK Ƶ�ʲ���ʼ�� DCO
    UCS_initFLLSettle(UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ, UCS_MCLK_FLLREF_RATIO);

    //���� ACLK = XT2CLK = 4MHz
    UCS_initClockSignal(UCS_ACLK, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //���� SMCLK = DCOCLK = 40MHz
    UCS_initClockSignal(UCS_SMCLK, UCS_DCOCLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //���� MCLK = DCOCLK = 40MHz
    UCS_initClockSignal(UCS_MCLK, UCS_DCOCLK_SELECT, UCS_CLOCK_DIVIDER_1);

}
#define CPU_F                               ((double)40000000)
#define delay_us(x)                       __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define delay(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define delay_s(x)                      __delay_cycles((long)(CPU_F*(double)x))
#endif
