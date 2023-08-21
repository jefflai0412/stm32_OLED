# stm32_OLED

## How to use
1. Configure the pin modes in the stm32CubeMX
    1. Set PA4 to GPIO_OUTPUT and name it OLED_DC
    2. Set PA8 to GPIO_OUTPUT and name it OLED_CS
    3. Set PB3 to GPIO_OUTPUT and name it OLED_CLK
    4. Set PB5 to GPIO_OUTPUT ane name it OLED_DIN
2. Includes
    1. include "OLED.h"
    2. include "ssd1306_fonts.h"
3. functions
    1. first use oled_init() to initialize the OLED
    2. use oled_dot(x, y) to display a single point on the oled.
    3. use oled_str(text, col, page, font_type) to display a string.
            

