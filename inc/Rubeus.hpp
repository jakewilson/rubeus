#pragma once

#include "CommandView.hpp"
#include "CreateView.hpp"
#include "ListView.hpp"
#include "IListObserver.hpp"
#include "IModel.hpp"
#include "IView.hpp"
#include "PasswordEntry.hpp"

#include <memory>
#include <vector>

#define COMMAND_VIEW_Y LINES - 1

constexpr int enter_key     = 10;
constexpr int escape_key    = 27;
constexpr int backspace_key = 127;

constexpr int window_padding = 2;

class Rubeus : public IListObserver
{
public:
    Rubeus();
    ~Rubeus();

    enum class ViewState
    {
        list,
        create
    };

    void run();
    void notify(const std::vector<PasswordEntry>) override;

private:
    std::unique_ptr<IModel> m_model;
    std::unique_ptr<IView> m_main_view;

    bool m_keep_running {true};

    ViewState m_view_state {ViewState::list};

    std::vector<PasswordEntry> m_entries;

    CommandView m_command_view;

    void process_input(const int c);
    void process_list_view_input(const int c);
    void process_create_view_input(const int c);

    void toggle_list_view();
    void toggle_create_view();

    std::unique_ptr<ListView> make_list_view();
    std::unique_ptr<CreateView> make_create_view();

    std::vector<RubeusCommand> get_list_view_commands();
    std::vector<RubeusCommand> get_create_view_commands();
};
