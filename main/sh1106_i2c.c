#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#include "sh1106.h"

#define TAG "SH1106"

#if CONFIG_I2C_PORT_0
#define I2C_NUM I2C_NUM_0
#elif CONFIG_I2C_PORT_1
#define I2C_NUM I2C_NUM_1
#else
#define I2C_NUM I2C_NUM_0
#endif

#define I2C_MASTER_FREQ_HZ 400000 // I2C clock of SH1106 can run at 400 kHz max
#define I2C_TICKS_TO_WAIT 100 // Maximum ticks to wait before issuing a timeout

void i2c_master_init(SH1106_t * dev, int16_t sda, int16_t scl, int16_t reset)
{
    // ESP_LOGI(TAG, "New I2C driver in use");
    i2c_master_bus_config_t i2c_master_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .i2c_port = I2C_NUM,
        .scl_io_num = scl,
        .sda_io_num = sda,
        .flags .enable_internal_pullup = true
    };
    i2c_master_bus_handle_t i2c_bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_master_bus_config, &i2c_bus_handle));

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = OLED_I2C_ADDRESS,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ
    };
    i2c_master_dev_handle_t i2c_dev_handle;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(i2c_bus_handle, &dev_cfg, &i2c_dev_handle));

    if(reset > 0)
    {
        gpio_reset_pin(reset);
        gpio_set_direction(reset, GPIO_MODE_OUTPUT);
        gpio_set_level(reset, 0);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_set_level(reset, 1);
    }

    dev->_address = OLED_I2C_ADDRESS;
    dev->_flip = false;
    dev->_i2c_num = I2C_NUM;
    dev->_i2c_bus_handle = i2c_bus_handle;
    dev->_i2c_dev_handle = i2c_dev_handle;
}

void i2c_device_add(SH1106_t * dev, i2c_port_t i2c_num, int16_t reset, uint16_t i2c_address)
{
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = OLED_I2C_ADDRESS,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ
    };
    i2c_master_dev_handle_t i2c_dev_handle;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(dev->_i2c_bus_handle, &dev_cfg, &i2c_dev_handle));
    if(reset >= 0)
    {
        gpio_reset_pin(reset);
		gpio_set_direction(reset, GPIO_MODE_OUTPUT);
		gpio_set_level(reset, 0);
		vTaskDelay(50 / portTICK_PERIOD_MS);
		gpio_set_level(reset, 1);
    }

    dev->_address = i2c_address;
    dev->_flip = false;
    dev->_i2c_num = i2c_num;
    dev->_i2c_dev_handle = i2c_dev_handle;
}

void i2c_init(SH1106_t * dev, int width, int height)
{
    
}

void i2c_display_image(SH1106_t * dev, int page, int seg, const uint8_t * images, int width)
{

}

void i2c_contrast(SH1106_t * dev, int contrast)
{

}

void i2c_hardware_scroll(SH1106_t * dev, sh1106_scroll_type_t scroll)
{

}