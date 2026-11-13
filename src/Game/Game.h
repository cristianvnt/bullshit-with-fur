#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Utils/Settings.h"
#include "Components/Buffers/VertexBuffer.h"
#include "Components/Buffers/VertexArray.h"
#include "Components/Buffers/VertexBufferLayout.h"
#include "Components/Shader.h"
#include "Components/Mesh.h"
#include "Components/Material.h"

class Game
{
private:
	Window _window;
	Renderer _renderer;
	Settings _settings;

	// for test
	VertexBuffer* _vbo = nullptr;
	IndexBuffer* _ibo = nullptr;
	VertexArray* _vao = nullptr;
	VertexBufferLayout* _layout = nullptr;
	Shader* _shader = nullptr;

	Mesh _mesh;
	Material _material;

public:
	Game() = default;
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	bool Init(const Settings& settings);
	void Run();
};
