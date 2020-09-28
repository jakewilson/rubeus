#pragma once

#include "IView.hpp"

#include <string>
#include <ncurses.h>

#define TITLE_X 3
#define TITLE_Y 3
#define TITLE_LABEL "Title: "
#define TITLE_CURSOR_X TITLE_X + strlen(TITLE_LABEL)

#define USERNAME_X 3
#define USERNAME_Y 4
#define USERNAME_LABEL "Username: "
#define USERNAME_CURSOR_X USERNAME_X + strlen(USERNAME_LABEL)

#define PASSWORD_X 3
#define PASSWORD_Y 5
#define PASSWORD_LABEL "Password: "
#define PASSWORD_CURSOR_X PASSWORD_X + strlen(PASSWORD_LABEL)

enum class Focus
{
    title,
    username,
    password
};

class CreateView : public IView
{
public:
    CreateView();
    ~CreateView() {}

    void render() override;
    void render_header() const;
    const int get_input() override;
    void move_cursor_right();
    void move_cursor_left();

    void add_char(const char c);
    void remove_char();

    void place_cursor();

    const Focus get_focus() const;
    void next_focus();
    void prev_focus();

private:
    WINDOW *m_window;

    std::string m_title {""};
    std::string m_username {""};
    std::string m_password {""};

    Focus m_focus;
    std::string& get_focus_str();
};
