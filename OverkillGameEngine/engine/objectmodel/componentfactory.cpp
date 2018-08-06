#include <stdafx.h>
#include <engine\objectmodel\componentfactory.h>

namespace OK
{
    BaseComponentFactory::BaseComponentFactory(ComponentFactoryID factoryID)
        : m_FactoryID{ factoryID }
    {
    }
}