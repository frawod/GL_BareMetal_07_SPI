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
	uint8_t tx_buffer[2] = {reg, data}; // bit 7 is 0 (write) by default

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // select the chip
	HAL_SPI_Transmit(accel_spi, tx_buffer, 2, HAL_MAX_DELAY); // write to it
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);   // deselect
}

// read 1 byte from register via SPI
static uint8_t LIS3DSH_ReadReg(uint8_t reg) {
	uint8_t tx_buffer[2] = {reg | 0x80, 0x00}; // bit 7 set to 1 (read) + dummy byte (unimportant worthless value) just to be able to transmit 'something'
	uint8_t rx_buffer[2] = {0, 0};

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // select
	HAL_SPI_TransmitReceive(accel_spi, tx_buffer, rx_buffer, 2, HAL_MAX_DELAY); // read
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET); // deselect

	return rx_buffer[1]; // return the actual read data
}

// --- Public "API"

// startup
void LIS3DSH_Init(SPI_HandleTypeDef *hspi) {
	accel_spi = hspi;

	// configuration
	LIS3DSH_WriteReg(CTRL_REG4, 0x67);
	// 0x67 = 0110 0111
	// 0110 = 100 Hz output
	// 0111 = enable X, Y and Z

	HAL_Delay(100); // to give the sensor time to stabilize. I actually have no idea how much time it needs exactly though
}

// read the accelerometer's XYZ values
void LIS3DSH_ReadXYZ(int16_t *x, int16_t *y, int16_t *z) {
	// read the lower and higher halves of the XYZ values
	uint8_t xl = LIS3DSH_ReadReg(OUT_X_L);
	uint8_t xh = LIS3DSH_ReadReg(OUT_X_H);

	uint8_t yl = LIS3DSH_ReadReg(OUT_Y_L);
	uint8_t yh = LIS3DSH_ReadReg(OUT_Y_H);

	uint8_t zl = LIS3DSH_ReadReg(OUT_Z_L);
	uint8_t zh = LIS3DSH_ReadReg(OUT_Z_H);

	// put the values together
	*x = (int16_t)((xh << 8) | xl);
	*y = (int16_t)((yh << 8) | yl);
	*z = (int16_t)((zh << 8) | zl);
}
