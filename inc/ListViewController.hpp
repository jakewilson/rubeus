#pragma once

#include "IController.hpp"
#include "IModel.hpp"

class ListViewController : public IController
{
public:
    ListViewController(IModel *model) : m_model(model) {}

private:
    IModel *m_model;
};
