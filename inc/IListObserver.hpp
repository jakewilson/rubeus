#pragma once

#include <vector>

class PasswordEntry;

class IListObserver
{
public:
    virtual ~IListObserver() {}
    virtual void notify(const std::vector<PasswordEntry>) = 0;
};
