#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_err.h"

#include "sh1106.h"
#include "font8x8_basic.h"

typedef union out_column_t {
    uint32_t u32;
    uint8_t u8[4];
} PACK8;

void sh1106_init(SH1106_t* dev, int width, int height)
{
    i2c_init(dev, width, height);
    for(int i = 0; i < dev->_pages; i++)
    {
        memset(dev->_page[i]._segments, 0, 128);
    }
}

void sh1106_get_width(SH1106_t* dev)
{
    return dev->_width;
}

void sh1106_get_height(SH1106_t* dev)
{
    return dev->_height;
}

int sh1106_get_pages(SH1106_t * dev)
{
    return dev->_pages;
}

void sh1106_show_buffer(SH1106_t * dev)
{
    for(int page = 0; page < dev->_pages; page++)
    {
        i2c_display_image(dev, page, 0, dev->_page[page]._segments, dev->_width);
    }
}

void sh1106_set_buffer(SH1106_t * dev, const uint8_t * buffer)
{
    int index = 0;
    for(int page = 0; page < dev->_pages; page++)
    {
        memcpy(&dev->_page[page]._segments, &buffer[index, 128]);
        index = index + 128;
    }
}

void sh1106_get_buffer(SH1106_t * dev, uint8_t * buffer)
{
    int index = 0;
    for(int page = 0; page < dev->_pages; page++)
    {
        memcpy(&buffer[index], &dev->_page[page]._segments, 128);
        index = index + 128;
    }
}

void sh1106_set_page(SH1106_t * dev, int page, const uint8_t * buffer)
{
    memcpy(&dev->_page[page]._segments, buffer, 128);
}

void sh1106_get_page(SH1106_t * dev, int page, uint8_t * buffer)
{
    memcpy(buffer, &dev->_page[page]._segments, 128);
}

void sh1106_display_image(SH1106_t * dev, int page, int seg, const uint8_t * images, int width)
{
    i2c_display_image(dev, page, seg, images, width);
    memcpy(&dev->_page[page]._segments[seg], images, width);
}

void sh1106_display_text(SH1106_t * dev, int page, const char * text, int text_len, bool invert)
{
    if(page >= dev->_pages) return;
    int _text_len = text_len;
    if(_text_len > 16) _text_len = 16;
    int seg = 0;
    uint8_t image[8];
    for(int i = 0; i < _text_len; i++)
    {
        memcpy(image, font8x8_basic_tr[(uint8_t)text[i]], 8);
        if(invert) sh1106_invert(image, 8);
        if(dev->_flip) sh1106_flip(image, 8);
        sh1106_display_image(dev, page, seg, image, 8);
        seg = seg + 8;
    }
}

void sh1106_display_text_box1(SH1106_t * dev, int page, int seg, const char * text, int box_width, int text_len, bool invert, int delay)
{

}

void sh1106_display_text_box2(SH1106_t * dev, int page, int seg, const char * text, int box_width, int text_len, bool invert, int delay)
{

}

void sh1106_display_text_x3(SH1106_t * dev, int page, const char * text, int text_len, bool invert)
{

}

void sh1106_clear_screen(SH1106_t * dev, bool invert)
{

}

void sh1106_clear_line(SH1106_t * dev, int page, bool invert)
{

}

void sh1106_contrast(SH1106_t * dev, int contrast)
{

}

void sh1106_software_scroll(SH1106_t * dev, int start, int end)
{

}

void sh1106_scroll_text(SH1106_t * dev, const char * text, int text_len, bool invert)
{

}

void sh1106_scroll_clear(SH1106_t * dev)
{

}

void sh1106_hardware_scroll(SH1106_t * dev, sh1106_scroll_type_t scroll)
{

}

void sh1106_wrap_arround(SH1106_t * dev, sh1106_scroll_type_t scroll, int start, int end, int8_t delay)
{

}

void _sh1106_bitmaps(SH1106_t * dev, int xpos, int ypos, const uint8_t * bitmap, int width, int height, bool invert)
{

}

void sh1106_bitmaps(SH1106_t * dev, int xpos, int ypos, const uint8_t * bitmap, int width, int height, bool invert)
{

}

void _sh1106_pixel(SH1106_t * dev, int xpos, int ypos, bool invert)
{

}

void _sh1106_line(SH1106_t * dev, int x1, int y1, int x2, int y2,  bool invert)
{

}

void _sh1106_circle(SH1106_t * dev, int x0, int y0, int r, unsigned int opt, bool invert)
{

}

void _sh1106_disc(SH1106_t * dev, int x0, int y0, int r, unsigned int opt, bool invert)
{

}

void _sh1106_cursor(SH1106_t * dev, int x0, int y0, int r, bool invert)
{

}

void sh1106_invert(uint8_t *buf, size_t blen)
{

}

void sh1106_flip(uint8_t *buf, size_t blen)
{

}

uint8_t sh1106_copy_bit(uint8_t src, int srcBits, uint8_t dst, int dstBits)
{

}

uint8_t sh1106_rotate_byte(uint8_t ch1)
{

}

void sh1106_fadeout(SH1106_t * dev)
{

}

void sh1106_rotate_image(uint8_t *image, bool flip)
{

}

void sh1106_display_rotate_text(SH1106_t * dev, int seg, const char * text, int text_len, bool invert)
{

}

void sh1106_dump(SH1106_t dev)
{

}

void sh1106_dump_page(SH1106_t * dev, int page, int seg)
{

}
