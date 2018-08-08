#pragma once

#include <engine\objectmodel\componentholder.h>

namespace OK
{
    namespace ComponentUtils
    {
        template <typename ComponentType, typename ... Args>
        EResult FindComponents(ComponentHolderID holderID, ComponentType*& component, Args ... args)
        {
            EResult findResult{ EResult::Failure };
            component = static_cast<ComponentType*>(ComponentHolder::FindComponentForID(holderID, ComponentType::GetFactoryID()));
            if (component != nullptr)
            {
                findResult = FindComponents(holderID, args...);
            }
            return findResult;
        }

        template <typename ComponentType>
        EResult FindComponents(ComponentHolderID holderID, ComponentType*& component)
        {
            component = static_cast<ComponentType*>(ComponentHolder::FindComponentForID(holderID, ComponentType::GetFactoryID()));
            return (component != nullptr ? EResult::Success : EResult::Failure);
        }
    }
}