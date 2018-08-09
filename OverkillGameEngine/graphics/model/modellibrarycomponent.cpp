#include <stdafx.h>
#include <graphics\model\modellibrarycomponent.h>

#include <graphics\graphicswrapper.h>

namespace OK
{
    EResult ModelLibraryComponent::LoadComponent(JSONNode* componentNode)
    {
        return GraphicsWrapper::Get()->RegisterModels(componentNode);
    }
}