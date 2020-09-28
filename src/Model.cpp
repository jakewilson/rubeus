#include "IListObserver.hpp"
#include "Logger.hpp"
#include "Model.hpp"

#include <vector>

Model::Model() : m_engine(Engine())
{
    m_engine.select_password_entries(&m_entries);
}

void Model::register_list_observer(IListObserver *observer)
{
    m_list_observers.push_back(observer);
    observer->notify(&m_entries); // TODO do I need this?
}

void Model::remove_list_observer(IListObserver *observer)
{
    auto index = std::find(
        m_list_observers.begin(), 
        m_list_observers.end(),
        observer
    );

    if (index != m_list_observers.end())
    {
        m_list_observers.erase(index);
    }
}

void Model::notify_list_observers() const
{
    for (const auto& observer : m_list_observers)
    {
        observer->notify(&m_entries);
    }
}

void Model::add_password_entry(
    const char *username,
    const char *password,
    const char *title
)
{
    const bool success = m_engine.add_password_entry(username, password, title);

    if (success)
    {
        // update the list of entries
        // TODO this is inefficient - we don't need to re-select
        // the entire list when adding a single item
        m_engine.select_password_entries(&m_entries);
        notify_list_observers();
    }
}
