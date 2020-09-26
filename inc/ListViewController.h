#pragma once

#include "IController.h"
#include "IModel.h"

class ListViewController : public IController
{
public:
    ListViewController(IModel *model) : m_model(model) {}

private:
    IModel *m_model;
};
