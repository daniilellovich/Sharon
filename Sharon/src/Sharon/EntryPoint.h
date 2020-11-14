#pragma once

#ifdef SHARON_PLATFORM_WINDOWS

extern Sharon::Application* Sharon::CreateApplication();

int main(int argc, char** argv)
{
    Sharon::Log::Init();
    SHARON_CORE_INFO("Logging system initialized.");
    auto app = Sharon::CreateApplication();
    app->Run();
    delete app;
}

#endif