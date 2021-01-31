#pragma once
#include "Sharon/Core.h"
#include <string>

namespace Sharon
{
	class SHARON_API Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		//uint32_t GetRendererID() { return m_RendererID; }

	private:
		uint32_t m_RendererID;
	};
}