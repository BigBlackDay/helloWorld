/**
  ************************************************
  *@file   spi_simulation.h
  *@author han
  *@time   2018-12-11 13:53:47
  *@note 
  ************************************************
  */

#ifndef __SPI_SIMULATION_H__
#define __SPI_SIMULATION_H__

#include <stdint.h>

//spi pin
#define SPI_PIN_CS_GPIOX       GPIOC
#define SPI_PIN_CS             GPIO_Pin_0  
#define SPI_PIN_MOSI_GPIOX     GPIOC
#define SPI_PIN_MOSI           GPIO_Pin_15
#define SPI_PIN_MISO_GPIOX     GPIOC
#define SPI_PIN_MISO           GPIO_Pin_14
#define SPI_PIN_CLK_GPIOX      GPIOC
#define SPI_PIN_CLK            GPIO_Pin_13  

/**@defGroup pin contorl
  *@{
  */
//init
#define CS_INIT          SPI_csInit()
#define MOSI_INIT        SPI_mosiInit()
#define MISO_INIT        SPI_misoInit()
#define CLK_INIT         SPI_clkInit()

//set bit
#define CS_H             GPIO_SetBits(SPI_PIN_CS_GPIOX,   SPI_PIN_CS)
#define MOSI_H           GPIO_SetBits(SPI_PIN_MOSI_GPIOX, SPI_PIN_MOSI)
#define CLK_H            GPIO_SetBits(SPI_PIN_CLK_GPIOX,  SPI_PIN_CLK)

//reset bit
#define CS_L             GPIO_ResetBits(SPI_PIN_CS_GPIOX,    SPI_PIN_CS)
#define MOSI_L           GPIO_ResetBits(SPI_PIN_MOSI_GPIOX,  SPI_PIN_MOSI)
#define CLK_L            GPIO_ResetBits(SPI_PIN_CLK_GPIOX, SPI_PIN_CLK)

#define MISO_READ        GPIO_ReadInputDataBit(SPI_PIN_MISO_GPIOX, SPI_PIN_MISO)

/**
  *@}
  */

void SPI_PinInit(void);
void SpiDelay(uint8_t temp);
uint8_t SPI_HOST_ReadWrite(uint8_t txData);

#endif
