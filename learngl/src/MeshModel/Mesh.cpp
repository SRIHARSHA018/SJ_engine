#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	x_InitModelMatrix();
	this->x_vertices = vertices;
	this->x_indices = indices;
	//this->x_textures = textures;
	x_setup_mesh();
}
Mesh::Mesh(PrimitiveType primitive)
{
	x_InitModelMatrix();
	switch (primitive)
	{
	case Cube:
		CreateCube();
		break;
	case Plane:
		CreatePlane();
		break;
	}
}



Mesh::~Mesh()
{
}

void Mesh::x_EnableVertexAttrib()
{

	//VertexPositions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//TextureCoordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoordinates));
	//VertexNormals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vertexNormals));
}


void Mesh::x_setup_mesh()
{


	glGenBuffers(1, &x_vbo);
	glCreateVertexArrays(1, &x_vao);
	glCreateBuffers(1, &x_ebo);
	glBindVertexArray(x_vao);
	glBindBuffer(GL_ARRAY_BUFFER, x_vbo);
	glBufferData(GL_ARRAY_BUFFER, x_vertices.size()*sizeof(Vertex), &x_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, x_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, x_indices.size() * sizeof(unsigned int), &x_indices[0], GL_STATIC_DRAW);
	x_EnableVertexAttrib();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::x_InitModelMatrix()
{

	x_ModelMatrix = glm::mat4(1.f);
	x_ModelMatrix = glm::translate(x_ModelMatrix, glm::vec3(0.f, 0.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
	x_ModelMatrix = glm::scale(x_ModelMatrix, glm::vec3(1.0f));

}



void  Mesh::DrawMesh(SJ_engine::SJ_shader::shader* obj)
{
	obj->UseShaderProgram();
	glBindVertexArray(this->x_vao);
	glDrawElements(GL_TRIANGLES, x_indices.size(), GL_UNSIGNED_INT,(void*)0);
}

void Mesh::CreateCube()
{

	Vertex cubeVertices[]=
	{

		//cube2
		 //back face
		glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec2(0.f,0.f),		glm::vec3(0.0f,  0.0f, -1.0f),//0
		glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec2(1.0f,0.f),	glm::vec3(0.0f,  0.0f, -1.0f),//1
		glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec2(1.0f,1.0f),	glm::vec3(0.0f,  0.0f, -1.0f),//2
		//glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec2(1.0f,1.0f),	glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec2(0.f,1.0f),    glm::vec3(0.0f,  0.0f, -1.0f),//3
		//glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec2(0.f,0.f),		glm::vec3(0.0f,  0.0f, -1.0f),
		//front face
		glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec2(0.f,0.f),		glm::vec3(0.0f,  0.0f, 1.0f),//4
		glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec2(1.0f,0.f),	glm::vec3(0.0f,  0.0f, 1.0f),//5
		glm::vec3(0.5f,  0.5f, 0.5f),		glm::vec2(1.f,1.f),		glm::vec3(0.0f,  0.0f, 1.0f),//6
		//glm::vec3(0.5f,  0.5f, 0.5f),		glm::vec2(1.f,1.f),		glm::vec3(0.0f,  0.0f, 1.0f),
		glm::vec3(-0.5f,  0.5f, 0.5f),		glm::vec2(0.f,1.f),		glm::vec3(0.0f,  0.0f, 1.0f),//7
		//glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec2(0.f,0.f),		glm::vec3(0.0f,  0.0f, 1.0f),
		//left face									 
		glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec2(0.f,0.f),		glm::vec3(-1.0f,  0.0f,  0.0f),//8
		glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec2(1.0f,0.f),	glm::vec3(-1.0f,  0.0f,  0.0f),//9
		glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec2(1.f,1.f),		glm::vec3(-1.0f,  0.0f,  0.0f),//10
		//glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec2(1.f,1.f),		glm::vec3(-1.0f,  0.0f,  0.0f),
		glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec2(0.f,1.f),		glm::vec3(-1.0f,  0.0f,  0.0f),//11
		//glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec2(0.f,0.f),		glm::vec3(-1.0f,  0.0f,  0.0f),
		//RIGHT FACE									 
		glm::vec3(  0.5f,  0.5f,  0.5f),	glm::vec2(0.f,0.f),     glm::vec3(1.0f,  0.0f,  0.0f),//12
		glm::vec3(  0.5f,  0.5f, -0.5f),	glm::vec2(1.0f,0.f),    glm::vec3(1.0f,  0.0f,  0.0f),//13
		glm::vec3(  0.5f, -0.5f, -0.5f),	glm::vec2(1.f,1.f),     glm::vec3(1.0f,  0.0f,  0.0f),//14
		//glm::vec3(  0.5f, -0.5f, -0.5f),	glm::vec2(1.f,1.f),     glm::vec3(1.0f,  0.0f,  0.0f),
		glm::vec3(  0.5f, -0.5f,  0.5f),	glm::vec2(0.f,1.f),     glm::vec3(1.0f,  0.0f,  0.0f),//15
		//glm::vec3(  0.5f,  0.5f,  0.5f),	glm::vec2(0.f,0.f),     glm::vec3(1.0f,  0.0f,  0.0f),
		//bottom face								 
		glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec2(0.f,0.f),		 glm::vec3(0.0f, -1.0f,  0.0f),//16
		glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec2(1.0f,0.f),	 glm::vec3(0.0f, -1.0f,  0.0f),//17
		glm::vec3(0.5f, -0.5f,  0.5f),		glm::vec2(1.f,1.f),		 glm::vec3(0.0f, -1.0f,  0.0f),//18
		//glm::vec3(0.5f, -0.5f,  0.5f),		glm::vec2(1.f,1.f),		 glm::vec3(0.0f, -1.0f,  0.0f),
		glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec2(0.f,1.f),		 glm::vec3(0.0f, -1.0f,  0.0f),//19
		//glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec2(0.f,0.f),		 glm::vec3(0.0f, -1.0f,  0.0f),
		//top face											 
		glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec2(0.f,0.f),		glm::vec3(0.0f,  1.0f,  0.0f),//20
		glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec2(1.0f,0.f),	glm::vec3(0.0f,  1.0f,  0.0f),//21
		glm::vec3(0.5f,  0.5f,  0.5f),		glm::vec2(1.f,1.f),		glm::vec3(0.0f,  1.0f,  0.0f),//22
		//glm::vec3(0.5f,  0.5f,  0.5f),		glm::vec2(1.f,1.f),		glm::vec3(0.0f,  1.0f,  0.0f),
		glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec2(0.f,1.f),		glm::vec3(0.0f,  1.0f,  0.0f)//23
		//glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec2(0.f,0.f),		glm::vec3(0.0f,  1.0f,  0.0f)
	};
	
	for (unsigned int i = 0; i < sizeof(cubeVertices) / sizeof(Vertex); i++)
	{
		x_vertices.push_back(cubeVertices[i]);
	}
	unsigned int indices[] = {
		0,1,2,
		2,3,0,
		4,5,6,
		6,7,4,
		8,9,10,
		10,11,8,
		12,13,14,
		14,15,12,
		16,17,18,
		18,19,16,
		20,21,22,
		22,23,20
	};
	for (unsigned int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++)
	{
		x_indices.push_back(indices[i]);
	}

	x_setup_mesh();
}
void Mesh::CreatePlane()
{
	Vertex planevertices[] =
	{
		//left triangle
		//vertex positions				  texture coordinates   normals
		glm::vec3(-10.f,-1.f,-10.f),      glm::vec2(0.f,0.f),   glm::vec3(0.f,1.f,0.f),//0
		glm::vec3( 10.f,-1.f,-10.f),      glm::vec2(1.f,0.f),   glm::vec3(0.f,1.f,0.f),//1
		glm::vec3( 10.f,-1.f,10.f),       glm::vec2(1.f,1.f),   glm::vec3(0.f,1.f,0.f),//2
		 //right triangle
		//glm::vec3(-10.f,-1.f,-10.f),      glm::vec2(0.f,0.f),   glm::vec3(0.f,1.f,0.f),
		//glm::vec3( 10.f,-1.f,10.f),       glm::vec2(1.f,1.f),   glm::vec3(0.f,1.f,0.f),
		glm::vec3( -10.f,-1.f,10.f),      glm::vec2(0.f,1.f),   glm::vec3(0.f,1.f,0.f),//3
	};
	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};
	for(unsigned int i=0;i<sizeof(planevertices)/sizeof(Vertex);i++)
	{
		x_vertices.push_back(planevertices[i]);
	}
	for (unsigned int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++)
	{
		x_indices.push_back(indices[i]);
	}

	x_setup_mesh();

}

void Mesh::SetTransformations(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	x_ModelMatrix = glm::translate(x_ModelMatrix, position);
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	x_ModelMatrix = glm::rotate(x_ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 0.f, 1.f));
	x_ModelMatrix = glm::scale(x_ModelMatrix, scale);
}

void Mesh::BindMesh()
{
	glBindBuffer(GL_ARRAY_BUFFER, x_vbo);
	glBindVertexArray(x_vao);
}