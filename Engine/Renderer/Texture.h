#pragma once
#include "Math/MathUtils.h"
#include "Resource/Resource.h"
#include "Renderer.h"
#include <string>

struct SDL_Texture;
struct SDL_Surface;
// !! forward declaration for SDL pointers below (SDL likes to use structs)

namespace neu
{
	// !! forward declaration for Renderer below
	class Renderer;

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(std::string filename, ...) override;
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);
		bool CreateTexture(int width, int height);
		bool CreateDepthTexture(int width, int height);

		bool Load(const std::string& filename);
		void SetActive(GLuint uint) { glActiveTexture(uint); }
		void Bind() { glBindTexture(m_target, m_texture); }

		glm::ivec2 GetSize() const;
		static GLenum GetInternalFormat(GLuint format);
		friend class Renderer;
		friend class Framebuffer;

	private:
		void FlipSurface(SDL_Surface* surface);
	protected:
		GLuint m_texture;
		GLenum m_target = GL_TEXTURE_2D;

		int m_width = 0;
		int m_height = 0;

	};
}
