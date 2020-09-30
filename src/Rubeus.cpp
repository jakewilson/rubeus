#include "colors.hpp"
#include "CreateView.hpp"
#include "ListView.hpp"
#include "Logger.hpp"
#include "Model.hpp"
#include "Rubeus.hpp"

#include <ncurses.h>

Rubeus::Rubeus()
    : m_model(std::make_unique<Model>()), m_command_view(LINES - 1) // TODO not LINES - 1
{
    m_model->register_list_observer(this);

    m_view = std::make_unique<ListView>(m_entries, m_command_view_y);
    m_command_view.set_commands({{106, "move down"}, {107, "move up"}});
    m_keep_running = true;
}

Rubeus::~Rubeus() {}

void Rubeus::run()
{
    while (m_keep_running)
    {
        m_view->render();
        m_command_view.render();
        process_input(m_view->get_input());
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
    auto list_view = dynamic_cast<ListView *>(m_view.get());
    if (list_view == nullptr) // should be impossible
        return;

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
    auto create_view = dynamic_cast<CreateView *>(m_view.get());
    if (create_view == nullptr) // should be impossible
        return;

    switch (c)
    {
        case escape_key:
            toggle_list_view();
            break;

        case backspace_key: case KEY_BACKSPACE: case '\b':
            create_view->remove_char();
            break;

        case KEY_ENTER: case '\n': case '\r':
            if (create_view->get_focus() == Focus::password)
            {
                m_model->add_password_entry(
                    create_view->get_username().c_str(),
                    create_view->get_password().c_str(),
                    create_view->get_title().c_str()
                );
                toggle_list_view();
            }
            else
            {
                create_view->next_focus();
            }
            break;

        default:
            if (c >= 32 && c <= 126)
            {
                create_view->add_char(static_cast<char>(c));
            }
            break;
    }
}

void Rubeus::toggle_list_view()
{
    m_view = std::make_unique<ListView>(m_entries, m_command_view_y);
    m_view_state = ViewState::list;
}

void Rubeus::toggle_create_view()
{
    m_view = std::make_unique<CreateView>(m_command_view_y);
    m_view_state = ViewState::create;
}

void Rubeus::notify(const std::vector<PasswordEntry> entries)
{
    m_entries = entries;
}
