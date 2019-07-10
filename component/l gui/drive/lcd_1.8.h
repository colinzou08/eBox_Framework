#ifndef __LCD_1_8_H
#define __LCD_1_8_H
/**
  ******************************************************************************
  * @file    lcd_1.8.h
  * @author  shentq
  * @version V1.2
  * @date    2016/08/14
  * @brief
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form
  * or means, without the prior written consent of shentq. This specification is
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#include "ebox_core.h"
#include "G_lcd_interface.h"

#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160

//����������eBox
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��
//              RES   ��PB3 (RST)
//              DC    ��PB4 (RS)
//              CS    ��PB5
//              BL    ��PB6

typedef enum
{
    ENABLE_BACK_COLOR = 0,
    DISABLE_BACK_COLOR = 1
} TEXT_MODE_TYPE;

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	    //��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111
class Lcd : public GAPI
{

public:
		Lcd(Gpio *cs, Gpio *led, Gpio *rs, Gpio *rst, Spi *spi,int16_t width,int16_t height):GAPI(width,height)
    {
        this->cs = cs;
        this->led = led;
        this->rs = rs;
        this->rst = rst;
        this->spi = spi;
    }
    void begin(void);
    void soft_reset(void);
    void clear(uint16_t Color);
    void on();
    void off();
    void column_order(uint8_t order);
    void row_order(uint8_t order);

    void set_xy(int16_t x, int16_t y);


    virtual void draw_pixel(int16_t x, int16_t y, E_COLOR color);
    virtual void draw_h_line(int16_t x0, int16_t y0, int16_t x1, E_COLOR color);
    virtual void draw_v_line(int16_t x0, int16_t y0, int16_t y1, E_COLOR color);
    virtual void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, E_COLOR color);
    virtual void fill_rect  (int16_t x0, int16_t y0,  int16_t x1, int16_t y1, E_COLOR color);
    virtual void fill_rect  (int16_t x0, int16_t y0,  int16_t x1, int16_t y1, uint16_t *bitmap);
    virtual void fill_screen(E_COLOR color);
    virtual void draw_circle(int16_t x, int16_t y, int16_t r, E_COLOR color);

private:
    Gpio *cs;
    Gpio *led;
    Gpio *rs;
    Gpio *rst;
    Spi  *spi;
    Spi::Config_t config;
    uint16_t width, height;
    uint8_t initialized;

    void reset(void);
    void init(void);
    void spi_write_data(uint8_t Data);
    void write_index(uint8_t Index);
    void write_data_8bit(uint8_t Data);
    void write_data_16bit(uint16_t Data);
    uint8_t read_8bit();
    int16_t read_16bit();

    void write_reg(uint8_t Index, uint8_t Data);
    uint8_t   read_reg(uint8_t Index);

    void set_region(int16_t x_start, int16_t y_start, int16_t x_end, int16_t y_end);

};
#endif