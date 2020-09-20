#pragma once

#include "IListObserver.h"
#include "IModel.h"
#include "passwordentry.h"

#include <ncurses.h>
#include <vector>

#define NUM_RUBEUS_COLS 4
#define COL_OFFSET 3
#define COL_SIZE (COLS - (2 * COL_OFFSET)) / NUM_RUBEUS_COLS
#define COL_BUFFER 1

#define RUBEUS_COL_START COL_OFFSET

#define LIST_HEADER_LINE 4
#define LIST_START_LINE  5

class ListView : public IListObserver
{
public:
    ListView(IModel *model);
    ~ListView();

    void update();
    void render();
    void render_list();
    void render_list_header();
    const char * pad_entry_str(std::string);
    void print_grid();

    virtual void notify(const std::vector<PasswordEntry>&) override;
private:
    WINDOW *m_window;
    IModel *m_model;

    std::vector<PasswordEntry> m_entries {};

    void print_header();
};
