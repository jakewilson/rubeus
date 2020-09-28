#include "colors.hpp"
#include "CreateView.hpp"
#include "ListView.hpp"
#include "Logger.hpp"
#include "Model.hpp"
#include "Rubeus.hpp"

#include <ncurses.h>

Rubeus::Rubeus()
{
    init();

    m_model = new Model;
    m_model->register_list_observer(this);

    m_current_view = new ListView(*m_entries);
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
        process_input(m_current_view->get_input());
    }
}

void Rubeus::process_input(const int c)
{
    switch (m_view_state)
    {
        case ViewState::list:
            process_list_view_input(c);
            break;

        case ViewState::create:
            process_create_view_input(c);
            break;
    }
}

void Rubeus::process_list_view_input(const int c)
{
    auto list_view = dynamic_cast<ListView *>(m_current_view);
    switch (c)
    {
        case 'q': case 'Q': case escape_key:
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

        case 'c': case 'C':
            toggle_create_view();
            break;
    }
}

void Rubeus::process_create_view_input(const int c)
{
    auto create_view = dynamic_cast<CreateView *>(m_current_view);
    switch (c)
    {
        case escape_key:
        {
            toggle_list_view();
            break;
        }
        case backspace_key: case KEY_BACKSPACE: case '\b':
        {
            create_view->remove_char();
            break;
        }
        case KEY_ENTER: case '\n': case '\r':
        {
            auto focus = create_view->get_focus();
            if (focus == Focus::password)
            {
                // TODO save password here
                toggle_list_view();
            }
            else
            {
                create_view->next_focus();
            }
            break;
        }
        default:
        {
            if (c >= 32 && c <= 126)
            {
                create_view->add_char(static_cast<char>(c));
            }
            break;
        }
    }
}

void Rubeus::toggle_list_view()
{
    // TODO we may want to dump the window instead of delete it
    delete m_current_view;

    m_current_view = new ListView(*m_entries);
    m_view_state = ViewState::list;
}

void Rubeus::toggle_create_view()
{
    // TODO we may want to dump the window instead of delete it
    delete m_current_view;

    m_current_view = new CreateView;
    m_view_state = ViewState::create;
}

void Rubeus::notify(std::vector<PasswordEntry> const * entries)
{
    m_entries = entries;
}
