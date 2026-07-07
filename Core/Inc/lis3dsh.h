#ifndef LIS3DSH_H
#define LIS3DSH_H

#include "stm32f4xx_hal.h"

void LIS3DSH_Init(SPI_HandleTypeDef *hspi);
void LIS3DSH_ReadTilt(int16_t *x, int16_t *y, int16_t *z);

#endif
