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
void ListView::print_grid() const
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
    //print_grid();
    print_header();
    render_list_header();
    render_list();
    wrefresh(m_window);
}

void ListView::render_list() const
{
    for (auto i = 0; i < m_entries.size(); i++)
    {
        if (i == m_selected_entry)
        {
            render_selected_entry();
            continue;
        }

        render_nth_column(
            USER_COL,
            LIST_START_LINE + i,
            pad_entry_str(m_entries[i].get_username())
        );
        render_nth_column(
            PASS_COL,
            LIST_START_LINE + i,
            pad_entry_str(m_entries[i].get_password())
        );
        render_nth_column(
            WEBSITE_COL,
            LIST_START_LINE + i,
            pad_entry_str(m_entries[i].get_website())
        );
    }
}

void ListView::render_list_header() const
{
    render_nth_column(USER_COL, LIST_HEADER_LINE, "Username");
    render_nth_column(PASS_COL, LIST_HEADER_LINE, "Password");
    render_nth_column(WEBSITE_COL, LIST_HEADER_LINE, "Website");
}

void ListView::render_nth_column(
    int col_number,
    int line_number,
    const char * str
) const
{
    const int col = RUBEUS_COL_START + ((COL_BUFFER + COL_SIZE) * col_number);
    mvwprintw(m_window, line_number, col, str);
}

void ListView::render_selected_entry() const
{
    wattron(m_window, COLOR_PAIR(RUBEUS_BLACK_WHITE));
    const auto& username = pad_entry_str(m_entries[m_selected_entry].get_username());
    const auto& password = pad_entry_str(m_entries[m_selected_entry].get_password());
    const auto& website =  pad_entry_str(m_entries[m_selected_entry].get_website());

    render_nth_column(
        USER_COL,
        LIST_START_LINE + m_selected_entry,
        username
    );
    render_n_spaces(COL_SIZE - strlen(username) + COL_BUFFER);
    render_nth_column(
        PASS_COL,
        LIST_START_LINE + m_selected_entry,
        password
    );
    render_n_spaces(COL_SIZE - strlen(password) + COL_BUFFER);
    render_nth_column(
        WEBSITE_COL,
        LIST_START_LINE + m_selected_entry,
        website
    );
    wattroff(m_window, COLOR_PAIR(RUBEUS_BLACK_WHITE));
}

void ListView::render_n_spaces(int n) const
{
    for (int i = 0; i < n; i++)
    {
        wprintw(m_window, " ");
    }
}

const char * ListView::pad_entry_str(std::string str) const
{
    if (str.length() > COL_SIZE)
    {
        str = str.substr(0, COL_SIZE - 3) + "...";
    }

    return str.c_str();
}

void ListView::print_header() const
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
