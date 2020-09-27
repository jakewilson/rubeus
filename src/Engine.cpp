#include "Engine.hpp"

#include <sqlite3.h>

Engine::Engine()
{
    sqlite3_open(m_db_name, &m_db);
}

Engine::~Engine()
{
    sqlite3_close(m_db);
}
