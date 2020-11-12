#pragma once
#include "Event.h"

namespace Sharon
{
    class WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() { }

        EVENT_CLASS_TYPE(WindowClosed)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


    class WindowFocusedEvent : public Event
    {
    public:
        WindowFocusedEvent() {}

        EVENT_CLASS_TYPE(WindowFocused)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


    class WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent() {}

        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


    class WindowResizedEvent : public Event
    {
    public:
        WindowResizedEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height)
        {
        }

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeigth() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResized)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int m_Width, m_Height;
    };


    class WindowMovedEvent : public Event
    {
    public:
        WindowMovedEvent(unsigned int xOffset, unsigned int yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset)
        {
        }

        unsigned int GetXOffset() const { return m_XOffset; }
        unsigned int GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowMovedEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int m_XOffset, m_YOffset;
    };


    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}