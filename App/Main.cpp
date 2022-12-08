#include "Engine.h"
#include <iostream> 

#define POST_PROCESS
					
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
	neu::g_gui.Initialize(neu::g_renderer);


	//create framebuffer texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(512, 512);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	//create framebuffer

	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/postprocess.scn");

	bool quit = false;
	float x;

	float ri = 1;

	glm::vec3 rot{ 0,0,0 };
	while (!quit)
	{
		neu::Engine::Instance().Update();


		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;


		
		auto material = neu::g_resources.Get<neu::Material>("Material/multi.mtrl");
		auto material2 = neu::g_resources.Get<neu::Material>("Material/box.mtrl");
		auto material3 = neu::g_resources.Get<neu::Material>("Material/ogre.mtrl");
		
		
		auto actor = scene->GetActorFromName("squirrel");
		auto light = scene->GetActorFromName("Light");

		if (actor)
		{
			//actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}
		if (light)
		{
			//light->m_transform.position = pos;
		}
		//auto program = neu::g_resources.Get<neu::Program>("shaders/lit/texture.prog");

		/*if (program)
		{
			program->Use();

			program->SetUniform("ri", ri);
		}*/
		auto program = neu::g_resources.Get<neu::Program>("shaders/postprocess/postprocess.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("offset", neu::g_time.time);
		}

		ImGui::Begin("Hello");
		ImGui::Button("Press Me");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction", &ri, 0.01, 1, 3);
		ImGui::End();

		scene->Update();

#ifdef POST_PROCESS 
		
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		
		neu::g_renderer.SetViewport(0, 0, framebuffer -> GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);

		
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(neu::g_renderer);
			}
		}
#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif



		/*{
			auto actor = scene->GetActorFromName("Screen");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();

		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);

		framebuffer->Unbind();

		{
			auto actor = scene->GetActorFromName("Screen");
			if (actor)
			{
				actor->SetActive(true);
			}
		}
	

		
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);*/

		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;
}