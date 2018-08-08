#pragma once

#include <engine\objectmodel\component.h>

namespace OK
{
    class CameraComponent : public Component<CameraComponent>
    {
    public:
        CameraComponent();

        OK::Bool IsActive() const { return m_IsActive; }

    private:
        EResult LoadComponent(JSONNode* componentNode) override;

        OK::Bool m_IsActive;
    };
}