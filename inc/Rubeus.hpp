#pragma once

#include "IListObserver.hpp"

#include <memory>
#include <vector>

class IModel;
class IView;
class PasswordEntry;

constexpr int escape_key    = 27;
constexpr int backspace_key = 127;

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
    std::unique_ptr<IView> m_view;

    bool m_keep_running {true};

    ViewState m_view_state {ViewState::list};

    std::vector<PasswordEntry> m_entries;

    void init();
    void process_input(const int c);
    void process_list_view_input(const int c);
    void process_create_view_input(const int c);

    void toggle_list_view();
    void toggle_create_view();
};
