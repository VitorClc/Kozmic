#pragma once

#include <Components/Transform.h>

class Renderer
{
    public:
        virtual void Start() = 0;
        virtual void Render(Transform* _activeCamera) = 0;
};
