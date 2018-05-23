/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "bsp.h"

/* Private Variables */
UART_HandleTypeDef huart1;

/* USART1 init function */
UART_HandleTypeDef* MX_USART1_UART_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  return &huart1; // Passing pointer to UART Handler
}

// Blocking UART TODO: Implement non-blocking but i really don't see a point
UART_TransmitResult UART_TransmitByte(UART_HandleTypeDef* huart, uint8_t transmitByte)
{
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_TXE)) { // Check for transmit buffer empty
    //HAL_StatusTypeDef transmitStatus;
    //transmitStatus = 
    HAL_UART_Transmit(huart, &transmitByte, 1, (uint32_t)10000);
    return UART_TransmitSuccess;
  }
  else
    return UART_TransmitFail;

  return UART_TransmitFail;
}

UART_TransmitResult UART_TransmitBytes(UART_HandleTypeDef* huart, uint8_t* transmitBytes, uint16_t noBytes)
{
  if(__HAL_UART_GET_FLAG(huart, UART_FLAG_TXE)) {
    //HAL_StatusTypeDef transmitStatus;
    //transmitStatus =
    HAL_UART_Transmit(huart, transmitBytes, noBytes, (uint32_t)(10000 * noBytes));
    return UART_TransmitSuccess;
  }
  else
    return UART_TransmitFail;

  return UART_TransmitFail;
}


