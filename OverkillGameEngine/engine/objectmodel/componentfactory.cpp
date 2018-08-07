#include <stdafx.h>
#include <engine\objectmodel\componentfactory.h>

namespace OK
{
    BaseComponentFactory::BaseComponentFactory(ComponentFactoryID factoryID, const OK::char8* name)
        : m_FactoryID{ factoryID }
        , m_Name{ name }
    {
    }
}