#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <string.h>

const uint8_t COMMAND_BYTE = 0x80;
const uint8_t DATA_BYTE = 0x40;
const uint8_t OLED_ID = 0x3C;

/* fundamental command table */
const char SET_CONTRAST = 0x81;
const char DISPLAY_RESUME_RAM = 0xA4;
const char DISPLAY_IGNORE_RAM = 0xA5;
const char INVERT_FALSE = 0xA6;
const char INVERT_TRUE = 0xA7;
const char DISPLAY_SLEEP = 0xAE;
const char DISPLAY_ON = 0xAF;

/* scrolling command table */

/* address setting command table */
const char SET_LOW_COL = 0x0; // page addressing mode only
const char SET_HI_COL = 0x10; // page addressing mode only
const char SET_MEM_MODE =
    0x20; // 2 bytes; 0b - horizontal;  1b - vertical; 10b page addressing mode
const char SET_COL_ADDR = 0x21;   // 3 bytes; 0 - 127d start; 0 - 127d end
const char SET_PAGE_ADDR = 0x22;  // 3 bytes; 0 - 7d start; 0 - 7d end
const char SET_PAGE_START = 0xB0; // | 0-7d page addressing mode

/* hardware configuration command table */
const char SET_DISPLAY_START = 0x40; // | 0-63d
const char SET_SEG_REMAP =
    0xA0; // | 0 - col 0 map to seg0; 1 - col 127 mapped to seg0
const char SET_MULTIPLEX_RATIO = 0xA8; // 2 bytes; 15-63

void send_cmd(uint8_t data[], size_t len) {
  uint8_t *outdata = malloc(len * sizeof(uint8_t) * 2);
  for (int i = 0; i < len; i++) {
    outdata[i * 2] = COMMAND_BYTE;
    outdata[(i * 2) + 1] = data[i];
  }
  i2c_write_blocking(i2c_default, OLED_ID, outdata, 2 * len, false);
  free(outdata);
}

void send_data(uint8_t data[8][128]) {
  int outsize = 8 * 128 + 13;
  uint8_t *outdata = malloc(outsize);
  memcpy(outdata, DISPLAY_RESET, 13);
  for (int i = 0; i < 8; i++) {
    for (int k = 0; k < 128; k++) {
      outdata[13 + (i * 128) + k] = data[i][k];
    }
  }
  i2c_write_blocking(i2c_default, OLED_ID, outdata, outsize, false);
  free(outdata);
}

uint8_t DISPLAY_INIT[25] = {0xAE, 0x20, 0x00, 0x40, 0xA1, 0xA8, 0x3F,
                            0xC8, 0xD3, 0x00, 0xDA, 0x12, 0xD5, 0x80,
                            0xD9, 0xF1, 0xDB, 0x30, 0x81, 0xFF, 0xA4,
                            0xA6, 0x8D, 0x14, 0xAF};

const uint8_t DISPLAY_RESET[] = {COMMAND_BYTE, 0x21, COMMAND_BYTE, 0x0,
                                 COMMAND_BYTE, 0x7f, COMMAND_BYTE, 0x22,
                                 COMMAND_BYTE, 0x0,  COMMAND_BYTE, 0x7,
                                 DATA_BYTE};
