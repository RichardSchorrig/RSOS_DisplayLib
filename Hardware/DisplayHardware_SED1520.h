/*
 * DisplayHardware_SED1520.h
 *
 *  Created on: 21.02.2017
 *      Author: Richard
 */

#ifndef DISPLAYHARDWARE_SED1520_H_
#define DISPLAYHARDWARE_SED1520_H_

#include <stdint.h>

#include "../DotMatrixElement.h"

/**
 * Definition to force a repositioning on each new line
 */
#define DISPLAY_PositioningOnEachNewLine

/**
 * minimum size of the command buffer
 */
#define DOTMATRIX_COMMANDBUFFER_SIZE 8

/**
 * Command Bytes for DotMatrix Display Interface hardware
 *
 * Command Start Byte:
 * 110B AxCC
 *
 * B: brightness bit, if set change brightness of LCD backlight
 * A, C: A bit sets instruction mode/ data mode; other bits the according CS signals (CS1/ CS2)
 */
#define COMMAND_START 0xC0
#define COMMAND_BRIGHTNESS 0x10
#define COMMAND_START_CS1 0x02
#define COMMAND_START_CS2 0x01
#define COMMAND_START_A0 0x08

/**
 * Command Bytes for SED1520 hardware
 */
#define COMMAND_DISPLAYDRIVER_ON 0xAF
#define COMMAND_DISPLAYDRIVER_OFF 0xAE
#define COMMAND_STATICDRIVE_ON 0xA5
#define COMMAND_STATICDRIVE_OFF 0xA4
#define COMMAND_RESET 0xE2
#define COMMAND_SETPAGE 0xB8
#define COMMAND_PAGE0 0x00
#define COMMAND_PAGE1 0x01
#define COMMAND_PAGE2 0x02
#define COMMAND_PAGE3 0x03
#define COMMAND_SETLINE 0xC0 /*Line 0: 0xC0, Line 1: 0xC1 ... Line 31: 0xDF*/

/**
 * Function uint8_t initializeDisplayHardware(uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength)
 * writes initialize data to the buffer
 * @param buffer: the buffer to be filled with the information
 * @param bufferoffset: the offset of the buffer, bytes are written to the index bufferoffset + n
 * @param bufferlength: the maximum length of the buffer; this function won't write to the buffer if length isn't sufficient
 * @return the number of bytes written to the buffer
 */
static inline uint8_t initializeDisplayHardware(uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength) __attribute__((always_inline));
static inline uint8_t initializeDisplayHardware(uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength)
{
    if (bufferlength-bufferoffset >= 8)
    {
        buffer[bufferoffset+0] = COMMAND_START | COMMAND_START_CS1 | COMMAND_START_CS2 | COMMAND_START_A0;
        buffer[bufferoffset+1] = 6;
        buffer[bufferoffset+2] = COMMAND_RESET;
        buffer[bufferoffset+3] = COMMAND_DISPLAYDRIVER_ON;
        buffer[bufferoffset+4] = COMMAND_STATICDRIVE_OFF;
        buffer[bufferoffset+5] = COMMAND_SETLINE;
        buffer[bufferoffset+6] = COMMAND_SETPAGE;
        buffer[bufferoffset+7] = 0;

        return 8;
    }
    return 0;
}

/**
 * Function uint8_t setCommandPosition(DisplayElement* element, uint8_t line, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength)
 * fills the buffer with display specific information to set the cursor to the position (line, column)
 * @param element: the DisplayElement to be transferred (used for obtaining position and size)
 * @param line: the line to set the cursor to
 * @param buffer: the buffer to be filled with the information
 * @param bufferoffset: the offset of the buffer, bytes are written to the index bufferoffset + n
 * @param bufferlength: the maximum length of the buffer; this function won't write to the buffer if length isn't sufficient
 * @return the number of bytes written to the buffer
 */
static inline uint8_t setCommandPosition(DisplayElement* element, uint8_t line, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength) __attribute__((always_inline));
static inline uint8_t setCommandPosition(DisplayElement* element, uint8_t line, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength)
{
    if (bufferlength-bufferoffset >= 4) {
        uint8_t xpos = element->pos_x;
        buffer[bufferoffset+0] = COMMAND_START | COMMAND_START_A0;
        if (xpos < 62) {
            buffer[bufferoffset+0] |= COMMAND_START_CS1;
        }
        else {
            buffer[bufferoffset+0] |= COMMAND_START_CS2;
        }
        xpos = xpos < 62 ? xpos : xpos - 62;
        buffer[bufferoffset+1] = 2;
        buffer[bufferoffset+2] = COMMAND_SETPAGE | line;
        buffer[bufferoffset+3] = xpos;

        return 4;
    }
    return 0;
}

/**
 * Function uint8_t setCommandData(DisplayElement* element, uint8_t * buffer, uint8_t bufferlength)
 * fills the buffer with display specific information to transfer data
 * @param element: the DisplayElement to be transferred (used for obtaining position and size)
 * @param buffer: the buffer to be filled with the information
 * @param bufferoffset: the offset of the buffer, bytes are written to the index bufferoffset + n
 * @param bufferlength: the maximum length of the buffer; this function won't write to the buffer if length isn't sufficient
 * @return the number of bytes written to the buffer
 */
static inline uint8_t setCommandData(DisplayElement* element, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength) __attribute__((always_inline));
static inline uint8_t setCommandData(DisplayElement* element, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength)
{
    if (bufferlength-bufferoffset >= 2) {
        buffer[bufferoffset+0] = COMMAND_START;
        if (element->pos_x < 62) {
            buffer[bufferoffset+0] |= COMMAND_START_CS1;
        }
        else {
            buffer[bufferoffset+0] |= COMMAND_START_CS2;
        }
        buffer[bufferoffset+1] = element->len_x;
        return 2;
    }
    return 0;
}


#endif /* DISPLAYHARDWARE_SED1520_H_ */
