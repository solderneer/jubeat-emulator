#ifndef __MATRIX_SCAN_H
#define __MATRIX_SCAN_H

/* Includes */
#include "stm32f4xx_hal.h"
#include "bsp.h"
#include "stdint.h"

/* Public function prototypes */
void Matrix_Init(void);
uint16_t Matrix_Scan(void);

#endif /* __MATRIX_SCAN_H */
