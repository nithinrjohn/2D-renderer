#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "util/utility.h"

class Shader
{
	private:
		GLuint ID;
		std::string vertexPath;
		std::string fragmentPath;
	public:
		Shader();
		Shader(std::string vertexPath, std::string fragmentPath);
		~Shader();
		
		bool Init();
		void Activate();
		void Deactivate();
		void Delete();

		void SetBool(const std::string &name, bool value) const;
		void SetInt(const std::string &name, int value) const;
		void SetFloat(const std::string &name, float value) const;

		void SetVec2(const std::string &name, const glm::vec2 &value) const;
		void SetVec3(const std::string &name, const glm::vec3 &value) const;
		void SetVec4(const std::string &name, const glm::vec4 &value) const;

		void SetMat2(const std::string &name, const glm::mat2 &mat) const;
		void SetMat3(const std::string &name, const glm::mat3 &mat) const;
		void SetMat4(const std::string &name, const glm::mat4 &mat) const;
		
		GLuint GetID() { return ID; }
};

