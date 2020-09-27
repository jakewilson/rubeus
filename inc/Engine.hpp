#pragma once

#include <string>

typedef struct sqlite3 sqlite3; // forward declaration

class Engine
{
public:
    Engine();
    ~Engine();

private:
    sqlite3 *m_db;
    const char *m_db_name {"rubeus.db"};
};
