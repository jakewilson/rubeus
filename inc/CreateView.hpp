#pragma once

#include "IView.hpp"

#include <ncurses.h>

class CreateView : public IView
{
public:
    CreateView();
    ~CreateView() {}

    void render() override;
    const int get_input() override;
private:
    WINDOW *m_window;
};
