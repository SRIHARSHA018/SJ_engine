#pragma once
#include<unordered_map>
#include<GL/glew.h>
#include<GLM/glm.hpp>
#include<GLM/gtx/transform.hpp>
#include<GLM/gtc/type_ptr.hpp>
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
//CLASS for shader
namespace SJ_engine {
	namespace SJ_shader {
		class shader
		{
		private:
			unsigned int x_Shader_Program_ID;
			unsigned int createprogram(unsigned int Vshader, unsigned int Fshader) ;
			//cache list of uniforms
			std::unordered_map<std::string, int> uniformlistCache;
		public:
			shader();
			glm::mat4 model = glm::mat4(1.f);
			unsigned int Get_shader_program(){	return x_Shader_Program_ID; }
			void GenBindData();
			void shaderdestroy();
			void UseShaderProgram();
		public:
			void modelmatrix();
			void SetUniformMatrix4f(const std::string &uniformname, int size, const glm::mat4 &matrix);
			void SetUniform1i(const std::string& uniformname, int value);
			unsigned int GetUniformLocation(const std::string &uniformname);

		};
	}
}
