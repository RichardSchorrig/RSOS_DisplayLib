/*
 * DotMatrixElement.h
 *
 *  Created on: 26.05.2017
 *      Author: Richard
 */

#ifndef OUTPUT_DOTMATRIXELEMENT_H_
#define OUTPUT_DOTMATRIXELEMENT_H_


/**
 * Display Element structure
 * Fields:
 *  pos_x, pos_y: position of the upper left corner in display
 *  len_x: the length of the elemnt in x direction
 *  height_y: the height of the element, in negative y direction
 *  status: bit field containing:
 *      AIxx xxxx LLLL MMMM
 *      A: active bit
 *      I: bit if this element should be displayed inverted
 *      L: the line corresponding to the y position. In case the height of the element interfere
 *         with more than one line, this is the first line
 *      M: additional lines, i.e. the other lines if element extends over more lines
 *         example: LLLL = 4, MMMM = 3 -> the element extends over line 4 through 7
 */
typedef struct DisplayElement_t {
    uint8_t pos_x;
    uint8_t pos_y;
    uint8_t len_x;
    uint8_t height_y;
//  uint8_t * buffer;
    uint16_t status;
} DisplayElement;

/**
 * sizes
 */
#define DOTMATRIX_DISPLAY_LINES (DOTMATRIX_DISPLAY_YRES / 8)

/**
 * bit identifier: is active
 */
#define dotMatrix_activeBit 0x8000

/**
 * bit identifier: is inverted
 */
#define dotMatrix_isInverted 0x4000

/**
 * mask: base line
 */
#define dotMatrix_lineMask 0x00F0

/**
 * mask: total lines
 */
#define dotMatrix_additionalLineMask 0x000F


#endif /* OUTPUT_DOTMATRIXELEMENT_H_ */
