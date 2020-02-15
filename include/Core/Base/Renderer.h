#pragma once

#include <Renderers/RenderUtils.h>
#include <Components/Transform.h>

class Renderer
{
    public:
        virtual void Start() = 0;
        virtual void Render(Transform* _activeCamera) = 0;

        Material material = Material();
};
