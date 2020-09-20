#pragma once

#include "IListObserver.h"
#include "IModel.h"

#include <ncurses.h>
#include <vector>

class PasswordEntry; // TODO

class ListView : public IListObserver
{
public:
    ListView(IModel *model);
    ~ListView();

    void update();
    void render();
    void print_grid();

    virtual void notify(const std::vector<PasswordEntry *>&) override;
private:
    WINDOW *m_window;
    IModel *m_model;

    void print_header();
};
