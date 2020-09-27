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

    // TODO would be nice to put these commands into a file
    std::stringstream query;
    query << "CREATE TABLE IF NOT EXISTS password_entry (";
    query << "id INTEGER PRIMARY KEY AUTOINCREMENT";
    query << ", username TEXT";
    query << ", password TEXT";
    query << ", website TEXT";
    query << ");";

    char *errmsg;
    rc = sqlite3_exec(
        m_db,
        query.str().c_str(),
        nullptr,
        nullptr,
        &errmsg
    );

    if (rc)
    {
        print_errmsg(rc, "error creating password_entry table", errmsg);
        sqlite3_free(errmsg);
    }
}

Engine::~Engine()
{
    sqlite3_close(m_db);
}

void Engine::select_password_entries(std::vector<PasswordEntry> *entries)
{
    char *errmsg;
    auto rc = sqlite3_exec(
        m_db,
        "SELECT * FROM password_entry",
        select_password_entries_cb,
        (void *)entries,
        &errmsg
    );

    if (rc)
    {
        print_errmsg(rc, "error selecting password entries", errmsg);
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

void Engine::print_errmsg(int rc, const char *rubeus_msg, const char *sqlite_errmsg)
{
        std::stringstream ss{};
        ss << "[rc " << rc << "] ";
        ss << sqlite3_errstr(rc);

        logger << rubeus_msg;
        logger << ss.str();
        logger << sqlite_errmsg;
}
