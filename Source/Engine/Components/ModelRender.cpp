#include "EnginePCH.h"
#include "ModelRender.h"

namespace neu
{
    FACTORY_REGISTER(ModelRender)

    void ModelRender::Update(float dt)
    {
    }

    void ModelRender::Draw(Renderer& renderer)
    {
        //if (material)
        {
            material->Bind();
            material->program->SetUniform("u_model", owner->transform.GetMatrix());
        }

        glDepthMask(enableDepth);
        glCullFace(cullFace);

        //if (model) 
        model->Draw(GL_TRIANGLES);
    }

    void ModelRender::Read(const serial_data_t& value)
    {
        Object::Read(value);

        std::string modelName;
        SERIAL_READ_NAME(value, "model", modelName);
        std::cout << modelName + " ";
        model = Resources().Get<Model>(modelName);

        std::string materialName;
        SERIAL_READ_NAME(value, "material", materialName);
        material = Resources().Get<Material>(materialName);

        SERIAL_READ(value, enableDepth);

        std::string cullFaceName;
        SERIAL_READ_NAME(value, "cullFace", cullFaceName);
        if (equalsIgnoreCase(cullFaceName, "front")) cullFace = GL_FRONT;
    }

    void ModelRender::UpdateGui()
    {
        std::string text;

        text = (model) ? model->name : "none";
        ImGui::Text("Model: %s", text.c_str());
        Editor::GetDialogResource<Model>(model, "ModelDialog", "Open model", "Model file (*.obj;*.fbx;*.glb){.obj,.fbx,.glb},.*");

            

        text = (material) ? material->name : "none";
        ImGui::Text("Material: %s", text.c_str());
        Editor::GetDialogResource<Material>(material, "MaterialDialog", "Open material", "material file (*.mat){.mat},.*");
    }
}