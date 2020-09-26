#pragma once

#include "IModel.hpp"
#include "PasswordEntry.hpp"

class Model : public IModel
{
public:
    Model();
    ~Model() {}
    void register_list_observer(IListObserver *) override;
    void remove_list_observer(IListObserver *) override;
protected:
    void notify_list_observers() const override;
private:
    std::vector<PasswordEntry> m_entries {};
};
