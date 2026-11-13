#pragma once

#include "Shader.h"

struct Material
{
	Shader* shader{};
	glm::vec4 color{ 1.f };
};
