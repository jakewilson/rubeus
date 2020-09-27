#pragma once

#include "IListObserver.hpp"
#include "IView.hpp"

#include <ncurses.h>
#include <vector>

#define NUM_RUBEUS_COLS 4
#define COL_OFFSET 3
#define COL_SIZE (COLS - (2 * COL_OFFSET)) / NUM_RUBEUS_COLS
#define COL_BUFFER 2

#define RUBEUS_COL_START COL_OFFSET

#define LIST_HEADER_LINE 4
#define LIST_START_LINE  5

#define USER_COL    0
#define PASS_COL    1
#define WEBSITE_COL 2

class IModel;
class PasswordEntry;

class ListView : public IListObserver, public IView
{
public:
    ListView(IModel *model);
    ~ListView();

    void render() override;
    const int get_input() override;
    void render_list() const;
    void render_list_header() const;
    void render_nth_column(int, int, const char *) const;
    void render_selected_entry() const;
    void render_n_spaces(int) const;
    const char * pad_entry_str(std::string) const;
    void print_grid() const;

    void selected_entry_up();
    void selected_entry_down();

    virtual void notify(const std::vector<PasswordEntry>&) override;

private:
    WINDOW *m_window;
    IModel *m_model;

    std::vector<PasswordEntry> m_entries {};
    int m_selected_entry {0};

    void print_header() const;
};
