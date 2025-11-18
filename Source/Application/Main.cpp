
int main(int argc, char* argv[])
{
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    auto renderTexture = std::make_shared<neu::RenderTexture>();
    renderTexture->Create(512, 512);
    neu::Resources().AddResource("renderTexture", renderTexture);
    
    // initialize scene
    auto scene = std::make_unique<neu::Scene>();
    scene->Load("Scenes/scene02.json");
	scene->Start();

	auto editor = std::make_unique<neu::Editor>();

    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) 
    {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            ImGui_ImplSDL3_ProcessEvent(&e);
        }
        float dt = neu::GetEngine().GetTime().GetDeltaTime();

        // update
        neu::GetEngine().Update();
		scene->Update(dt);
			editor->Begin();
			editor->UpdateGui(*scene);
            


			//draw
			neu::GetEngine().GetRenderer().Clear();

            scene->Draw(neu::GetEngine().GetRenderer());


            // draw ImGui

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			neu::GetEngine().GetRenderer().Present();
        }

        neu::GetEngine().Shutdown();

        return 0;
    }
