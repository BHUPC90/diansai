#include "HardwareSerial.h"

/**
 * @brief  串口1初始化
 * @param  baseAddress:串口模块，BaudRate: 波特率
 * @retval 无
 */
bool Serialint(uint16_t baseAddress, uint32_t BaudRate)
{

    if (baseAddress == USCI_A1_BASE)
    {
        //P4.4,5 = USCI_A1 TXD/RXD
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN5);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    }
    if (baseAddress == USCI_A0_BASE)
    {
        //P3.3,4 = USCI_A1 TXD/RXD
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN4);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN3);
    }

    USCI_A_UART_initParam param = { 0 };
    float BRTemp = (float) UCS_getACLK() / (float) BaudRate;
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_ACLK; //串口时钟ACLK，ACLK = XT2CLK = 4MHz，详见systime.h
    param.clockPrescalar = (uint16_t) BRTemp;    //UCBRx 位
    param.firstModReg = 0u;    //UCBRFx 位
    param.secondModReg = (uint16_t) ((BRTemp - (uint16_t) (BRTemp)) * 8.0); //UCBRSx 位
    param.parity = USCI_A_UART_NO_PARITY;    //奇偶校验
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;    //控制接收和发送移位寄存器的方向。
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;    //停止位，1位
    param.uartMode = USCI_A_UART_MODE;    //默认模式
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION; //表示低频采样波特率生成
    if (STATUS_FAIL == USCI_A_UART_init(baseAddress, &param))
    {
        //失败返回
        return false;
    }
    //使能 UART 模块
    USCI_A_UART_enable(baseAddress);
    //Enable Receive Interrupt
    USCI_A_UART_clearInterrupt(baseAddress, USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(baseAddress, USCI_A_UART_RECEIVE_INTERRUPT);
    return true;
}

/**
 * @brief  串口发送字符串
 * @param  baseAddress: 串口模块，*ptr: 字符串
 * @retval 无
 */
void send_buf(uint16_t baseAddress, unsigned char *ptr)    //Send string.
{
    while (*ptr != '\0')
    {
        USCI_A_UART_transmitData(baseAddress, *ptr);
        ptr++;
    }
}



