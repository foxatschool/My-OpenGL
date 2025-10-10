
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // initialize variables
 
    //--OpenGL
    std::vector<neu::vec3> points = { {-0.5f, -0.5f, 0}, {0.5f, -0.5f, 0 }, {0.0f, 0.5f, 0} };
    std::vector<neu::vec3> colors = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
	float angle = 0;

    GLuint vbo[2];
    glGenBuffers(1, vbo);

	//vertex buffer (position)
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * points.size(), points.data(), GL_STATIC_DRAW);

    //vertex buffer (Color)
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(neu::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
    
    //vertex array
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	//Position
    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //Color
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //vertex shader
    std::string vsSource;
	neu::file::ReadTextFile("Shaders/Basic.vert", vsSource);
    const char* vsCstr = vsSource.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsCstr, NULL);
	glCompileShader(vs);

    // fragment shader
	std::string fsSource;
	neu::file::ReadTextFile("Shaders/Basic.frag", fsSource);
	const char* fsCstr = fsSource.c_str();
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsCstr, NULL);
	glCompileShader(fs);

    int success;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::string infoLog(512, '\0');  // pre-allocate space
        GLsizei length;
        glGetShaderInfoLog(fs, (GLsizei)infoLog.size(), &length, &infoLog[0]);
        infoLog.resize(length);

        LOG_WARNING("Shader compilation failed: {}", infoLog);
    }

	GLuint shProgram = glCreateProgram();
	glAttachShader(shProgram, vs);
	glAttachShader(shProgram, fs);
	glLinkProgram(shProgram);
	glUseProgram(shProgram);

    // uniform
    GLint uniform = glGetUniformLocation(shProgram, "u_time");
    ASSERT(uniform != -1);

    glGetProgramiv(shProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        std::string infoLog(512, '\0');  // pre-allocate space
        GLsizei length;
        glGetProgramInfoLog(shProgram, (GLsizei)infoLog.size(), &length, &infoLog[0]);
        infoLog.resize(length);

        LOG_WARNING("Shader compilation failed: {}", infoLog);
    }


    // initialize scene

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

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        glUniform1f(uniform, neu::GetEngine().GetTime().GetTime());

        
		//// update the triangle scale based on input
  //      if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_W)) 
  //      {
  //          for (auto& p : points) p *= 1.1f;
		//}
  //      if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_S)) 
  //      {
  //          for (auto& p : points) p *= 0.9f;
  //      }

		//// update the triangle location based on mouse location
		//auto mousePos = neu::GetEngine().GetInput().GetMousePosition();
  //      float x = mousePos.x / neu::GetEngine().GetRenderer().GetWidth();
		//float y = mousePos.y / neu::GetEngine().GetRenderer().GetHeight();
  //      
		//neu::vec2 mousse = neu::GetEngine().GetInput().GetMousePosition();
  //      neu::vec2 position;
  //      position.x = neu::math::Remap(0.0f, (float)neu::GetEngine().GetRenderer().GetWidth(), -1.0f, 1.0f, mousePos.x);
  //      position.y = -neu::math::Remap(0.0f, (float)neu::GetEngine().GetRenderer().GetHeight(), -1.0f, 1.0f, mousePos.y);

  //      if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A))
  //      {
  //          angle += 0.1f;
		//}
  //      if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D))
  //      {
  //          angle -= 0.1f;
  //      }


        // draw
        
        //neu::vec3 color{ 0, 0, 0 };
        //neu::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        neu::GetEngine().GetRenderer().Clear();
        
		glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)points.size());

        /*
		glLoadIdentity();
        glPushMatrix();

		glTranslatef(position.x, position.y, 0);
		glRotatef(angle, 0, 0, 1);

		// Create a simple triangle using 3 points and colors you define
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < points.size(); i++)
        {
            glColor3f(colors[i].r, colors[i].g, colors[i].b);
            glVertex3f(points[i].x, points[i].y, points[i].z);
		}
        glEnd();
        */

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
