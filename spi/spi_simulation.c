/**
  ****************************************************
  *@file   spi_simulation.c
  *@author han
  *@time   2018-12-11 13:46:55
  *@note 
  ****************************************************
  */
#include "stm32f4xx_gpio.h"
#include "SPI_simulation.h"

void SPI_csInit()
{
}
void SPI_mosiInit()
{ 
}
void SPI_misoInit()
{  
}
void SPI_clkInit()
{
}

void SpiDelay(uint8_t temp)
{
    uint8_t i,j;
    for (i=0; i<temp; i++)
        for (j=0; j<255; j++);
}

/**
  *@brief host spi read write
  */
uint8_t SPI_HOST_ReadWrite(uint8_t txData)
{
    uint8_t i;
    uint8_t rxData=0;
    
    CLK_L;
    CS_L;
    
    for (i=0; i<8; i++)
    {
        CLK_L;
        if (txData & (0x01<<(7-i)))
        {
            MOSI_H;            
        }
        else
        {
            MOSI_L;               
        }
        SpiDelay(30);
        
        CLK_H;
        SpiDelay(30); 
        if (MISO_READ)                rxData |=  (0x01<<(7-i));
        else                          rxData &= ~(0x01<<(7-i));
        SpiDelay(3);
    }
    CS_H;
    CLK_L;
    SpiDelay(30); 
    
    return rxData;
}


/**
  *@brief slave spi read write
  *@param txData  send data
  *       rxData  read data
  *@return 0 right  1 error
  *@note  This function is used by the slave to receive data, 
  *       and the above function is not in a file, 
  *       so if you want to use it, 
  *       the manipulation function for the pin must be rewritten according to the content.
  */
uint8_t SPI_SLAVE_ReadWrite(uint8_t txData, uint8_t *rxData)
{
    uint8_t i;
        
    if (CS_READ == 0)
    {
//        printf("C");
        for (i=0; i<8; i++)
        {
            while ((CLK_READ == 0) && (CS_READ == 0))
            {
                if (MOSI_READ)               
                {                    
                    (*rxData) |=  (0x01<<(7-i));
//                    printf("h");
                }
                else  
                {
                    (*rxData) &= ~(0x01<<(7-i));
//                    printf("l");
                }
            }
            
            while ((CLK_READ == 1) && (CS_READ == 0))
            {
                if (txData & (0x01<<(7-i)))
                {
                    MISO_H;                    
//                    printf("H");
                }
                else
                {
                    MISO_L;    
//                    printf("L");
                }
            }
        }
        
        while (CS_READ == 0) ;
        return 0;
    }        
    
    return 1;
}

void SPI_PinInit(void)
{
    CS_INIT;
    CS_H;
    MOSI_INIT;
    MISO_INIT;
    CLK_INIT;
}
