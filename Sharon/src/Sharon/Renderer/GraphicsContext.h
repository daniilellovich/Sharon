#pragma once

namespace Sharon
{
    class SHARON_API GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}

