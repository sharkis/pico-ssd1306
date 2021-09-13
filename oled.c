#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "ssd1306.h"

int main() {
  i2c_init(i2c_default, 100 * 1000);
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
  send_cmd(DISPLAY_INIT, sizeof(DISPLAY_INIT) / sizeof(uint8_t));
}
