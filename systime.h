/*
 * systime.h
 * https://blog.csdn.net/qq_42796406/article/details/108474066
 * XT1频率为32.768kHz，XT2频率为4MHz
 * ACLK为4MHz（XT2直接提供），SMCLK和MCLK都是40MHz（XT2 10倍频提供）
 *  Created on: 2021年7月21日
 *      Author: liujiaqi
 */

#ifndef SYSTEMTIME_H_
#define SYSTEMTIME_H_
#include <driverlib.h>

//*****************************************************************************
//
//Desired Timeout for XT1 initialization
//初始化 XT1 所需的超时时间
//
//*****************************************************************************
#define UCS_XT1_TIMEOUT 50000

//*****************************************************************************
//
//Desired Timeout for XT2 initialization
//初始化 XT2 所需的超时时间
//
//*****************************************************************************
#define UCS_XT2_TIMEOUT 50000

//*****************************************************************************
//
//XT1 Crystal Frequency being used
//XT1 晶振频率
//
//*****************************************************************************
#define UCS_XT1_CRYSTAL_FREQUENCY    32768

//*****************************************************************************
//
//XT2 Crystal Frequency being used
//XT2 晶振频率
//
//*****************************************************************************
#define UCS_XT2_CRYSTAL_FREQUENCY   4000000

//*****************************************************************************
//
//Target frequency for MCLK in kHz
//系统主时钟  MCLK 的目标频率 (kHz)
//
//*****************************************************************************
#define UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ   40000

//*****************************************************************************
//
//MCLK/FLLRef Ratio XT2 10倍频
//
//*****************************************************************************
#define UCS_MCLK_FLLREF_RATIO   10

//*****************************************************************************
//
//Variable to store current clock values
//用于存储当前时钟值的变量
//
//*****************************************************************************
uint32_t clockValue;

//*****************************************************************************
//
//Variable to store status of Oscillator fault flags
//存储振荡器故障标志状态的变量
//
//*****************************************************************************
uint16_t status;

//*****************************************************************************
//
//Variable to store returned STATUS_SUCCESS or STATUS_FAIL
//存储返回的 STATUS_SUCCESS 或 STATUS_FAIL 的变量
//
//*****************************************************************************
uint8_t returnValue = 0;
void ClockInit(void)
{
    //设置核心电压为3级
    PMM_setVCore(PMM_CORE_LEVEL_3);

    //初始化正在使用的 XT1 和 XT2 晶振频率
    UCS_setExternalClockSource(UCS_XT1_CRYSTAL_FREQUENCY,
                               UCS_XT2_CRYSTAL_FREQUENCY);

    //初始化 XT1。 如果初始化成功，则返回 STATUS_SUCCESS
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN4 + GPIO_PIN5);
    returnValue = UCS_turnOnLFXT1WithTimeout(UCS_XT1_DRIVE_0, UCS_XCAP_3, UCS_XT1_TIMEOUT);
    //启动 HF XT2 晶振 端口选择 XT2
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN2 + GPIO_PIN3);

    //初始化 XT2。 如果初始化成功，则返回 STATUS_SUCCESS
    returnValue = UCS_turnOnXT2WithTimeout(UCS_XT2_DRIVE_4MHZ_8MHZ, UCS_XT2_TIMEOUT);

    //设置 DCO FLL 参考 = REFO
    UCS_initClockSignal(UCS_FLLREF, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //设置比率和所需的 MCLK 频率并初始化 DCO
    UCS_initFLLSettle(UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ, UCS_MCLK_FLLREF_RATIO);

    //设置 ACLK = XT2CLK = 4MHz
    UCS_initClockSignal(UCS_ACLK, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //设置 SMCLK = DCOCLK = 40MHz
    UCS_initClockSignal(UCS_SMCLK, UCS_DCOCLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //设置 MCLK = DCOCLK = 40MHz
    UCS_initClockSignal(UCS_MCLK, UCS_DCOCLK_SELECT, UCS_CLOCK_DIVIDER_1);

}
#define CPU_F                               ((double)40000000)
#define delay_us(x)                       __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define delay(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))
#define delay_s(x)                      __delay_cycles((long)(CPU_F*(double)x))
#endif
