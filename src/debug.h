#pragma once

#define DEBUG

#ifdef DEBUG
static char _debug_buffer[512];
#define debug(fmt, args ...)  do {sprintf(_debug_buffer, "[%s:%d]: " fmt "\n\r", __PRETTY_FUNCTION__, __LINE__, ## args); Serial.print(_debug_buffer);} while(0)
#else
#define debug(fmt, args ...)
#endif