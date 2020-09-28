#pragma once

class IModel;
class IView;

constexpr int escape_key    = 27;
constexpr int backspace_key = 127;

class Rubeus
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

private:
    IModel *m_model;
    IView *m_current_view;

    bool m_keep_running {true};
    ViewState m_view_state {ViewState::list};

    void init();
    void process_input(const int c);
    void process_list_view_input(const int c);
    void process_create_view_input(const int c);

    void toggle_list_view();
    void toggle_create_view();
};
