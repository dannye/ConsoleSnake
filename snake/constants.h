#include <Windows.h>

const int LEVEL_HEIGHT = 30;
const int LEVEL_WIDTH = 30;
const char ALL_DIRS[4] = { 'w', 'a', 's', 'd' };

// colors
const int WHITE     = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int RED       = FOREGROUND_RED   | FOREGROUND_INTENSITY;
const int GREEN     = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int BLUE      = FOREGROUND_BLUE  | FOREGROUND_INTENSITY;
