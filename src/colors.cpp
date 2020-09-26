#include "colors.hpp"

void init_colors()
{
    start_color();

    init_pair(RUBEUS_RED_BLACK, COLOR_RED,   COLOR_BLACK);
    init_pair(RUBEUS_BLACK_RED, COLOR_BLACK, COLOR_RED);

    init_pair(RUBEUS_GREEN_BLACK, COLOR_GREEN,   COLOR_BLACK);
    init_pair(RUBEUS_BLACK_GREEN, COLOR_BLACK,   COLOR_GREEN);

    init_pair(RUBEUS_CYAN_BLACK, COLOR_CYAN,   COLOR_BLACK);
    init_pair(RUBEUS_BLACK_CYAN, COLOR_BLACK,  COLOR_CYAN);

    init_pair(RUBEUS_MAGENTA_BLACK, COLOR_MAGENTA,   COLOR_BLACK);
    init_pair(RUBEUS_BLACK_MAGENTA, COLOR_BLACK,     COLOR_MAGENTA);

    init_pair(RUBEUS_BLUE_BLACK, COLOR_BLUE,   COLOR_BLACK);
    init_pair(RUBEUS_BLACK_BLUE, COLOR_BLACK,  COLOR_BLUE);

    init_pair(RUBEUS_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);

}
