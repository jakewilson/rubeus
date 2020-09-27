#include "colors.hpp"
#include "ListView.hpp"
#include "Logger.hpp"
#include "Model.hpp"
#include "Rubeus.hpp"

#include <ncurses.h>

Rubeus::Rubeus()
{
    init();

    m_model = new Model;
    m_current_view = new ListView(m_model);
    m_keep_running = true;
}

Rubeus::~Rubeus()
{
    delete m_current_view;
    delete m_model;

    endwin();
}

void Rubeus::init()
{
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    refresh(); // not sure why this is needed
    init_colors();
}

void Rubeus::run()
{
    while (m_keep_running)
    {
        m_current_view->render();
        process_input(getch());
    }
}

void Rubeus::process_input(const int c)
{
    switch (m_view_state)
    {
        case ViewState::LIST_VIEW:
            process_list_view_input(c);
            break;

        case ViewState::CREATE_VIEW:
            // TODO
            break;
    }
}

void Rubeus::process_list_view_input(const int c)
{
    // TODO
    auto list_view = dynamic_cast<ListView *>(m_current_view);
    switch (c)
    {
        case 'q': case 'Q':
            // TODO may want to generate an 'action' that
            // does this instead - or may be overkill
            m_keep_running = false;
            break;

        case 'j': case 'J': case KEY_DOWN:
            list_view->selected_entry_down();
            break;

        case 'k': case 'K': case KEY_UP:
            list_view->selected_entry_up();
            break;
    }
}
