#pragma once

#include <vector>

class PasswordEntry;

class IListObserver
{
public:
    virtual void notify(std::vector<PasswordEntry> const *) = 0;
};
