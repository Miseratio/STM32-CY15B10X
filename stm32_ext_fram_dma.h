
#include <stdint.h>

/* Define SPI_CS Pin config */
#ifdef STM32WB55xx
	#include "stm32wbxx_hal.h"
    #define SPI1_CS_Pin GPIO_PIN_4
    #define SPI1_CS_GPIO_Port GPIOA
#endif

#ifdef STM32L496xx
	#include "stm32l4xx_hal.h"
    #define SPI1_CS_Pin GPIO_PIN_13
    #define SPI1_CS_GPIO_Port GPIOH
#endif

extern SPI_HandleTypeDef hspi1;

void FRAM_DMA_Init();
void FRAM_DMA_Read(uint8_t *addr, uint8_t *dst, unsigned long len);
void FRAM_DMA_Write(uint8_t *addr, uint8_t *src, unsigned long len);
