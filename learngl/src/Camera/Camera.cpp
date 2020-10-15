#include "Camera.h"
namespace SJ_engine {
	namespace SJ_camera {
		void Camera::reset_position()
		{
			x_front = glm::vec3(0.f, 0.f, -1.f);
			x_position = x_initialPos;
			x_yaw = 0.f;
			x_pitch = 0.f;
		}
		void Camera::Nav(Cl_window* obj,SJ_shader::shader* shaderObj)
		{

			shaderObj->SetUniformMatrix4f("u_View", 1,Cal_ViewMatrix());
			shaderObj->SetUniformMatrix4f("u_Projection", 1,Cal_projectionMatrix(obj->AspectRatio));

		}
		Camera::Camera(glm::vec3 intialPos, float movespeed, float turnspeed, float yaw, float pitch)
		{
			x_position = intialPos;
			x_initialPos = x_position;
			x_WorldUp = glm::vec3(0.f, 1.f, 0.f);
			x_front = glm::vec3(0.f, 0.f, -1.f);
			x_yaw = yaw;
			x_pitch = pitch;
			x_movementspeed = movespeed;
			x_turnspeed = turnspeed;
			update();


		}
		void Camera::update()
		{
			x_front.x = cos(glm::radians(x_yaw)) * cos(glm::radians(x_pitch));
			x_front.y = sin(glm::radians(x_pitch));
			x_front.z = sin(glm::radians(x_yaw)) * cos(glm::radians(x_pitch));
			x_front = glm::normalize(x_front);
			x_right = glm::normalize(glm::cross(x_front, x_WorldUp));
			x_up = glm::normalize(glm::cross(x_right, x_front));

		}
		Camera::~Camera()
		{

		}

		void Camera::keycontrol(Cl_window* obj,SJ_shader::shader* shaderObj)
		{
			float velocity = get_deltaTime() * x_movementspeed;
			if (obj->keys[GLFW_KEY_W] == true)
			{
				x_position += x_front * velocity;
			}
			if (obj->keys[GLFW_KEY_S] == true)
			{
				x_position -= x_front * velocity;
			}
			if (obj->keys[GLFW_KEY_A] == true)
			{
				x_position -= x_right * velocity;
			}
			if (obj->keys[GLFW_KEY_D] == true)
			{
				x_position += x_right * velocity;
			}
			if (obj->keys[GLFW_KEY_W] || obj->keys[GLFW_KEY_S] || obj->keys[GLFW_KEY_A] || obj->keys[GLFW_KEY_D] || obj->keys[GLFW_KEY_LEFT_ALT])
			{
				if (obj->mousebuttons[GLFW_MOUSE_BUTTON_LEFT] == true)
				{
					obj->xChange *= x_turnspeed;
					obj->yChange *= x_turnspeed;
					x_yaw += (float)obj->xChange;
					x_pitch += (float)obj->yChange;	
					if (x_pitch > 89.f)
					{
						x_pitch = 89.f;
					}
					if (x_pitch < -89.f)
					{
						x_pitch = -89.f;
					}
					update();
				}

			}
			if (obj->keys[GLFW_KEY_F] == true)
			{
				reset_position();
				update();
			}
			Nav(obj,shaderObj);
		}

		float Camera::get_deltaTime()
		{
			float now = (float)glfwGetTime();
			x_DeltaTime = now - x_lastTime;
			x_lastTime = now;
			return x_DeltaTime;
		}

		glm::mat4 Camera::Cal_ViewMatrix()
		{
			return glm::lookAt(x_position, x_position + x_front, x_WorldUp);
		}

		glm::mat4 Camera::Cal_projectionMatrix(float aspect)
		{
			return glm::perspective(glm::radians(55.f), aspect, 0.1f, 100.f);
		}
	}
}