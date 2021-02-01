#pragma once

namespace Sharon
{
    enum class RendererAPI
    {
        None, OpenGL, Direct3D, Vulcan, Metal,
    };

    class Renderer
    {
    public:
        static RendererAPI GetAPI() { return s_RendererAPI; }
    private:
        static RendererAPI s_RendererAPI;
    };
}