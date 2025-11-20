#pragma once
#include "RendererComponent.h"

namespace neu
{
	class ModelRender : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(ModelRender);

		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const serial_data_t& value);
		void UpdateGui() override;

	public:
		res_t<Model> model;
		res_t<Material> material;

		bool enableDepth{ true };
		GLint cullFace{ GL_BACK };

	};
}