#include "colors.hpp"
#include "Rubeus.hpp"
#include "RubeusCommand.hpp"

#include <iostream>
#include <ncurses.h>

void init()
{
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    refresh(); // not sure why this is needed
    init_colors();
}

void kill()
{
    endwin();
}

int main()
{
    // TODO add arg for private key
    // TODO add arg for file (?)
    // TODO check for # rows and cols
    init();

    Rubeus rubeus{};
    rubeus.run();

    kill();
    return 0;
}
