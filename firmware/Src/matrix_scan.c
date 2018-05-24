/* Includes */
#include "matrix_scan.h"
#include "stm32f4xx_hal.h"
#include "bsp.h"
#include "stdint.h"

/* Private function prototypes */
uint8_t Matrix_ScanCol(void);

/* Function Definitions */
void Matrix_Init(void)
{
  // Code to initialize appropriate GPIO pins
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|COL1_Pin|COL2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, COL3_Pin|COL4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin 
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
  */

  /*Configure GPIO pins : LD2_Pin COL1_Pin COL2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|COL1_Pin|COL2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : COL3_Pin COL4_Pin */
  GPIO_InitStruct.Pin = COL3_Pin|COL4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW1_Pin ROW2_Pin ROW3_Pin */
  GPIO_InitStruct.Pin = ROW1_Pin|ROW2_Pin|ROW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ROW4_Pin */
  GPIO_InitStruct.Pin = ROW4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ROW4_GPIO_Port, &GPIO_InitStruct);
}

// TODO: Optimize using loops or smth
void Matrix_Scan(uint8_t* results)
{
  // Resetting array space
  *results = 0;
  *(results+1) = 0;

  // Scanning column 1
  HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_SET);
  *results = Matrix_ScanCol();
  HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, GPIO_PIN_RESET);

  // Scanning column 2
  HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_SET);
  *results = (Matrix_ScanCol() << 4);
  HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, GPIO_PIN_RESET);

  // Scanning column 3
  HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_SET);
  *(results+1) = Matrix_ScanCol();
  HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, GPIO_PIN_RESET);

  // Scanning column 4
  HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_SET);
  *(results+1) = (Matrix_ScanCol() << 4);
  HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_RESET);
}

/* Private helper function */
uint8_t Matrix_ScanCol(void)
{
  uint8_t results = 0;

  results |= HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin);
  results |= (HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin) << 1);
  results |= (HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) << 2);
  results |= (HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) << 3);

  return results;
}
