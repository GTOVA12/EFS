#pragma once
#include <glad/glad.h>
#include  <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using std::string;
class Shader
{
public:
	// the program ID
	unsigned int ID;
	// constructor reads and builds the shader
	Shader(string VertexCodePath, string FragmentCodePath);
	// use/activate the shader
	void use();
	// utility uniform functions
	void SetBool(const string& name, bool value) const ;
	void SetInt(const string& name, int value) const ;
	void SetFloat(const string& name, float value) const ;
	void SetVec3(const string& name, const glm::vec3& value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
};

