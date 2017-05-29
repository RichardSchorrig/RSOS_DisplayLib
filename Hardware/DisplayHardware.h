/*
 * DisplayHardware.h
 *
 *  Created on: 24.02.2017
 *      Author: Richard
 */

#ifndef DISPLAYHARDWARE_H_
#define DISPLAYHARDWARE_H_

/**
 * Hardware defines for the SSD1309 Oled driver, connected via I2C or SPI
 */
#ifdef DOTMATRIX_USE_SSD1309
#include "DisplayHardware_SSD1309.h"
#endif /* DOTMATRIX_USE_SSD1309 */

/**
 * Hardware defines for the SED1520 LCD driver, connected via SPI and DotMatrixDisplayInterface(TM)
 */
#ifdef DOTMATRIX_USE_SED1520
#include "DisplayHardware_SED1520.h"
#endif /* DOTMATRIX_USE_SED1520 */


#endif /* DISPLAYHARDWARE_H_ */
