#include "main.h"
#include "OLED.h"
#include "ssd1306_fonts.h"
#include <string.h>

volatile static uint8_t oledGram[128][8];


void send_OneByte(uint8_t data)  // msb first  // data[0]->data[7]
{
	for (uint8_t i = 0; i < 8; i++)
	{
		CLK(0);
		DATA((data >> (7 - i)) & 0x01);  // SEND THE DATA
		CLK(1);
  }
}

void send_command(uint8_t command)
{
	DC(0);
	CS(0);  
	send_OneByte(command);
	CS(1);
	DC(1);
}

void send_data(uint8_t data)
{
	DC(1);
	CS(0);
	send_OneByte(data);
	CS(1);
	DC(1);
}

void oled_RefreshGram(void)
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		send_command(0xb0+i); 
		send_command(0x02);   
		send_command(0x10);   
		for(n=0;n<128;n++)
			send_data(oledGram[n][i]); 
	}   
} 

void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)     
		for(n=0;n<128;n++)
			oledGram[n][i] = 0;
	
	oled_RefreshGram();//更新显示
}

void oled_init(void)
{
  send_command(0xAE);  //关闭显示
	send_command(0x02);  //---set low column address
	send_command(0x10);  //---set high column address
	send_command(0x40);  //设置显示开始行[5:0](0x00~0x3F)
	send_command(0x81);  //对比度设置
	send_command(0xCF);   // Set SEG Output Current Brightness
	send_command(0xA1);  //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	send_command(0xC8);  //Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	send_command(0xA6);  //--set normal display
	send_command(0xA8);  //--set multiplex ratio(1 to 64)
  send_command(0x3f);  //--1/64 duty
  send_command(0xD3);  //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  send_command(0x00);  //-not offset
	send_command(0xd5);  //设置时钟分频因子，震荡频率
	send_command(0x80);  //[3:0],分频因子;[7:4],震荡频率
	send_command(0xD9);  //--set pre-charge period
	send_command(0xF1);  //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  send_command(0xDA);  //--set com pins hardware configuration
  send_command(0x12);  
  send_command(0xDB);  //--set vcomh
  send_command(0x40);  //Set VCOM Deselect Level
  send_command(0x20);  //-Set Page Addressing Mode (0x00/0x01/0x02)
	send_command(0x02);  //
  send_command(0x8D);  //--set Charge Pump enable/disable
	send_command(0x14);  //--set(0x10) disable
	send_command(0xA4);  // Disable Entire Display On (0xa4/0xa5)
	send_command(0xA6);  // Disable Inverse Display On (0xa6/a7) 
	send_command(0xAF);  //--turn on oled panel
	
	send_command(0xAF);  /*display ON*/     
	OLED_Clear();             
							 
	HAL_Delay(100);
}


void oled_dot(uint8_t x, uint8_t y)
{
	if (x>127 ||y>63) return;
	oledGram[x][y/8] |= 0x01 << y%8;
}		

void oled_char(uint8_t char_index, uint8_t col, uint8_t page, const uint8_t *font_type)
{
	uint8_t font_width = font_type[1];  
	uint8_t font_height = font_type[2]; 
	for (uint8_t i=0; i<font_width; i++)
	{
		for(uint8_t j=0; j<font_height/8; j++) 
		{
			oledGram[col+i][page+j] = font_type[4+(char_index*font_width*font_height / 8)+ i+j*font_width];  // had to skip 4
		}
	}
}

void oled_str(char * text, uint8_t col, uint8_t page, const uint8_t *font_type)
{
	uint8_t font_width = font_type[1];
	uint8_t font_height = font_type[2];
	for(uint8_t i=0; i<strlen(text); i++) 
	{
		char chr = text[i];
		uint8_t char_index = chr - ' ';
		if (col+font_width >= 128)
		{
			col = 0;
			page += font_height / 8;
		}
		if (chr == '\n')
		{
			col = 0;
			page += font_height / 8;
			continue;
		}
		
		oled_char(char_index, col, page, font_type);
		col += font_width; 
	}
}	