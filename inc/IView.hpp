#pragma once

struct IView
{
    virtual ~IView() {}
    virtual void render() = 0;
};
