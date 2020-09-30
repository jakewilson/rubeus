#include "colors.hpp"
#include "IModel.hpp"
#include "ListView.hpp"
#include "PasswordEntry.hpp"

#include <algorithm>
#include <sstream>

ListView::ListView(
    const std::vector<PasswordEntry> entries,
    int window_height
) : m_entries(entries),
    m_window_height(window_height),
    m_num_visible_items(std::min(
        static_cast<int>(entries.size()),
        window_height - LIST_START_LINE
    ))
{
    m_window = newwin(m_window_height, COLS, 0, 0);
    box(m_window, 0, 0);

    curs_set(0); // make the cursor invisible

    m_list_start = 0;
    m_list_end = m_num_visible_items;
}

ListView::~ListView()
{
    delwin(m_window);
}

// debug fn
void ListView::print_grid() const
{
    for (auto line = 0; line < LINES; line++)
    {
        mvwprintw(m_window, line, 0, "%d", line);
    }

    for (auto col = 1; col < COLS - 1; col++)
    {
        if (col % 10 == 0)
            mvwprintw(m_window, 0, col, "%d", col / 10);
        mvwprintw(m_window, 1, col, "%d", col % 10);
    }
}

void ListView::render()
{
    wclear(m_window);
    print_header();
    render_list_header();
    render_list();
    wrefresh(m_window);
}

void ListView::render_list() const
{
    for (auto i = m_list_start; i < m_list_end; i++)
    {
        auto y_pos = LIST_START_LINE + (i - m_list_start);
        if (i == m_selected_entry)
        {
            render_selected_entry(y_pos);
            continue;
        }

        render_nth_column(
            USER_COL,
            y_pos,
            pad_entry_str(m_entries[i].get_username())
        );
        render_nth_column(
            PASS_COL,
            y_pos,
            pad_entry_str(m_entries[i].get_password())
        );
        render_nth_column(
            TITLE_COL,
            y_pos,
            pad_entry_str(m_entries[i].get_title())
        );
    }
}

void ListView::render_list_header() const
{
    render_nth_column(TITLE_COL, LIST_HEADER_LINE, "Title");
    render_nth_column(USER_COL, LIST_HEADER_LINE, "Username");
    render_nth_column(PASS_COL, LIST_HEADER_LINE, "Password");
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

void ListView::render_selected_entry(int y_pos) const
{
    wattron(m_window, COLOR_PAIR(RUBEUS_BLACK_WHITE));
    const auto& username = pad_entry_str(m_entries[m_selected_entry].get_username());
    const auto& password = pad_entry_str(m_entries[m_selected_entry].get_password());
    const auto& title =  pad_entry_str(m_entries[m_selected_entry].get_title());

    render_nth_column(
        TITLE_COL,
        y_pos,
        title
    );
    render_n_spaces(COL_SIZE - strlen(title) + COL_BUFFER);
    render_nth_column(
        USER_COL,
        y_pos,
        username
    );
    render_n_spaces(COL_SIZE - strlen(username) + COL_BUFFER);
    render_nth_column(
        PASS_COL,
        y_pos,
        password
    );
    render_n_spaces(COL_SIZE - strlen(password) + COL_BUFFER);
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

void ListView::selected_entry_up()
{
    if (m_selected_entry == m_list_start && m_selected_entry > 0)
    {
        m_list_end--;
        m_list_start--;
        m_selected_entry = m_list_start;
    }
    else if (m_selected_entry == 0)
    {
        m_list_end = m_entries.size();
        m_list_start = m_list_end - m_num_visible_items;
        m_selected_entry = m_list_end - 1;
    }
    else
    {
        m_selected_entry--;
    }
}

void ListView::selected_entry_down()
{
    m_selected_entry++;
    if (m_selected_entry == m_list_end && m_selected_entry < m_entries.size())
    {
        m_list_start++;
        m_list_end++;
    }
    else if (m_selected_entry == m_entries.size())
    {
        m_selected_entry = 0;
        m_list_start = 0;
        m_list_end = m_num_visible_items;
    }
}

const int ListView::get_input()
{
    return wgetch(m_window);
}
