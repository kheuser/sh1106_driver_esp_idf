#ifndef MAIN_SH1106_H_
#define MAIN_SH1106_H_

#include "driver/i2c.h"

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
    i2c_port_t i2c_num;
#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 2, 0))
    i2c_master_bus_handle_t _i2c_bus_handle;
    i2c_master_dev_handle_t _i3c_dev_handle;
} SH1106_t;

void sh1106_init(SH1106_t* dev, int width, int height);



#endif