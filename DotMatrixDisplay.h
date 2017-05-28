/*
 * DotMatrixDisplay.h
 *
 *  Created on: 02.10.2016
 *      Author: Richard
 */

#ifndef DOTMATRIXDISPLAY_H_
#define DOTMATRIXDISPLAY_H_

#include <stdint.h>
#include <RSOSDefines.h>

/* exclude everything if not used */
#ifdef DOTMATRIX_MEMSIZE

#include "DotMatrixElement.h"

#ifndef DOTMATRIX_SPI
#ifndef DOTMATRIX_I2C
#error "No Serial Interface Type specified: either DOTMATRIX_SPI or DOTMATRIX_I2C"
#endif
#endif /* SPI / I2C */

#include <Task.h>
#include <buffer/BasicBuffer.h>
#include <buffer/Buffer_int8.h>
#include <buffer/BufferBuffer_int8.h>

#ifdef DOTMATRIX_SPI
#include <SerialInterface/SPIOperation.h>
#elif defined DOTMATRIX_I2C
#include <SerialInterface/I2C_Operation.h>
#endif /* SPI / I2C */

extern int8_t dotMatrix_size;
extern DisplayElement dotMatrix_mem[DOTMATRIX_MEMSIZE];

/**
 * User can add commands to the buffer and force the output
 * by calling
 * DotMatrix_forceCommandOutput()
 */
extern uint8_t g_dotMatrix_displayCommandBuffer[10];

/**
 * resets the display, initializes the dot matrix display function
 * (must be called prior any other dot matrix function call)
 * to operate, the following structures must be available:
 *      1x Task
 *      3x Buffer_void
 *      1x DisplayElement ?
 *
 * @param dotMatrixSOP the SerialInterface operation structure to use.
 *                    must be initialized outside, the type depends on
 *                    preprocessor define. The buffer for the operation structure
 *                    can be acquired by calling DotMatrix_getBuffer();
 *
 * takes an initialized SerialInterface structure,
 * either an SPIOperation or an I2COperation, depending on the operation.
 * a preprocessor define, either DOTMATRIX_SPI or DOTMATRIX_I2C, must exist
 */
#ifdef DOTMATRIX_SPI
void DotMatrix_initDisplay(SPIOperation* dotMatrixSOP);
#elif defined DOTMATRIX_I2C
void DotMatrix_initDisplay(I2C_Data* dotMatrixSOP);
#endif /* SPI / I2C */

/**
 * used for the init process for the Serial Interface Operation that is needed
 * for the DotMatrix_initDisplay() function. Also initializes all needed buffers.
 * The Serial Interface must be initialized with the buffer returned by this function
 * @return the buffer to use for the serial interface
 */
Buffer_void* DotMatrix_getBuffer();

/**
 * writes the commands needed to initialize the display's hardware
 * @return -1 if the interface is currently busy, 0 if the transfer is successfully initiated
 */
int8_t DotMatrix_initializeDisplayHardware();

/**
 * task function: checks all display elements for active bit
 * if an active element is found, it cycles until all lines of the element are transferred
 * it also checks the next element if it is active. If the next active element refers to the same
 * display line and is not too far apart (10 positions) it will be added to the transfer
 */
void DotMatrix_transferElement();

/**
 * initializes a new Display Element with the given positions and sizes
 * the position defines the upper left corner
 * the size defines the size, or, the lower right corner along with the position
 *
 * to make display operation more efficient, you should init the display elements in the order
 * of their position on the display
 *
 * @param xpos: the x position of the element on the screen in pixel
 * @param ypos: the y position of the element on the screen in pixel
 * @param xsize: the x size of the element in pixel
 * @param ysize: the y size of the element in pixel
 * @param isInverted: displays the element inverted (can be used for list selections)
 *                    0: not inverted, 1: invert element
 * @return: the initialized DisplayElement structure
 */
DisplayElement* DotMatrix_newDisplayElement(uint8_t xpos, uint8_t ypos, uint8_t xsize, uint8_t ysize, uint8_t showInverted);

/**
 * cleans the entire display
 */
int8_t DotMatrix_CleanDisplay();

/**
 * cleans the entire display element delm, i.e. sets all pixel to 0 (even when element is inverted)
 * @return 1 on success, -1 on failure
 */
int16_t DotMatrix_cleanElement(DisplayElement* delm);

//int8_t DotMatrix_scroll(uint8_t line);

/**
 * checks if any element is currently transferred
 * @return 0: no element is transferred
 *         any positive number: the number of bytes left to be transferred
 */
uint8_t DotMatrix_isActive();

/**
 * can be used to write the bytes from the command buffer to the display element
 * prior to calling, the g_dotMatrix_displayCommandBuffer should be filled with
 * the bytes to be transferred. Before filling the buffer, call DotMatrix_isActive()
 * to check if the buffer is currently in use.
 * @param nOfBytes: the number of bytes to be transferred from the command buffer
 * @return 1 if successful
 */
int8_t DotMatrix_forceCommandOutput(uint8_t nOfBytes);

/**
 * changes display data according to data till the end of the element or datalen is reached
 * position is relative to the display element, so 0,0 describes the top left corner of the element
 * data leaking out of boundary is discarded
 *
 * @param delm: the display element to change
 * @param xpos: the x position inside the display element, at which point it is to change. can be negative, data will be cut to fit
 * @param ypos: the y position inside the display element, at which point it is to change. can be negative
 * @param data: the data buffer to copy to the display element's memory
 * @param datalen: the maximum number of bytes to read of data
 *
 * @return: -1 if changes were not possible (dimensions out of bounds) or element is currently transferred, 0 if no changes where made,
 *          or the number of changed columns
 */
int8_t DotMatrix_changeElementN(DisplayElement* delm, int16_t xpos, int16_t ypos, const uint8_t * data, uint8_t datalen);

/**
 * changes one column of display data
 * position is relative to the display element, so 0,0 describes the top left corner of the element
 * data leaking out of boundary is discarded
 *
 * @param delm: the display element to change
 * @param xpos: the x position inside the display element, at which point it is to change. can be negative, data will be cut to fit
 * @param ypos: the y position inside the display element, at which point it is to change. can be negative
 * @param data: a data byte to copy to the display element's memory
 *
 * @return: -1 if changes were not possible (dimensions out of bounds) or element is currently transferred, 0 if no changes where made,
 *          or 1 if change was successful
 */
int8_t DotMatrix_changeElement(DisplayElement* delm, int16_t xpos, int16_t ypos, const uint8_t data);

/**
 * activates the element for update on the display. the content corresponding to the position of the
 * Display Element is transferred to the display.
 * @param delm: the display element to be activated
 */
void DotMatrix_activateElement(DisplayElement* delm);


#endif /* DOTMATRIX_MEMSIZE */
#endif /* DOTMATRIXDISPLAY_H_ */
