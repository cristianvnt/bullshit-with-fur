#include "Game.h"

#include "Utils/Logger.h"
#include "Utils/Paths.h"
#include "Utils/DeltaTimer.h"

#include "glfw/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

float vertices[] = {
	-0.5f, -0.5f, -0.5f, // 0
	 0.5f, -0.5f, -0.5f, // 1
	 0.5f,  0.5f, -0.5f, // 2
	-0.5f,  0.5f, -0.5f, // 3
	-0.5f, -0.5f,  0.5f, // 4
	 0.5f, -0.5f,  0.5f, // 5
	 0.5f,  0.5f,  0.5f, // 6
	-0.5f,  0.5f,  0.5f  // 7
};

unsigned int indices[] = {
	0, 1, 2,  2, 3, 0, // Back face
	4, 5, 6,  6, 7, 4, // Front face
	4, 0, 3,  3, 7, 4, // Left face
	1, 5, 6,  6, 2, 1, // Right face
	3, 2, 6,  6, 7, 3, // Top face
	4, 5, 1,  1, 0, 4  // Bottom face
};

Game::~Game()
{
	delete _vao;
	delete _vbo;
	delete _ibo;
	delete _layout;
	delete _shader;
}

bool Game::Init(const Settings& settings)
{
	_settings = settings;
	if (!_window.Init(settings.window))
	{
		std::cout << "Failed to initialize the window.\n";
		return false;
	}

	_renderer.Init();

	_vbo = new VertexBuffer(vertices, sizeof(vertices));

	_layout = new VertexBufferLayout();
	_layout->Push<float>(3);

	_vao = new VertexArray();
	_vao->AddBuffer(*_vbo, *_layout);

	_ibo = new IndexBuffer(indices, 36);

	_shader = new Shader(ShaderPath("shader", ".vert"), ShaderPath("shader", ".frag"));

	_mesh.vao = _vao;
	_mesh.ibo = _ibo;
	_mesh.vertexCount = 36;

	_material.shader = _shader;
	_material.color = glm::vec4(0.2f, 0.7f, 0.9f, 1.0f);

	return true;
}

void Game::Run()
{
	DeltaTimer deltaTimer;

	while (!_window.ShouldClose())
	{
		_window.PollEvents();

		float dt = deltaTimer.GetDeltaTime();

		// render
		_renderer.BeginFrame();

		glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f));
		glm::mat4 proj = glm::perspective(glm::radians(70.f), (float)_settings.window.width / _settings.window.height, 0.1f, 100.f);
		glm::mat4 model = glm::mat4(1.f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		_renderer.DrawObject(_mesh, _material, model, view, proj);

		_window.SwapBuffers();

		deltaTimer.Update();
	}
}
