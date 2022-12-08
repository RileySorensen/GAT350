#pragma once
#include "Framework/Component.h"

namespace neu
{
	class Program;

	class LightComponent : public Component
	{
	public:
		enum class Type
		{
			Point,
			Directional,
			Spot
		};
	public:
		CLASS_DECLARATION(LightComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void setProgram(std::shared_ptr<Program> program, int index);

	public:
		Type type = Type::Point;
		glm::vec3 color{ 0 };
		float cutoff{ 45.0f };
		float exponent{ 50.0f };
	
	};
}