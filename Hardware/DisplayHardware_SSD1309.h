/*
 * DisplayHardware_SSD1309.h
 *
 * Commands and defines for the ssd1309 oled display controller
 * in combination with the DotMatrix DisplayInterface in the RSOS
 *
 *  Created on: 07.05.2017
 *      Author: Richard
 */

#ifndef DISPLAYHARDWARE_SSD1309_H_
#define DISPLAYHARDWARE_SSD1309_H_

#include <stdint.h>

#include "../DotMatrixElement.h"

/**
 * minimum size of the command buffer
 */
#define DOTMATRIX_COMMANDBUFFER_SIZE 13

/**
 * I2C Slave Address
 */
#define SSD1309_SlaveAddress 0b0111101

/**
 * Command start Data /Command selection
 * if the bit is 1, the following bytes is treated as display data
 * if the bit is 0, the following BYTE is treated as command
 * (?? can a data sequence follow a command byte ??)
 */
#define DISPLAY_COMMAND_DATA 0x40

/**
 * Command start Co
 * if the bit is 0, all following bytes are display data bytes
 * if the bit is 1, ?
 */
#define DISPLAY_COMMAND_CO 0x80


/**
 * ======
 * Fundamental Commands
 * ======
 */

/**
 * command byte to set contrast, followed by contrast byte
 * (0..255)
 */
#define DISPLAY_COMMAND_CONTRAST 0x81

/**
 * entire display on, output follows ram content
 */
#define DISPLAY_COMMAND_DisplayON 0xA4

/**
 * entire display on, force all pixels on
 */
#define DISPLAY_COMMAND_DisplayOFF 0xA5

/**
 * set display inverted mode off
 */
#define DISPLAY_COMMAND_DisplayInvertModeOFF 0xA6

/**
 * set display inverted
 */
#define DISPLAY_COMMAND_DisplayInvertModeON 0xA7

/**
 * set force Display off (sleep-mode)
 */
#define DISPLAY_COMMAND_DisplaySleepModeON 0xAE

/**
 * set Display on (sleep-mode exit)
 */
#define DISPLAY_COMMAND_DisplaySleepModeOFF 0xAF

/**
 * command for no operation
 */
#define DISPLAY_COMMAND_NOP 0xE3

/**
 * Lock oled driver command
 * this command must be followed by actual lock /unlock command
 */
#define DISPLAY_COMMAND_DRIVER_LOCK 0xFD

/**
 * actual lock command
 * must be send together with Lock oled driver command
 */
#define DISPLAY_COMMAND_DRIVER_Unlock 0x12
#define DISPLAY_COMMAND_DRIVER_Lock 0x16


/**
 * ======
 * Positioning Commands
 * ======
 */

/**
 * set lower nibble for column address
 * in page address mode (logically or'ed with column number)
 * values ranging from 0 to 15
 */
#define DISPLAY_COMMAND_Column_Lower 0x00

/**
 * set higher nibble for column address
 * in page address mode (logically or'ed with column number)
 * values ranging from 0 to 7 (equals 0 to 112)
 */
#define DISPLAY_COMMAND_Column_Higher 0x10

/**
 * set the page
 * in page address mode (logically or'ed with page number)
 * values ranging from 0 to 7
 */
#define DISPLAY_COMMAND_Page 0xB0

/**
 * set memory addressing mode
 * this byte followed by an address mode byte
 * form the addressing mode command
 */
#define DISPLAY_COMMAND_SetAddressingMode 0x20

/**
 * addressing mode Horizontal
 * must be send together with SetAddressingMode
 */
#define DISPLAY_COMMAND_AddressModeHorizontal 0x00

/**
 * addressing mode Vertical
 * must be send together with SetAddressingMode
 */
#define DISPLAY_COMMAND_AddressModeVertical 0x01

/**
 * addressing mode page
 * must be send together with SetAddressingMode
 */
#define DISPLAY_COMMAND_AddressModePage 0x02

