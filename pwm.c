#include "pwm.h"
/**
 * @brief  PWM A初始化
 * @param  baseAddress:模块，compareRegister 接口，selectedPort: 接口地址，selectedPins：接口号，timerPeriod：周期100为2.5us，dutyCycle占空比周期为分母
 * @retval 无
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
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK; //选择时钟源：SMCLK=40MHz，详见systime.h
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1; //是时钟源所需的分频器
    param.timerPeriod = timerPeriod; //选择所需的定时器周期,默认0
    param.compareRegister = compareRegister; //选择正在使用的比较寄存器。 请参阅数据表以确保器件具有正在使用的捕获比较寄存器。
    param.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET; //输出模式复位设置
    param.dutyCycle = dutyCycle; //指定生成波形的占空比
    Timer_A_outputPWM(baseAddress, &param);
}
