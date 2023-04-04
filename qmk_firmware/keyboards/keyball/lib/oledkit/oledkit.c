/*
Copyright 2021 @Yowkees
Copyright 2021 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

#if defined(OLED_ENABLE) && !defined(OLEDKIT_DISABLE)

// clang-format off
static const char PROGMEM logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0};
// clang-format on

// redgosho
static const char PROGMEM redgosho[] ={
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xe0, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xe0, 0xf0, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xfc, 0xfc, 0x18, 0x08, 0x04, 0x0c, 0x1c,
  0x18, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0x08, 0x04, 0x04, 0x04, 0x04, 0x8c, 0xf8, 0xf0, 0xe0, 0x00,
  0x00, 0xc0, 0xf0, 0xf8, 0x18, 0x0c, 0x04, 0x04, 0x0c, 0x08, 0x18, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x20, 0xf8, 0xf8, 0x0c, 0x04, 0x04, 0x04, 0x0c, 0xf8, 0xf8, 0x64, 0x0c, 0x0c, 0x00, 0x80,
  0xe0, 0xf0, 0x18, 0x0c, 0x04, 0x04, 0x04, 0x0c, 0x1c, 0x78, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x70,
  0xf8, 0xec, 0xc4, 0x84, 0x84, 0x84, 0x0c, 0x1c, 0x10, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
  0x08, 0x08, 0x0c, 0x0c, 0x0c, 0x3c, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x38, 0x08,
  0x04, 0x04, 0x04, 0x0c, 0x0c, 0x38, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x7f, 0x7f, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x31, 0x61, 0x61, 0x61, 0x41, 0x61, 0x21, 0x31, 0x00, 0x00,
  0x00, 0x07, 0x1f, 0x3f, 0x30, 0x60, 0x60, 0x40, 0x60, 0x20, 0x30, 0x7f, 0x7f, 0x20, 0x00, 0x00,
  0x00, 0xc8, 0xfc, 0x3f, 0x1b, 0x1b, 0x1a, 0x1b, 0x19, 0x19, 0x30, 0xf0, 0xf0, 0xc0, 0x00, 0x03,
  0x0f, 0x1f, 0x38, 0x30, 0x60, 0x40, 0x40, 0x40, 0x20, 0x38, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0x38,
  0x30, 0x61, 0x41, 0x41, 0x43, 0x63, 0x67, 0x3f, 0x3e, 0x00, 0x00, 0x00, 0x40, 0x7f, 0x7f, 0x7f,
  0x40, 0x00, 0x00, 0x00, 0x00, 0x60, 0x7f, 0x7f, 0x40, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0x3e, 0x30,
  0x60, 0x40, 0x40, 0x40, 0x60, 0x30, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0x03, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// マウスLayer
static const char PROGMEM mouse[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x40, 0x60, 0x20, 0x20, 0x60, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0,
  0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
  0xc0, 0x00, 0x10, 0xf0, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x30, 0x38, 0x18, 0x18, 0x18, 0x18, 0x30,
  0x70, 0xe0, 0xe0, 0x70, 0x30, 0x30, 0x30, 0x70, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x01, 0x03, 0x03, 0xe1, 0xfc, 0x06,
  0x03, 0x01, 0x01, 0x01, 0x03, 0x06, 0xf8, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xf0, 0x1c, 0x06, 0x02, 0x1e, 0x1e, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0xc1, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x81, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0,
  0x33, 0x5e, 0x58, 0x1f, 0x1f, 0x1f, 0x19, 0x18, 0x18, 0x00, 0x10, 0x38, 0x78, 0x30, 0x30, 0x00,
  0x00, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0x38, 0x18, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1c, 0x18, 0x38, 0x30, 0x71, 0x7f, 0x78,
  0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x7f, 0x70, 0x70, 0xff, 0x78, 0x70, 0x70, 0x70, 0x70, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x1e, 0x38, 0x70, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0xc0, 0xc0, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0xc7, 0x37, 0x0f, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff,
  0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f,
  0xcc, 0x7a, 0x1a, 0xf8, 0xf8, 0xf8, 0x98, 0x18, 0x18, 0x00, 0x04, 0x0e, 0x0e, 0x0e, 0x04, 0x00,
  0x00, 0x0c, 0x0c, 0x0e, 0x0f, 0x0f, 0x1c, 0x18, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03,
  0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07,
  0x0c, 0x0f, 0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
  0x03, 0x00, 0x08, 0x0f, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x0c, 0x0c, 0x18, 0x18, 0x18, 0x18, 0x0c,
  0x0e, 0x07, 0x07, 0x06, 0x0c, 0x0c, 0x0c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__attribute__((weak)) void oledkit_render_logo_user(void) {
    oled_write_P(logo, false);
}

__attribute__((weak)) void oledkit_render_mouse(void) {
    oled_write_raw_P(mouse, sizeof(mouse));
}

__attribute__((weak)) void oledkit_render_redgosho(void) {
    oled_write_raw_P(redgosho, sizeof(redgosho));
}

__attribute__((weak)) void oledkit_render_info_user(void) {
    oled_write_P(logo, false);
}

__attribute__((weak)) bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // レイヤー4にいるかどうかをチェック
        if (get_highest_layer(layer_state) == 4) {
            // レイヤー4にいる場合、layer4_imageを表示
            oledkit_render_mouse();
        } else {
            oledkit_render_info_user();
        }
    } else {
            oledkit_render_redgosho();

    }
    return true;
}

__attribute__((weak)) oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return !is_keyboard_master() ? OLED_ROTATION_180 : rotation;
}

#endif // OLED_ENABLE
