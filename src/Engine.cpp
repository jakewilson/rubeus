#include "Engine.hpp"
#include "Logger.hpp"
#include "PasswordEntry.hpp"

#include <sqlite3.h>
#include <sstream>
#include <string.h>
#include <vector>

Engine::Engine()
{
    auto rc = sqlite3_open(m_db_name, &m_db);

    if (rc)
    {
        logger << "error opening sqlite3 db";
        logger << sqlite3_errstr(rc);
    }
}

Engine::~Engine()
{
    sqlite3_close(m_db);
}

void Engine::select_password_entries(std::vector<PasswordEntry> *entries)
{
    char *errmsg;

    std::stringstream query {};
    query << "SELECT * FROM password_entry;";

    auto rc = sqlite3_exec(
        m_db,
        query.str().c_str(),
        select_password_entries_cb,
        (void *)entries,
        &errmsg
    );

    if (rc)
    {
        std::stringstream ss{};
        ss << "[rc " << rc << "] ";
        ss << sqlite3_errstr(rc);

        logger << "error selecting password entries";
        logger << ss.str();
        logger << errmsg;

        sqlite3_free(errmsg);
    }
}

int select_password_entries_cb(
    void *entries_vec,
    int num_columns,
    char **col_ptrs,
    char **col_names
)
{
    if (num_columns == 0)
    {
        return 0;
    }

    const char * id_col = "id";
    const char * username_col = "username";
    const char * password_col = "password";
    const char * website_col = "website";

    int id;
    std::string username, password, website;

    for (auto i = 0; i < num_columns; i++)
    {
        if (strncmp(col_names[i], id_col, strlen(id_col)) == 0)
        {
            id = atoi(col_ptrs[i]);
        }
        else if (strncmp(col_names[i], username_col, strlen(username_col)) == 0)
        {
            username = col_ptrs[i];
        }
        else if (strncmp(col_names[i], password_col, strlen(password_col)) == 0)
        {
            password = col_ptrs[i];
        }
        else if (strncmp(col_names[i], website_col, strlen(website_col)) == 0)
        {
            website = col_ptrs[i];
        }
    }

    auto *entries = reinterpret_cast<std::vector<PasswordEntry> *>(entries_vec);

    entries->push_back({id, username, password, website});

    return 0;
}
