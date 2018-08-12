#include <stdafx.h>
#include <graphics\texture\texturelibrarycomponent.h>

#include <graphics\graphicswrapper.h>

namespace OK
{
    EResult TextureLibraryComponent::LoadComponent(const JSONNode& componentNode)
    {
        return GraphicsWrapper::Get()->RegisterTextures(componentNode);
    }
}