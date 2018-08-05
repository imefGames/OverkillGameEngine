#include <stdafx.h>
#include <engine\objectmodel\componentholder.h>

namespace OK
{
    ComponentHolderID ComponentHolder::GetNextComponentHolderID()
    {
        static ComponentHolderID currentComponentHolderID;
        return ++currentComponentHolderID;
    }
}