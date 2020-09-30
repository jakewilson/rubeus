#include "colors.hpp"
#include "CommandView.hpp"
#include "Logger.hpp"

#include <sstream>
#include <vector>

CommandView::CommandView(int window_y)
    : m_window_y(window_y)
{
    m_window = newwin(2, COLS, m_window_y, 0);
    curs_set(0);
}

CommandView::~CommandView()
{
    delwin(m_window);
}

void CommandView::render()
{
    wattron(m_window, COLOR_PAIR(RUBEUS_BLACK_GREEN));
    mvwprintw(m_window, 0, 0, " %s ", m_command_str.c_str());
    wattroff(m_window, COLOR_PAIR(RUBEUS_BLACK_GREEN));
    wrefresh(m_window);
}

void CommandView::set_commands(const std::vector<RubeusCommand>& commands)
{
    for (const auto& command : commands)
    {
        m_command_str += command.to_str() + " ";
    }
}
