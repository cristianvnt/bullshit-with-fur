#include "Renderer.h"

#include "Components/Mesh.h"
#include "Components/Material.h"

void Renderer::Init()
{
	GL_CHECK(glEnable(GL_DEPTH_TEST));
	GL_CHECK(glEnable(GL_BLEND));
	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::BeginFrame()
{
	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawObject(const Mesh& mesh, const Material& material, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) const
{
	material.shader->Bind();
	material.shader->SetUniformMat4f("u_Model", model);
	material.shader->SetUniformMat4f("u_View", view);
	material.shader->SetUniformMat4f("u_Proj", proj);

	material.shader->SetUniformVec4("u_Color", material.color);

	mesh.vao->Bind();

	if (mesh.ibo != nullptr)
	{
		mesh.ibo->Bind();
		GL_CHECK(glDrawElements(GL_TRIANGLES, mesh.ibo->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
	else
	{
		GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount));
	}
}
