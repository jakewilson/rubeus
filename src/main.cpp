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
    init();

    Rubeus rubeus{};
    rubeus.run();

    kill();
    return 0;
}
