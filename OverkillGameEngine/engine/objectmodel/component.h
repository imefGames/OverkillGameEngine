#pragma once

#include <engine\objectmodel\componentholder.h>

namespace OK
{
    class Component
    {
    protected:
        Component();

    private:
        ComponentHolderID m_ComponentHolderID;
    };
}