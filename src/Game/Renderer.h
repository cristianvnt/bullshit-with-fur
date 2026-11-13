#pragma once

#include "glm/glm.hpp"

struct Mesh;
struct Material;

class Renderer
{
public:
	Renderer() = default;

	void Init();
	void BeginFrame();

	void DrawObject(const Mesh& mesh, const Material& material, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) const;
};
