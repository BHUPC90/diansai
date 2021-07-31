#include "HardwareSerial.h"

/**
 * @brief  ����1��ʼ��
 * @param  baseAddress:����ģ�飬BaudRate: ������
 * @retval ��
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
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_ACLK; //����ʱ��ACLK��ACLK = XT2CLK = 4MHz�����systime.h
    param.clockPrescalar = (uint16_t) BRTemp;    //UCBRx λ
    param.firstModReg = 0u;    //UCBRFx λ
    param.secondModReg = (uint16_t) ((BRTemp - (uint16_t) (BRTemp)) * 8.0); //UCBRSx λ
    param.parity = USCI_A_UART_NO_PARITY;    //��żУ��
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;    //���ƽ��պͷ�����λ�Ĵ����ķ���
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;    //ֹͣλ��1λ
    param.uartMode = USCI_A_UART_MODE;    //Ĭ��ģʽ
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION; //��ʾ��Ƶ��������������
    if (STATUS_FAIL == USCI_A_UART_init(baseAddress, &param))
    {
        //ʧ�ܷ���
        return false;
    }
    //ʹ�� UART ģ��
    USCI_A_UART_enable(baseAddress);
    //Enable Receive Interrupt
    USCI_A_UART_clearInterrupt(baseAddress, USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(baseAddress, USCI_A_UART_RECEIVE_INTERRUPT);
    return true;
}

/**
 * @brief  ���ڷ����ַ���
 * @param  baseAddress: ����ģ�飬*ptr: �ַ���
 * @retval ��
 */
void send_buf(uint16_t baseAddress, unsigned char *ptr)    //Send string.
{
    while (*ptr != '\0')
    {
        USCI_A_UART_transmitData(baseAddress, *ptr);
        ptr++;
    }
}



