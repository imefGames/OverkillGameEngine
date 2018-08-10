#pragma once

#include <engine\objectmodel\component.h>

namespace OK
{
    class TextureLibraryComponent : public Component<TextureLibraryComponent>
    {
    private:
        EResult LoadComponent(JSONNode* componentNode) override;
    };
}