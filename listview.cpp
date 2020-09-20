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
/*
    for (auto line = 0; line < LINES; line++)
    {
        mvwprintw(m_window, line, 0, "%d", line);
    }
*/

    for (auto col = 1; col < COLS - 1; col++)
    {
        if (col % 10 == 0)
            mvwprintw(m_window, 0, col, "%d", col / 10);
        mvwprintw(m_window, 1, col, "%d", col % 10);
    }
}

void ListView::render()
{
    print_grid();
    print_header();
    render_list_header();
    render_list();
    wrefresh(m_window);
}

void ListView::render_list()
{
    for (auto i = 0; i < m_entries.size(); i++)
    {
        int col {0};
        mvwprintw(
            m_window,
            LIST_START_LINE + i,
            0,
            "%s",
            pad_entry_str(m_entries[i].get_username())
        );

        col += COL_BUFFER + COL_SIZE;
        mvwprintw(
            m_window,
            LIST_START_LINE + i,
            col,
            "%s",
            pad_entry_str(m_entries[i].get_password())
        );
    }
}

void ListView::render_list_header()
{
    // TODO should have functions for nth column
    int col {0};
    mvwprintw(
        m_window,
        LIST_HEADER_LINE,
        0,
        "Username"
    );

    col += COL_BUFFER + COL_SIZE;
    mvwprintw(
        m_window,
        LIST_HEADER_LINE,
        col,
        "Password"
    );
}

const char * ListView::pad_entry_str(std::string str)
{
    // TODO
    return str.c_str();
}

void ListView::print_header()
{
    const int starting_line {2};
    const int starting_col {(COLS / 2) - 3};

    wattron(m_window, COLOR_PAIR(RUBEUS_CYAN_BLACK));

    mvwprintw(m_window, starting_line, starting_col, "rubeus");

    wattroff(m_window, COLOR_PAIR(RUBEUS_CYAN_BLACK));
}

void ListView::notify(const std::vector<PasswordEntry>& entries)
{
    m_entries = entries;
}
