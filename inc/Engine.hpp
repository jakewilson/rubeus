#pragma once

#include <vector>

// forward declarations
class PasswordEntry;
typedef struct sqlite3 sqlite3;

class Engine
{
public:
    Engine();
    ~Engine();

    void init();

    void select_password_entries(std::vector<PasswordEntry> *);
    bool add_password_entry(const char *, const char *, const char *);

private:
    sqlite3 *m_db;
    const char *m_db_name {"rubeus.db"};
    void print_errmsg(int, const char *, const char *);
};

// TODO I would like this to be private...or maybe a lambda?
int select_password_entries_cb(void *, int, char**, char**);
