/**

 */
#include "colors.h"
#include "listview.h"
#include "model.h"

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

void run()
{
    int c {0};
    Model model {};
    ListView list_view {&model};

    while (c != 'q')
    {
        list_view.render();
        c = getch();
    }
}

int main()
{
    // TODO add arg for private key
    // TODO add arg for file (?)
    // TODO check for # rows and cols
    init();
    run();
    kill();
    return 0;
}
