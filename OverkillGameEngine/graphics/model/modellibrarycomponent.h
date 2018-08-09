#pragma once

#include <engine\objectmodel\component.h>

namespace OK
{
    class ModelLibraryComponent : public Component<ModelLibraryComponent>
    {
    private:
        EResult LoadComponent(JSONNode* componentNode) override;
    };
}