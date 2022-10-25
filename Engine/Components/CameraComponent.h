#pragma once
#include "Framework/Component.h"
#include "Math/Matrix3x3.h"

namespace neu
{
	class CameraComponent : public Component
	{

	public:
		CLASS_DECLARATION(CameraComponent)

			void Update() override;


		void SetPerspective(float fov, float aspectRatio, float near, float far);

		const glm::mat4& GetProjection() { return m_projection; }
		const glm::mat4& GetView() { return m_view; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::mat4 m_projection{ 1 };
		glm::mat4 m_view{ 1 };
	};
}