#include <iostream>
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "tests/TestClearColor.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int wWidth = 960;
	int wHeight = 540;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(wWidth, wHeight, "Shri Radha", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	std::cout << "GLFW: " << glfwGetVersionString() << std::endl;
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Vsync

	// ImGui INIT
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	/*Glew Init*/
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error Initializing Glew" << std::endl;
		return -1;
	}


	{ /*A seperate Scope so that the destructors of the BufferObjects are called before
	  glfwTerminate to avoid a infinite Loop */

	  /*
  float vertices[]	= {
	 -0.5f, -0.5f, 0.0f, 0.0f, // Bottom Left (vPosX, vPosY, TexPosX, TPosY)
	  0.5f, -0.5f, 1.0f, 0.0f, // Bottom Right
	  0.5f,  0.5f, 1.0f, 1.0f, // Top Right
	 -0.5f,  0.5f, 0.0f, 1.0f // Top left
  };
	  */

		float vertices[] = {
		   -150.0f,   -150.0f, 0.0f, 0.0f, // Bottom Left (vPosX, vPosY, TexPosX, TPosY)
			150.0f,	  -150.0f, 1.0f, 0.0f, // Bottom Right
			150.0f,   150.0f, 1.0f, 1.0f, // Top Right
			-150.0f,  150.0f, 0.0f, 1.0f // Top left
		};


		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		// Blending
		GL(glEnable(GL_BLEND));
		GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		VertexBuffer vb(vertices, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.PushFloat(2);
		layout.PushFloat(2);
		va.AddBuffer(vb, layout);


		IndexBuffer ib(indices, 6);

		glm::mat4 projMat = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // camera


		Shader basicShader("src/resources/shaders/basic.shader");
		basicShader.Bind();


		Texture radhikaRaniTexture("src/resources/textures/RadhikaRani.png");
		Texture radhaKrsnaTexture("src/resources/textures/RadhaKrsna.png");



		va.UnBind();
		vb.UnBind();
		ib.UnBind();
		basicShader.UnBind();

		int count = 0;

		Renderer renderer;
		bool ImGuiShowDemoWindow = false;

		glm::vec3 translationObjA = glm::vec3(200, 200, 0);
		glm::vec3 translationObjB = glm::vec3(510, 248, 0);
		/* Loop until the user closes the window */

		//Test
		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };


		while (!glfwWindowShouldClose(window))
		{


			/* Poll for and process events */
			glfwPollEvents();



			/* Render here */
			/*renderer.ClearColor(0.0, 0.0, 0.0, 0.0);*/
			renderer.Clear();




			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (ImGuiShowDemoWindow)
				ImGui::ShowDemoWindow();
			///-------------------------------
			ImGui::Begin("Controller");

			ImGui::Text("Radhey Shyam");

			ImGui::SliderFloat3("Obj: A", glm::value_ptr(translationObjA), 0, 900);
			ImGui::SliderFloat3("Obj: B", glm::value_ptr(translationObjB), 0, 900);
			ImGui::ColorEdit4("ClearColor", clearColor); 

			ImGui::NewLine();
			ImGui::Text("Counter:");

			if (ImGui::Button("+"))
				count++;
			ImGui::SameLine();
			ImGui::Text("Count: %d", count);
			ImGui::SameLine();
			if (ImGui::Button("-"))
				count = std::max(0, --count);

			

			/// Rendering
			renderer.ClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			renderer.Clear();


			basicShader.Bind();

			// Obj One
			{
				glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translationObjA);
				glm::mat4 mvp = projMat * viewMat * modelMat;
				basicShader.SetUniformMat4("u_MVP", mvp);
				radhikaRaniTexture.Bind();
				basicShader.SetUniform1i("u_Texture", 0);

				renderer.Draw(va, ib, basicShader);
			}


			// Second Obj
			{

				glm::mat4 modelMat = modelMat = glm::translate(glm::mat4(1.0f), translationObjB);
				glm::mat4 mvp = projMat * viewMat * modelMat;
				basicShader.SetUniformMat4("u_MVP", mvp);
				radhaKrsnaTexture.Bind();
				basicShader.SetUniform1i("u_Texture", 0);
				renderer.Draw(va, ib, basicShader);
			}



			/// End Rendering 



			// Fps
			ImGui::Text("Application average %.3f ms/frame \n(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();





			//----------------------
			// ImGui
			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

		}

		/*Extra Scope ends Here*/

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}