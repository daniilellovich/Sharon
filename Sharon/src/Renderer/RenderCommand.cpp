#include "sharon_pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sharon
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}