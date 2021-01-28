#include "sharon_pch.h"
#include "Layer.h"

namespace Sharon
{
    Layer::Layer(const std::string& debugName)
        : m_DebugName(debugName) { }

    Layer::~Layer() { }
}