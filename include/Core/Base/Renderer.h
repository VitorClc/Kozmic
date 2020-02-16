#pragma once

#include <Renderers/RenderUtils.h>
#include <Components/Transform.h>

class Renderer
{
    public:
        virtual void Start(){};
        virtual void Render(Transform* _activeCamera){};

        Material material = Material();
};
