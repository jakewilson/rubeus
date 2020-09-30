#include "IView.hpp"

IView::IView(int x, int y, int w, int h)
    : m_x(x), m_y(y), m_w(w), m_h(h)
{
    m_window = newwin(m_h, m_w, m_y, m_x);
}

IView::~IView()
{
    delwin(m_window);
}
