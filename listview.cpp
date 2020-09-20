#include "colors.h"
#include "listview.h"

#include <iostream>

ListView::ListView(IModel *model) : m_model(model)
{
    m_model->register_list_observer(this);

    m_window = newwin(LINES, COLS, 0, 0);
    box(m_window, 0, 0);
}

ListView::~ListView()
{
    m_model->remove_list_observer(this);

    delwin(m_window);
}

void ListView::update()
{
    // TODO
}

// debug fn
void ListView::print_grid()
{
    for (auto line = 0; line < LINES; line++)
    {
        mvwprintw(m_window, line, 0, "%d", line);
    }

    for (auto col = 0; col < COLS - 1; col++)
    {
        if (col % 10 == 0)
            mvwprintw(m_window, 0, col, "%d", col / 10);
        mvwprintw(m_window, 1, col, "%d", col % 10);
    }
}

void ListView::render()
{
    //print_grid();
    print_header();
    wrefresh(m_window);
}

void ListView::print_header()
{
    const int starting_line = 2;
    const int starting_col = (COLS / 2) - 3;

    wattron(m_window, COLOR_PAIR(RUBEUS_CYAN_BLACK));

    mvwprintw(m_window, starting_line, starting_col, "rubeus");

    wattroff(m_window, COLOR_PAIR(RUBEUS_CYAN_BLACK));
}

void ListView::notify(const std::vector<PasswordEntry *>& entries)
{
    // TODO
}