/**
 * set column start and end address
 * this command, followed by start column and
 * end column, form the setColumnAddress command
 * for Horizontal and Vertical Address Mode
 */
#define DISPLAY_COMMAND_SetColumn 0x21

/**
 * set page start and end address
 * this command, followed by start page and
 * end page form the setPageAddress command
 * for Horizontal and Vertical Address Mode
 */
#define DISPLAY_COMMAND_SetPage 0x22

/**
 * ======
 * Hardware Configuration Commands
 * ======
 */

/**
 * set Display start line
 * (logically or'ed with start line)
 * values ranging from 0 to 63
 */
#define DISPLAY_COMMAND_SetStartLine 0x40

/**
 * Segment Remap: address 0 mapped to SEG0
 */
#define DISPLAY_COMMAND_SegmentRemapSEG0 0xA0

/**
 * Segment Remap: address 0 mapped to SEG127
 */
#define DISPLAY_COMMAND_SegmentRemapSEG127 0xA1

/**
 * set Multiplex Ratio
 * this command, followed by a byte representing
 * the ratio (values from 15 to 63),
 * form the set Multiplex Ration command
 */
#define DISPLAY_COMMAND_SetMultiplexRatio 0xA8

/**
 * set COM output direction:
 * Scan from COM0 to COM[N-1]
 */
#define DISPLAY_COMMAND_COMDirectionNormal 0xC0

/**
 * set COM output direction:
 * Scan from COM[N-1] to COM0
 */
#define DISPLAY_COMMAND_COMDirectionRemap 0xC8

/**
 * set Display Offset (Vertical shift)
 * this command, followed by offset value
 * (from 0 to 63), form the Display Offset Command
 */
#define DISPLAY_COMMAND_SetDisplayOffset 0xD3

/**
 * Set COM pins hardware configuration
 * this byte, followed by a command value form
 * the COM pin Hardware Command
 */
#define DISPLAY_COMMAND_SetCOMPins 0xDA

/**
 * Hardware Configuration:
 * Sequential COM pin configuration,
 * Disable COM left/right remap
 * must be send together with SetCOMPins
 */
#define DISPLAY_COMMAND_SetCOMPinsMODE0 0x02

/**
 * Hardware Configuration:
 * Alternative COM pin configuration,
 * Disable COM left/right remap
 * must be send together with SetCOMPins
 */
#define DISPLAY_COMMAND_SetCOMPinsMODE1 0x12

/**
 * Hardware Configuration:
 * Sequential COM pin configuration,
 * Enable COM left/right remap
 * must be send together with SetCOMPins
 */
#define DISPLAY_COMMAND_SetCOMPinsMODE2 0x22

/**
 * Hardware Configuration:
 * Alternative COM pin configuration,
 * Enable COM left/right remap
 * must be send together with SetCOMPins
 */
#define DISPLAY_COMMAND_SetCOMPinsMODE3 0x32


/**
 * ======
 * Timing and Driving Scheme Commands
 * ======
 */

/**
 * Display Clock Divider and Oscillator Frequency
 * this command, followed by a value for the divider and clock frequncy,
 * form the Clock Frequency and Divider command
 * the following byte holds two fields:
 *      FFFF DDDD
 *      F: Oscillator Frequency, Reset is 0b0111
 *      D: Divider (+1), Reset is 0b0000
 */
#define DISPLAY_COMMAND_FREQUENCY_DIVIDER 0xD5

/**
 * Pre Charge Period
 * this command, followed by a value for the charge time,
 * form the Pre Charge Period command
 * the following byte holds both phases of the charge time
 *      2222 1111
 *      2: Phase 2 in clock cycles
 *      1: Phase 1 in clock cycles
 *      0 is an invalid time, reset is 2
 */
#define DISPLAY_COMMAND_PRECHARGEPeriod 0xD9

