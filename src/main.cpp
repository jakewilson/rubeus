#include "crypto.hpp"
#include "colors.hpp"
#include "Rubeus.hpp"
#include "RubeusCommand.hpp"

#include <iostream>
#include <ncurses.h>
#include <termios.h>

constexpr int stdin_id = 1;

void toggle_keystrokes(bool enable)
{
    termios tty;
    tcgetattr(stdin_id, &tty);

    if (enable)
        tty.c_lflag |= ECHO; // turn on echo
    else
        tty.c_lflag &= ~ECHO; // turn off echo

    tcsetattr(stdin_id, TCSANOW, &tty);
}

std::string get_password()
{
    std::string password, confirm_password;
    toggle_keystrokes(false);

    std::cout << "password: ";
    std::getline(std::cin, password);

    std::cout << "\nretype password: ";
    std::getline(std::cin, confirm_password);

    std::cout << std::endl;

    toggle_keystrokes(true);
    if (password != confirm_password)
    {
        std::cout << "passwords did not match" << std::endl;
        abort();
    }

    return password;
}

void init()
{
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    init_colors();
}

void kill()
{
    endwin();
}

int main(int argc, char *argv[])
{
    auto password = get_password();

    char key[crypto::output_len];
    auto rc = crypto::derive_key(password, key);

    if (rc)
    {
        std::cout << "error deriving key: " << rc << std::endl;
        return rc;
    }

/*
    for (auto i = 0; i < crypto::output_len; i++) {
        if (i % 8 == 0) printf("\n");
        printf("0x%02x ", static_cast<uint8_t>(key[i]));
    }
    printf("\n");
*/


    // TODO add arg for file (?)
    init();

    Rubeus rubeus{};
    rubeus.run();

    kill();
    return 0;
}
