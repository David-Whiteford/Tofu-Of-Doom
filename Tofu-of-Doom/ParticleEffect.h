#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtx/norm.hpp"
#include "stb_image.h"

#include <SFML/System.hpp>
#include <algorithm>

class ParticleEffect
{
public:
	ParticleEffect(sf::Time& t_deltaTime);
	~ParticleEffect();
	int FindUnusedParticle();
	void SortParticles();
	void generateParticles(glm::vec3 t_cameraPosition);
	void drawParticles();

private:
	sf::Time &delta;

	GLfloat g_vertex_buffer_data[12] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f };

	struct Particle
	{
		glm::vec3 pos;
		glm::vec3 speed;
		float size;
		float angle;
		float weight;
		float life; // Remaining life of the particle - If it's less than zero then the particle is dead
		float cameradistance; // Squared distance to the camera - if dead, it's -1.0f

		// Particle colour (RGBA)
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

		// Overload the less than operator
		bool operator<(const Particle& particle) const
		{
			// Sort in reverse order and draw far particles first
			return this->cameradistance > particle.cameradistance;
		}
	};

	const static int MaxParticles = 10000;
	Particle ParticlesContainer[MaxParticles];
	int LastUsedParticle = 0;

	// And now for some OpenGL stuff
	GLfloat* g_particule_position_size_data;
	GLubyte* g_particule_color_data;
	GLuint billboard_vertex_buffer;
	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
};

#endif // !PARTICLEEFFECT_H
