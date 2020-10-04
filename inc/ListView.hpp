#pragma once

#include "IListObserver.hpp"
#include "IView.hpp"

#include <ncurses.h>
#include <vector>

class PasswordEntry;

constexpr int list_header_line = 0;
constexpr int list_start_line = 1;
constexpr int num_columns = 3;
constexpr int col_buffer = 2;

constexpr int title_col = 0;
constexpr int user_col = 1;
constexpr int pass_col = 2;

constexpr int list_view_start_col = 1;

class ListView : public IView
{
public:
    ListView(int, int, int, int, const std::vector<PasswordEntry>);
    ~ListView() {}

    void render() override;
    const int get_input() override;

    void selected_entry_up();
    void selected_entry_down();

private:
    int m_list_start;
    int m_list_end;
    const int m_num_visible_items;

    const int m_col_size;

    const std::vector<PasswordEntry> m_entries;
    int m_selected_entry {0};

    void render_list() const;
    void render_list_header() const;
    void render_nth_column(int, int, const char *) const;
    void render_n_spaces(int) const;
    const char * pad_entry_str(std::string) const;
    void print_grid() const;
};
