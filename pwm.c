#include "pwm.h"
/**
 * @brief  PWM A��ʼ��
 * @param  baseAddress:ģ�飬compareRegister �ӿڣ�selectedPort: �ӿڵ�ַ��selectedPins���ӿںţ�timerPeriod������100Ϊ2.5us��dutyCycleռ�ձ�����Ϊ��ĸ
 * @retval ��
 */
void PwmIntA(uint16_t baseAddress, uint16_t compareRegister,
             uint8_t selectedPort, uint16_t selectedPins, uint16_t timerPeriod,
             uint16_t dutyCycle)
{
    if (timerPeriod == 0)
    {
        Timer_A_stop(baseAddress);
        return;
    }
    GPIO_setAsPeripheralModuleFunctionOutputPin(selectedPort, selectedPins);
    //Generate PWM - Timer runs in Up mode
    Timer_A_outputPWMParam param = { 0 };
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK; //ѡ��ʱ��Դ��SMCLK=40MHz�����systime.h
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1; //��ʱ��Դ����ķ�Ƶ��
    param.timerPeriod = timerPeriod; //ѡ������Ķ�ʱ������,Ĭ��0
    param.compareRegister = compareRegister; //ѡ������ʹ�õıȽϼĴ����� ��������ݱ���ȷ��������������ʹ�õĲ���ȽϼĴ�����
    param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET; //���ģʽ��λ����
    param.dutyCycle = dutyCycle; //ָ�����ɲ��ε�ռ�ձ�
    Timer_A_outputPWM(baseAddress, &param);
}
