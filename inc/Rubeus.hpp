#pragma once

class IModel;
class IView;

enum ViewState
{
    LIST_VIEW,
    CREATE_VIEW
};

class Rubeus
{
public:
    Rubeus();
    ~Rubeus();

    void run();
private:
    IModel *m_model;
    IView *m_current_view;

    bool m_keep_running {true};
    ViewState m_view_state {ViewState::LIST_VIEW};

    void init();
    void process_input(const int c);
    void process_list_view_input(const int c);
};
