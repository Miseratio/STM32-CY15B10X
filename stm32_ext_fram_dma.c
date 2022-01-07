#include "stm32_ext_fram_dma.h"

void FRAM_DMA_Init(){
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	uint8_t buf[2];
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	buf[0] = 0x06; //CMD_WREN
	HAL_SPI_Transmit(&hspi1, buf, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	buf[0] = 0x01; //CMD_WRSR
	buf[1] = 0xc0;
	HAL_SPI_Transmit(&hspi1, buf, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

}

void FRAM_DMA_Read(uint8_t *addr, uint8_t *dst, unsigned long len){
	uint8_t buf[4];
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	buf[0] = 0x03; //CMD_READ;
	buf[1] = addr[0];
	buf[2] = addr[1];
	buf[3] = addr[2];
	HAL_SPI_Transmit(&hspi1, buf, 4, HAL_MAX_DELAY);
	completed_rx = 0;
	HAL_SPI_Receive_DMA(&hspi1, dst, len);
	while(completed_rx == 0){;}
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}

void FRAM_DMA_Write(uint8_t *addr, uint8_t *src, unsigned long len){
	uint8_t buf[4];
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	buf[0] = 0x06; //CMD_WREN
	HAL_SPI_Transmit(&hspi1, buf, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);

	buf[0] = 0x02; //CMD_WRITE;
	buf[1] = addr[0];
	buf[2] = addr[1];
	buf[3] = addr[2];
	HAL_SPI_Transmit(&hspi1, buf, 4, HAL_MAX_DELAY);
	completed_tx = 0;
	HAL_SPI_Transmit_DMA(&hspi1, src, len);
	while(completed_tx == 0){;}
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi)
{
	completed_tx = 1;
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi)
{
	completed_rx = 1;
}
