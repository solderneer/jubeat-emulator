#ifndef __UART_H
#define __UART_H

/* Includes */
#include "stm32f4xx_hal.h"
#include "stdint.h"

typedef enum {
  UART_TransmitSuccess,
  UART_TransmitFail
}UART_TransmitResult;

UART_HandleTypeDef test;

/* Public function prototypes */
UART_HandleTypeDef* MX_USART1_UART_Init(void);
UART_TransmitResult UART_TransmitByte(UART_HandleTypeDef* huart, uint8_t transmitByte);
UART_TransmitResult UART_TransmitBytes(UART_HandleTypeDef* huart, uint8_t* transmitBytes, uint16_t noBytes);

#endif /* __UART_H */
