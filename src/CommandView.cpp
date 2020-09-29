#include "CommandView.hpp"

#include <ncurses.h>

CommandView::CommandView(std::initializer_list<int> commands)
    : m_commands(std::vector<int>(commands))
{

}

void render()
{

}
