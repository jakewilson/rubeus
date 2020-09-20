#include "IListObserver.h"
#include "model.h"

#include <vector>

Model::Model()
{
    // TODO test - remove
    m_entries.push_back({"user1", "1234", "google.com"});
    m_entries.push_back({"user2", "3456", "github.com"});
}

void Model::register_list_observer(IListObserver *observer)
{
    m_list_observers.push_back(observer);
    notify_list_observers(); // TODO remove
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
        observer->notify(m_entries);
    }
}
