#pragma once

class IModel;
class IView;

class Rubeus
{
public:
    Rubeus();
    ~Rubeus();

    void run();
private:
    IModel *m_model;
    IView *m_current_view;

    bool m_keep_running;

    void init();
    void process_input(const int c);
};
