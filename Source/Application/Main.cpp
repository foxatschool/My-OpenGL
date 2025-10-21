
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // initialize variables
 
    //--OpenGL
    /*std::vector<neu::vec3> points = { {-0.5f, -0.5f, 0}, {0.5f, -0.5f, 0 }, {0.0f, 0.5f, 0} };
    std::vector<neu::vec3> colors = { {1, 0, 0},         {0, 1, 0},         {0, 0, 1} };
	std::vector<neu::vec2> textcoord{ {0, 0},            {0.5f, 1.0f},      {1, 1} };*/

    struct Vertex
    {
        neu::vec3 position;
        neu::vec3 color;
        neu::vec2 textcoord;
    };

    std::vector<Vertex> vertices
    {
        {{-0.5f, -0.5f, 0}, {0, 0, 1}, {0, 0}},
        {{-0.5f, 0.5f, 0 }, {0, 0, 1}, {0, 1} },
	    {{0.5f, 0.5f, 0},   {0, 0, 1}, {1, 1} },
	    {{0.5f, -0.5f, 0},  {0, 0, 1}, {1, 0} }
    };

    std::vector<GLushort> indices{ 0, 1, 2, 2, 3, 0 };

    auto model3d = std::make_shared<neu::Model>();
    model3d->Load("models/sphere.obj");
        
    // Shaders
    auto vs = neu::Resources().Get<neu::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
    auto fs = neu::Resources().Get<neu::Shader>("shaders/basic.frag", GL_FRAGMENT_SHADER);

    // Program
    auto program = std::make_shared<neu::Program>();
    program->AttachShader(vs);
    program->AttachShader(fs);
    program->Link();
    program->Use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

	glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    program->SetUniform("u_model", model);
    program->SetUniform("u_projection", projection);

    neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("textures/beast.png");
	program->SetUniform("u_texture", 0);

    // initialize scene
    glm::vec3 eye{ 0, 0, 5 };

    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // update
        neu::GetEngine().Update();
        float dt = neu::GetEngine().GetTime().GetDeltaTime();
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}

        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) {
            eye.x -= 0.1f * dt;
        }
        if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) {
            eye.x -= 0.1f * dt;
        }

        glm::mat4 view = glm::lookAt(eye, eye + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        program->SetUniform("u_view", view);


        // draw
        neu::GetEngine().GetRenderer().Clear();
        model3d->Draw(GL_TRIANGLES);
        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
