#include <ncurses.h>

class Rubeus
{
public:
    Rubeus();
    ~Rubeus();

    void update();
    void render();
    void print_grid();
private:
    WINDOW *m_window;

    void print_header();
};
