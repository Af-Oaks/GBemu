#pragma once

#include <common.h>

static const int SCREEN_WIDTH = 1024;
static const int SCREEN_HEIGHT = 768;

void ui_init();
void ui_handle_events();
void ui_update();
void ui_on_key(bool down, u32 key_code);
void ui_close();
void update_dbg_window();