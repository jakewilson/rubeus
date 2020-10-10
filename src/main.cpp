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

    char key[crypto::key_len];
    std::cout << "hashing..." << std::flush;
    auto rc = crypto::derive_key(password, key);

    if (rc)
    {
        std::cout << "error deriving key: " << rc << std::endl;
        return rc;
    }
    else
    {
        std::cout << "done" << std::endl;
    }

/* TODO - use this when storing/retrieving passwords
    unsigned char ciphertext[256] = {0};
    try
    {
        crypto::encrypt_str((const unsigned char *)key, "my name is jake", ciphertext);
        for (auto i = 0; i < 256; i++) {
            if (i % 16 == 0) printf("\n");
            printf("0x%02x ", static_cast<uint8_t>(ciphertext[i]));
        }
        printf("\n\n");
        std::string cipher ((char *)ciphertext);
        unsigned char plaintext[256] = {0};
        crypto::decrypt_str((const unsigned char *)key, cipher, plaintext);
        printf("%s\n", plaintext);
    }
    catch (crypto::encrypt_exception &e)
    {
        std::cout << e.what() << std::endl;
    }
*/

    // TODO add arg for file (?)
    init();

    Rubeus rubeus {key};
    rubeus.run();

    // zero out key
    memset(key, 0, crypto::key_len);
    kill();
    return 0;
}
