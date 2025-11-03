#pragma once
#include "Resources/Resource.h"
#include "GUI/GUI.h"
#include <glm/vec2.hpp>

namespace neu
{
	class Program;
	class Texture;

	class Material : public Resource, GUI
	{
	public:
		Material() = default;
		~Material() = default;

		bool Load(const std::string& filename);
		void Bind();
	public:

		res_t<Texture> baseMap;
		res_t<Program> program;
		glm::vec3 baseColor{ 1,1,1 };
		res_t<Texture> specularMap;

		float shininess{ 2 };
		glm::vec2 tiling{ 1,1 };
		glm::vec2 offset{ 0,0 };


		// Inherited via GUI
		void UpdateGui() override;

	};
}