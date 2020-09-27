#pragma once

struct IView
{
    virtual ~IView() {}
    virtual void render() = 0;
    virtual const int get_input() = 0;
};
