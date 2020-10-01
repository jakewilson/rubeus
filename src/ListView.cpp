#include "colors.hpp"
#include "IModel.hpp"
#include "ListView.hpp"
#include "PasswordEntry.hpp"

#include <algorithm>
#include <sstream>

ListView::ListView(
    const std::vector<PasswordEntry> entries,
    int x,
    int y,
    int w,
    int h
) :
    IView(x, y, w, h),
    m_entries(entries),
    m_col_size(w / num_columns),
    m_num_visible_items(std::min(
        static_cast<int>(entries.size()),
        h - list_start_line
    ))
{
    box(m_window, 0, 0);

    curs_set(0); // make the cursor invisible

    m_list_start = 0;
    m_list_end = m_num_visible_items;
}

// debug fn
void ListView::print_grid() const
{
    for (auto line = m_y; line < m_y + m_h; line++)
    {
        mvwprintw(m_window, line, 0, "%d", line);
    }

    for (auto col = m_x; col < m_w + m_x; col++)
    {
        if (col % 10 == 0)
            mvwprintw(m_window, 0, col, "%d", col / 10);
        mvwprintw(m_window, 1, col, "%d", col % 10);
    }
}

void ListView::render()
{
    wclear(m_window);
    render_list_header();
    render_list();
    wrefresh(m_window);
}

void ListView::render_list() const
{
    for (auto i = m_list_start; i < m_list_end; i++)
    {
        auto y_pos = list_start_line + (i - m_list_start);
        render_nth_column(
            user_col,
            y_pos,
            pad_entry_str(m_entries[i].get_username())
        );
        render_nth_column(
            pass_col,
            y_pos,
            pad_entry_str(m_entries[i].get_password())
        );
        render_nth_column(
            title_col,
            y_pos,
            pad_entry_str(m_entries[i].get_title())
        );
        if (i == m_selected_entry)
        {
            wmove(m_window, y_pos, 0);
            wchgat(m_window, -1, A_STANDOUT, 0, NULL);
        }
    }
}

void ListView::render_list_header() const
{
    render_nth_column(title_col, list_header_line, "Title");
    render_nth_column(user_col, list_header_line, "Username");
    render_nth_column(pass_col, list_header_line, "Password");
}

void ListView::render_nth_column(
    int col_number,
    int line_number,
    const char * str
) const
{
    const int col = (col_buffer + m_col_size) * col_number;
    mvwprintw(m_window, line_number, col, str);
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
    if (str.length() > m_col_size)
    {
        str = str.substr(0, m_col_size - 3) + "...";
    }

    return str.c_str();
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
