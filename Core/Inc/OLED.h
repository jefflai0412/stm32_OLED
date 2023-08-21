#include "main.h"

#define DATA(x) HAL_GPIO_WritePin(OLED_DIN_GPIO_Port, OLED_DIN_Pin, x? GPIO_PIN_SET : GPIO_PIN_RESET)
#define CLK(x)	HAL_GPIO_WritePin(OLED_CLK_GPIO_Port, OLED_CLK_Pin, x? GPIO_PIN_SET : GPIO_PIN_RESET)
#define CS(x)		HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, x? GPIO_PIN_SET : GPIO_PIN_RESET)
#define DC(x) 	HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, x? GPIO_PIN_SET : GPIO_PIN_RESET)


void oled_init(void);
void oled_RefreshGram(void);
void OLED_Clear(void);
void oled_write(uint8_t data);
void draw_dot(uint8_t x, uint8_t y);
void oled_char(uint8_t char_index, uint8_t col, uint8_t page, const uint8_t *font_type);
void oled_str(char * text, uint8_t col, uint8_t page, const uint8_t *font_type);


