
/* 
 * File:   display.h
 * Author: maxymsmal
 *
 * Created on September 20, 2025, 2:01 PM
 */
#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>
#include <stddef.h>

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 32

#define SSD1306_I2C_ADDR 0x3C

/**
 * @brief Initialize the SSD1306 display.
 */
void ssd1306_InitDisplay(void);

/**
 * @brief Write a command to the SSD1306 display.
 * 
 * @param command The command byte to write.
 */
void ssd1306_WriteCommand(uint8_t command);

/**
 * @brief Write data to the SSD1306 display.
 * 
 * @param data Pointer to the data buffer to write.
 * @param size Number of bytes to write from the data buffer.
 */
void ssd1306_WriteData(uint8_t* data, size_t size);

/**
 * @brief Clear the display buffer.
 */
void ssd1306_ClearDisplay(void);

/**
 * @brief Update the display with the contents of the buffer.
 */
void ssd1306_SetDisplay(void);

/**
 * @brief Update the display in horizontal addressing mode.
 */
void ssd1306_SetDisplay_Horisontal(void);

/**
 * @brief Update the display in vertical addressing mode.
 */
void ssd1306_SetDisplay_Vertical(void);

/**
 * @brief Enable or disable the display.
 * 
 * @param state 1 to enable, 0 to disable.
 */
void ssd1306_EnableDisplay(uint8_t state);

/**
 * @brief Set the display contrast.
 * 
 * @param value Contrast value (0-255).
 */
void ssd1306_SetContrast(uint8_t value);

/**
 * @brief Set the display inversion mode.
 * 
 * @param setInversion 1 to enable inversion, 0 to disable.
 */
void ssd1306_SetInversionMode(uint8_t setInversion);

/**
 * @brief Set the display to entire mode (all pixels on).
 * 
 * @param state 1 to enable entire mode, 0 to disable.
 */
void ssd1306_SetEntireMode(uint8_t state);

/**
 * @brief Set a pixel in the display buffer.
 * 
 * @param x The x coordinate of the pixel (0 to SSD1306_WIDTH-1).
 * @param y The y coordinate of the pixel (0 to SSD1306_HEIGHT-1).
 * @param color 1 to set the pixel, 0 to clear it.
 */
void ssd1306_SetPixel(int16_t x, int16_t y, uint8_t color);

/**
 * @brief Set the cursor position for text rendering.
 * 
 * @param x The x coordinate (0 to SSD1306_WIDTH-1).
 * @param y The y coordinate (0 to (SSD1306_HEIGHT/8)-1).
 */
void ssd1306_SetCursor(uint8_t x, uint8_t y);

/**
 * @brief Render a character at the current cursor position.
 * 
 * @param c The character to render.
 */
void ssd1306_SetChar(char c);

/**
 * @brief Render a string at the current cursor position.
 * 
 * @param str The null-terminated string to render.
 */
void ssd1306_DemoAnimation(void);

#endif // _DISPLAY_H