/**
 * Vcomh Deselect Level
 * this command, followed by a value for the deselect voltage on Vcomh,
 * form the Vcomh Deselect Level command
 * the following byte holds the level for Vcomh:
 *      00LL LL00
 *      L: Percentage of Vcc, values ranging from 0 (0.64Vcc) to 15 (0.84Vcc)
 *         reset is 0b1101 (0.78Vcc)
 */
#define DISPLAY_COMMAND_VCOMH_DeselectLevel 0xDB

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
    if (bufferlength - bufferoffset >= 13)
    {
        buffer[bufferoffset+0] = DISPLAY_COMMAND_CO;
        buffer[bufferoffset+1] = DISPLAY_COMMAND_DRIVER_LOCK;
        buffer[bufferoffset+2] = DISPLAY_COMMAND_DRIVER_Unlock;
        buffer[bufferoffset+3] = DISPLAY_COMMAND_CO;
        buffer[bufferoffset+4] = DISPLAY_COMMAND_FREQUENCY_DIVIDER;
        buffer[bufferoffset+5] = 0xA0;
        buffer[bufferoffset+6] = DISPLAY_COMMAND_CO;
        buffer[bufferoffset+7] = DISPLAY_COMMAND_SegmentRemapSEG127;
        buffer[bufferoffset+8] = DISPLAY_COMMAND_CO;
        buffer[bufferoffset+9] = DISPLAY_COMMAND_COMDirectionRemap;
        buffer[bufferoffset+10] = DISPLAY_COMMAND_CO;
        buffer[bufferoffset+11] = DISPLAY_COMMAND_PRECHARGEPeriod;
        buffer[bufferoffset+12] = 0x25;
        return 13;
    }
    return 0;

}

/**
 * Function uint8_t setCommandPosition(DisplayElement* element, uint8_t line, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength)
 * fills the buffer with display specific information to set the cursor to the position (line, column)
 * @param element: the DisplayElement to be transferred (used for obtaining position and size)
 * @param line: the (base) line of the element
 * @param buffer: the buffer to be filled with the information
 * @param bufferoffset: the offset of the buffer, bytes are written to the index bufferoffset + n
 * @param bufferlength: the maximum length of the buffer; this function won't write to the buffer if length isn't sufficient
 * @return the number of bytes written to the buffer
 */
static inline uint8_t setCommandPosition(DisplayElement* element, uint8_t line, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength) __attribute__((always_inline));
static inline uint8_t setCommandPosition(DisplayElement* element, uint8_t line, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength)
{
    if (bufferlength-bufferoffset >= 11) {
        buffer[bufferoffset+0] = DISPLAY_COMMAND_CO;
        buffer[bufferoffset+1] = DISPLAY_COMMAND_SetAddressingMode;
        buffer[bufferoffset+2] = DISPLAY_COMMAND_AddressModeHorizontal;
        buffer[bufferoffset+3] = DISPLAY_COMMAND_CO;
        buffer[bufferoffset+4] = DISPLAY_COMMAND_SetColumn;
        buffer[bufferoffset+5] = element->pos_x;
        buffer[bufferoffset+6] = element->pos_x + element->len_x;
        buffer[bufferoffset+7] = DISPLAY_COMMAND_CO;
        buffer[bufferoffset+8] = DISPLAY_COMMAND_SetPage;
        buffer[bufferoffset+9] = (element->status & dotMatrix_lineMask) >> 4;
//        buffer[bufferoffset+10] = ((element->status & dotMatrix_lineMask) >> 4) + (element->status & dotMatrix_additionalLineMask);
        buffer[bufferoffset+10] = (line) + (element->status & dotMatrix_additionalLineMask);
        return 11;
    }
    return 0;
}

/**
 * Function uint8_t setCommandData(DisplayElement* element, uint8_t * buffer, uint8_t bufferoffset, uint8_t bufferlength)
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
    if (bufferlength-bufferoffset >= 1) {

        buffer[bufferoffset+0] = DISPLAY_COMMAND_DATA;
        return 1;
    }
    return 0;
}

#endif /* DISPLAYHARDWARE_SSD1309_H_ */
