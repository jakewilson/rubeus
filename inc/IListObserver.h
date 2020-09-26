#pragma once

#include <vector>

class PasswordEntry;

class IListObserver
{
public:
    virtual void notify(const std::vector<PasswordEntry>&) = 0;
};
