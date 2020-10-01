#include "colors.hpp"
#include "CommandView.hpp"
#include "Logger.hpp"

#include <sstream>
#include <vector>

CommandView::CommandView(int x, int y, int w, int h)
{
    m_window = newwin(h, w, y, x);
    curs_set(0);
}

CommandView::~CommandView()
{
    delwin(m_window);
}

void CommandView::render()
{
    wclear(m_window);
    mvwprintw(m_window, 0, 0, "%s", m_command_str.c_str());
    mvwchgat(m_window, 0, 0, -1, 0, RUBEUS_BLACK_GREEN, NULL);
    wrefresh(m_window);
}

void CommandView::set_commands(const std::vector<RubeusCommand>& commands)
{
    std::string command_str {};
    for (const auto& command : commands)
    {
        command_str += command.to_str() + " ";
    }

    m_command_str = command_str;
}
