#include "lis3dsh.h"

// LIS3DSH hardware registers. Split into low (_L) and high (_H), because the accelerometer outputs 16 bits, but SPI only reads 8 at a time
#define CTRL_REG4 0x20
#define OUT_X_L   0x28
#define OUT_X_H   0x29
#define OUT_Y_L   0x2A
#define OUT_Y_H   0x2B
#define OUT_Z_L   0x2C
#define OUT_Z_H   0x2D

static SPI_HandleTypeDef *accel_spi;

// --- Private helper functions

// write 1 byte to register via SPI
static void LIS3DSH_WriteReg(uint8_t reg, uint8_t data) {
	return;
}

// read 1 byte from register via SPI
static uint8_t LIS3DSH_ReadReg(uint8_t reg) {
	return 0;
}

// --- Public "API"

// startup
void LIS3DSH_Init(SPI_HandleTypeDef *hspi) {
	return;
}

// read the accelerometer's XYZ tilt values
void LIS3DSH_ReadTilt(int16_t *x, int16_t *y, int16_t *z) {
	return;
}
