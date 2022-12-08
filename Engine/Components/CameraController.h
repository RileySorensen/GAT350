#pragma once
#include "Framework/Component.h" 

namespace neu
{
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

		void Update() override;
		void Initialize() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		float sensitivity = 0.11;
		float speed = 0;
	private:
		float m_yaw; // left right
		float m_pitch; // up down
	};
}