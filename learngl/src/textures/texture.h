#pragma once
#include<string>
#include<GL/glew.h>

class Texture
{
private:
	unsigned int x_ID;
	std::string x_FilePath;
	unsigned char* x_Local_Buffers;
	int x_Width, x_Height, x_BPP;
public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot=0) const;
	void UnBind() const;
	int GetWidth() { return x_Width; }
	int GetHeigth() { return x_Height; }
};