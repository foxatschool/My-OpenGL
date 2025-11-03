#pragma once
#include "RendererComponent.h"

namespace neu
{
	class ModelRender : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(ModelRender);

		//std::unique_ptr<Object> Clone() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const serial_data_t& value);
		void UpdateGui() override;

	public:
		res_t<Model> model;
		res_t<Material> material;

	};
}