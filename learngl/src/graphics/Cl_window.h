#pragma once
#include"dependencies.h"
namespace SJ_engine {
	class Cl_window
	{
	public:
		Cl_window(int Windth, int Height, const char* Title);
		~Cl_window();
		bool Init();
		int width, height;
		const char* Title;
		const bool closed();
		void Update();
		void clear();
	private:
		int x_Win_Height, x_Win_Width;
		const char* x_Name;
		GLFWwindow* x_window;

	};
}