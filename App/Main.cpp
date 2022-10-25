#include "Engine.h" 
#include <iostream> 


float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
						
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
						
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
						
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
						
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
						
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};						
int main(int argc, char**argv)
{
	LOG("Application Started ...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	LOG("Engine Initialized . . .");

	neu::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Created . . .");

	auto scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;
	bool success = neu::json::Load("scenes/basic.scn", document);
	if (!success)
	{
		LOG("Error Loading Scene File %s.", "scenes/basic.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}
	

	//std::shared_ptr<neu::VertexBuffer> vb = neu::g_resources.Get<neu::VertexBuffer>("box");
	//vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	//vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	//vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	//vb->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	neu::Vector2 position;

	glm::mat4 mx{1};
	
	//create the material
	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("Material/ogre.mtrl");
	material->Bind();

	material->GetProgram()->SetUniform("scale", 0.05f);

	glm::mat4 model{ 1 };
	float aspectRatio = neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight();
	glm::mat4 projection = glm::perspective(45.0f, aspectRatio,0.1f,100.0f);
	glm::vec3 cameraPosition{ 0,0,2 }; 
	float speed = 3;
	
	auto m = neu::g_resources.Get<neu::Model>("models/ogre.obj");

	std::vector<neu::Transform> transforms;
	for (size_t i = 0; i < 100; i++) {
		transforms.push_back({ {neu::random((i + 1) * -1,i + 1),neu::random((i + 1) * -1,i + 1),neu::random(-10,10)},{neu::random(360),neu::random(360),neu::random(360)} });
	}

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;
		

		if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.x -= speed * neu::g_time.deltaTime;
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.x += speed * neu::g_time.deltaTime;
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.y += speed * neu::g_time.deltaTime;
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_down) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.y -= speed * neu::g_time.deltaTime;
		}
		if (neu::g_inputSystem.GetButtonState(neu::button_left) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.z += speed * neu::g_time.deltaTime;
		}
		if (neu::g_inputSystem.GetButtonState(neu::button_right) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.z -= speed * neu::g_time.deltaTime;
		}

		
		model = glm::eulerAngleXYZ(0.0f,neu::g_time.time, 0.0f);
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });


		//glUniformMatrix4fv(uniform3, 1, GL_FALSE, glm::value_ptr(mx));
		
		//material->GetProgram()->SetUniform("scale", std::sin(neu::g_time.time * 3));
		scene->Update();
		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

		for (size_t i = 0; i < 5; i++)
		{
			
			transforms[i].rotation += glm::vec3{ 10 * std::sin(neu::g_time.time * 2) * neu::g_time.deltaTime, std::cos(neu::g_time.time)* 8 * neu::g_time.deltaTime,std::tan(neu::g_time.time * 2) * neu::g_time.deltaTime * 5 };

			glm::mat4 mvp = projection * view * (glm::mat4)transforms[i];

			material->GetProgram()->SetUniform("mvp", mvp);

			//vb->Draw();
			m->m_vertexBuffer.Draw();
		}


		neu::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;
}