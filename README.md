# PCF8591-drive
用于PCF8951的驱动库（基于STM32G431写的，移植方便）
用例
```
#include "PCF8951.h"

PFC8951_Typedef PCF8951 = { 0 };
uint8_t txData[2] = { 0 };
uint8_t rxData[20] = { 0 };

int main()
{
    PCF8951.PCF8951AddressRead = PCF8951_ADR_R;
    PCF8951.PCF8951AddressWrite = PCF8951_ADR_W;
    PCF8951.PCF8951ControlByte = PCF_CONTROL_BYTE(PCF_ANALOG_OUT_ENABLE, PCF_AD_MODE_SINGLE_ENDED, PCF_AUTO_INCREMENT_ENABLE, PCF_AD_CHANNEL_0);
    txData[0] = PCF8951.PCF8951ControlByte;
    /* 呼吸灯效果先亮再灭 */
    for(uint16_t i = 0; i < 255; i++)
    {
        txData[1] = i;
        PCF8951_DAC_Output(PCF8951, txData, 2);
        HAL_Delay(10);
    }
    for(uint16_t i = 0; i < 255; i++)
    {
        txData[1] = 256 - i;
        PCF8951_DAC_Output(PCF8951, txData, 2);
        HAL_Delay(10);
    }
    PCF8951_Init(PCF8951);
    PCF8951_ADC_intput(PCF8951, rxData, sizeof(rxData));
    while(1);
}
```
