#include "colors.h"
#include "rubeus.h"

#include <iostream>

Rubeus::Rubeus()
{
    m_window = newwin(LINES, COLS, 0, 0);
    box(m_window, 0, 0);
}

Rubeus::~Rubeus()
{
    delwin(m_window);
}

void Rubeus::update()
{
    // TODO
}

// debug fn
void Rubeus::print_grid()
{
    for (auto line = 0; line < LINES; line++)
    {
        mvwprintw(m_window, line, 0, "%d", line);
    }

    for (auto col = 0; col < COLS; col++)
    {
        if (col % 10 == 0)
            mvwprintw(m_window, 0, col, "%d", col / 10);
        mvwprintw(m_window, 1, col, "%d", col % 10);
    }
}

void Rubeus::render()
{
    //print_grid();
    print_header();
    wrefresh(m_window);
}

void Rubeus::print_header()
{
    wattron(m_window, COLOR_PAIR(RUBEUS_CYAN_BLACK));
    mvwprintw(m_window, 2, (COLS / 2) - 3, "rubeus");
    wattroff(m_window, COLOR_PAIR(RUBEUS_CYAN_BLACK));
}

