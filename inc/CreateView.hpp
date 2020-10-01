#pragma once

#include "IView.hpp"

#include <string>
#include <ncurses.h>

constexpr int title_y = 2;
constexpr int username_y = 3;
constexpr int password_y = 4;

constexpr int create_view_start_col = 1;

const std::string title_label {"Title: "};
const std::string username_label {"Username: "};
const std::string password_label {"Password: "};

const int title_cursor_x = title_label.length();
const int username_cursor_x = username_label.length();
const int password_cursor_x = password_label.length();

enum class Focus
{
    title,
    username,
    password
};

class CreateView : public IView
{
public:
    CreateView(int, int, int, int);
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

    const std::string get_title() { return m_title; }
    const std::string get_username() { return m_username; }
    const std::string get_password() { return m_password; }

private:

    std::string m_title {""};
    std::string m_username {""};
    std::string m_password {""};

    Focus m_focus;
    std::string& get_focus_str();
};
