#include "EnginePCH.h"
#include "ModelRender.h"

namespace neu
{
    FACTORY_REGISTER(ModelRender)

    void neu::ModelRender::Update(float dt)
    {
    }

    void neu::ModelRender::Draw(Renderer& renderer)
    {
        material->Bind();
        material->program->SetUniform("u_model", owner->transform.GetMatrix());
        model->Draw(GL_TRIANGLES);
    }

    void ModelRender::Read(const serial_data_t& value)
    {
        Object::Read(value);

        std::string modelName;
        SERIAL_READ_NAME(value, "model", modelName);

        model = Resources().Get<Model>(modelName);

        std::string materialName;
        SERIAL_READ_NAME(value, "material", materialName);

        material = Resources().Get<Material>(materialName);
    }
    void ModelRender::UpdateGui()
    {
    }
}