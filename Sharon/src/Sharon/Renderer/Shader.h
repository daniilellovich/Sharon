#pragma once
#include "Sharon/Core/Base.h"
#include <string>
#include "glm/glm.hpp"

namespace Sharon
{
	class SHARON_API Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		//uint32_t GetRendererID() { return m_RendererID; }

	private:
		uint32_t m_RendererID;
	};
}