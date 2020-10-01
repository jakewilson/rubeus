#pragma once

#include "RubeusCommand.hpp"

#include <ncurses.h>
#include <string>

class CommandView
{
public:
    CommandView(int, int, int, int);
    ~CommandView();

    void render();
    void set_commands(const std::vector<RubeusCommand>&);

private:
    std::string m_command_str;

    WINDOW *m_window;
};
