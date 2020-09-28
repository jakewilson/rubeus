#include "colors.hpp"
#include "CreateView.hpp"

#include <string>
#include <ncurses.h>



CreateView::CreateView() : m_focus(Focus::title)
{
    m_window = newwin(LINES, COLS, 0, 0);
    box(m_window, 0, 0);

    notimeout(m_window, true);
    curs_set(1); // make the cursor visible
}

void CreateView::render()
{
    wclear(m_window);

    render_header();
    mvwprintw(
        m_window,
        TITLE_Y,
        TITLE_X,
        "%s%s", TITLE_LABEL, m_title.c_str()
    );
    mvwprintw(
        m_window,
        USERNAME_Y,
        USERNAME_X,
        "%s%s", USERNAME_LABEL, m_username.c_str()
    );
    mvwprintw(
        m_window,
        PASSWORD_Y,
        PASSWORD_X,
        "%s%s", PASSWORD_LABEL, m_password.c_str()
    );

    place_cursor();
    wrefresh(m_window);
}

void CreateView::place_cursor()
{
    switch (m_focus)
    {
        case Focus::title:
            wmove(m_window, TITLE_Y, TITLE_CURSOR_X + m_title.length());
            break;
        case Focus::username:
            wmove(m_window, USERNAME_Y, USERNAME_CURSOR_X + m_username.length());
            break;
        case Focus::password:
            wmove(m_window, PASSWORD_Y, PASSWORD_CURSOR_X + m_password.length());
            break;
    }
}

const int CreateView::get_input()
{
    return wgetch(m_window);
}

void CreateView::render_header() const
{
    const char *header_str = "Create a new password";
    wattron(m_window, COLOR_PAIR(RUBEUS_CYAN_BLACK));
    mvwprintw(m_window, 1, (COLS / 2) - strlen(header_str) / 2, header_str);
    wattroff(m_window, COLOR_PAIR(RUBEUS_CYAN_BLACK));
}

void CreateView::move_cursor_right()
{
    int x = 0, y = 0;
    getyx(m_window, y, x);
    wmove(m_window, y, x + 1);
}

void CreateView::move_cursor_left()
{
    int x = 0, y = 0;
    getyx(m_window, y, x);
    wmove(m_window, y, x - 1);
}

std::string& CreateView::get_focus_str()
{
    switch (m_focus)
    {
        case Focus::title:
            return m_title;
        case Focus::username:
            return m_username;
        case Focus::password:
            return m_password;
    }
}

void CreateView::add_char(const char c)
{
    auto& focus = get_focus_str();
    focus += c;
}

void CreateView::remove_char()
{
    auto& focus = get_focus_str();
    if (focus.length() == 0)
        return;

    focus.erase(focus.end() - 1);
}

void CreateView::next_focus()
{
    switch (m_focus)
    {
        case Focus::title:
            m_focus = Focus::username;
            break;
        case Focus::username:
            m_focus = Focus::password;
            break;
        case Focus::password:
            // nothing to do?
            break;
    }
}

void CreateView::prev_focus()
{
    switch (m_focus)
    {
        case Focus::title:
            // nothing to do
            break;
        case Focus::username:
            m_focus = Focus::title;
            break;
        case Focus::password:
            m_focus = Focus::username;
            break;
    }
}

const Focus CreateView::get_focus() const
{
    return m_focus;
}
