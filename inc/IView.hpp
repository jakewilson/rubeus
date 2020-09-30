#pragma once

#include <ncurses.h>

class IView
{
public:
    IView(int, int, int, int);
    virtual ~IView();
    virtual void render() = 0;
    virtual const int get_input() = 0;

protected:
    WINDOW *m_window;
    int m_x, m_y;
    int m_w, m_h;
};
