#include "CreateView.hpp"

#include <ncurses.h>

CreateView::CreateView()
{
    m_window = newwin(LINES, COLS, 0, 0);
    box(m_window, 0, 0);

    notimeout(m_window, true);
    curs_set(1); // make the cursor visible
}

void CreateView::render()
{
    mvwprintw(m_window, 1, 3, "Username: ");
    wrefresh(m_window);
}

const int CreateView::get_input()
{
    return wgetch(m_window);
}
