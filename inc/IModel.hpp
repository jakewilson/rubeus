#pragma once

#include <vector>

class IListObserver;

class IModel
{
public:
    IModel() {}
    virtual ~IModel() {}
    virtual void register_list_observer(IListObserver *) = 0;
    virtual void remove_list_observer(IListObserver *) = 0;
protected:
    virtual void notify_list_observers() const = 0;
    std::vector<IListObserver *> m_list_observers {};
};
