#ifndef MAIN_SH1106_H_
#define MAIN_SH1106_H_

#include "driver/i2c.h"
#include <i2c_types.h>

#define OLED_I2C_ADDRESS 0x3C

#define OLED_CONTROL_BYTE_CMD_SINGLE 0x80
#define OLED_CONTROL_BYTE_CMD_STREAM 0x00
#define OLED_CONTROL_BYTE_DATA_STREAM 0x40

#define OLED_CMD_NOP 0xE4

#define OLED_CMD_SET_CONTRAST 0x81

#define OLED_CMD_SET_LOWER_COLUMN_ADDR 0x02
#define OLED_CMD_SET_HIGH_COLUMN_ADDR 0x10

#define OLED_CMD_ENTIRE_DISPLAY_ON 0xA5
#define OLED_CMD_ENTIRE_DISPLAY_OFF 0xA4

#define OLED_CMD_DISPLAY_INVERT_NORMAL 0xA6
#define OLED_CMD_DISPLAY_INVERT_INVERTED 0xA7

#define OLED_CMD_SET_MULTIPLEX_RATIO 0xA8

#define OLED_CMD_DISPLAY_OFF 0xAE
#define OLED_CMD_DISPLAY_ON 0xAF

#define OLED_CMD_SET_DISPLAY_START_LINE 0x40

#define OLED_CMD_SET_SEGMENT_REMAP_INVERSE 0xA1
#define OLED_CMD_SET_SEGMENT_REMAP_NORMAL 0xA0

#define OLED_CMD_SET_COM_SCAN_MODE_REVERSE 0xC8
#define OLED_CMD_SET_COM_SCAN_MODE_NORMAL 0xC0

#define OLED_CMD_SET_DISPLAY_OFFSET 0xD3

#define OLED_CMD_SET_DISPLAY_CLK_DIV 0xD5
#define OLED_CMD_SET_PRECHARGE 0xD9

#define OLED_CMD_SET_COM_PIN_HW_CONFIG 0xDA

#define OLED_CMD_SSET_VCOMH_DESELCT 0xDB

#define OLED_CMD_SET_CHARGE_PUMP_SETTING 0x8D
#define OLED_CMD_SET_CHARGE_PUMP_CTRL 0xAD
#define OLED_CMD_SET_CHARGE_PUMP_ON 0x0B
#define OLED_CMD_SET_CHARGE_PUMP_OFF 0x0A

typedef enum {
    SCROLL_RIGHT = 1,
    SCROLL_LEFT = 2,
    SCROLL_DOWN = 3,
    SCROLL_UP = 4,
    PAGE_SCROLL_DOWN = 5,
    PAGE_SCROLL_UP = 6,
    SCROLL_STOP = 7
} sh1106_scroll_type_t;

typedef struct {
    uint8_t _segments[128];
} PAGE_t;

typedef struct {
    int _address;
    int _width;
    int _height;
    int _pages;
    int _dc;
    bool _scEnable;
    int _scStart;
    int _scEnd;
    int _scDirection;
    PAGE_t _page[8];
    bool _flip;
    i2c_port_t _i2c_num;
    i2c_master_bus_handle_t _i2c_bus_handle;
    i2c_master_dev_handle_t _i2c_dev_handle;
} SH1106_t;

void sh1106_init(SH1106_t* dev, int width, int height);
void sh1106_get_width(SH1106_t* dev);
void sh1106_get_height(SH1106_t* dev);
int sh1106_get_pages(SH1106_t * dev);
void sh1106_show_buffer(SH1106_t * dev);
void sh1106_set_buffer(SH1106_t * dev, const uint8_t * buffer);
void sh1106_get_buffer(SH1106_t * dev, uint8_t * buffer);
void sh1106_set_page(SH1106_t * dev, int page, const uint8_t * buffer);
void sh1106_get_page(SH1106_t * dev, int page, uint8_t * buffer);
void sh1106_display_image(SH1106_t * dev, int page, int seg, const uint8_t * images, int width);
void sh1106_display_text(SH1106_t * dev, int page, const char * text, int text_len, bool invert);
void sh1106_display_text_box1(SH1106_t * dev, int page, int seg, const char * text, int box_width, int text_len, bool invert, int delay);
void sh1106_display_text_box2(SH1106_t * dev, int page, int seg, const char * text, int box_width, int text_len, bool invert, int delay);
void sh1106_display_text_x3(SH1106_t * dev, int page, const char * text, int text_len, bool invert);
void sh1106_clear_screen(SH1106_t * dev, bool invert);
void sh1106_clear_line(SH1106_t * dev, int page, bool invert);
void sh1106_contrast(SH1106_t * dev, int contrast);
void sh1106_software_scroll(SH1106_t * dev, int start, int end);
void sh1106_scroll_text(SH1106_t * dev, const char * text, int text_len, bool invert);
void sh1106_scroll_clear(SH1106_t * dev);
void sh1106_hardware_scroll(SH1106_t * dev, sh1106_scroll_type_t scroll);
void sh1106_wrap_arround(SH1106_t * dev, sh1106_scroll_type_t scroll, int start, int end, int8_t delay);
void _sh1106_bitmaps(SH1106_t * dev, int xpos, int ypos, const uint8_t * bitmap, int width, int height, bool invert);
void sh1106_bitmaps(SH1106_t * dev, int xpos, int ypos, const uint8_t * bitmap, int width, int height, bool invert);
void _sh1106_pixel(SH1106_t * dev, int xpos, int ypos, bool invert);
void _sh1106_line(SH1106_t * dev, int x1, int y1, int x2, int y2,  bool invert);
void _sh1106_circle(SH1106_t * dev, int x0, int y0, int r, unsigned int opt, bool invert);
void _sh1106_disc(SH1106_t * dev, int x0, int y0, int r, unsigned int opt, bool invert);
void _sh1106_cursor(SH1106_t * dev, int x0, int y0, int r, bool invert);
void sh1106_invert(uint8_t *buf, size_t blen);
void sh1106_flip(uint8_t *buf, size_t blen);
uint8_t sh1106_copy_bit(uint8_t src, int srcBits, uint8_t dst, int dstBits);
uint8_t sh1106_rotate_byte(uint8_t ch1);
void sh1106_fadeout(SH1106_t * dev);
void sh1106_rotate_image(uint8_t *image, bool flip);
void sh1106_display_rotate_text(SH1106_t * dev, int seg, const char * text, int text_len, bool invert);
void sh1106_dump(SH1106_t dev);
void sh1106_dump_page(SH1106_t * dev, int page, int seg);


void i2c_master_init(SH1106_t * dev, int16_t sda, int16_t scl, int16_t reset);
void i2c_device_add(SH1106_t * dev, i2c_port_t i2c_num, int16_t reset, uint16_t i2c_address);
void i2c_init(SH1106_t * dev, int width, int height);
void i2c_display_image(SH1106_t * dev, int page, int seg, const uint8_t * images, int width);
void i2c_contrast(SH1106_t * dev, int contrast);
void i2c_hardware_scroll(SH1106_t * dev, sh1106_scroll_type_t scroll);


#endif