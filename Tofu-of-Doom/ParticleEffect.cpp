#include "ParticleEffect.h"

/// <summary>
/// Constructor for the ParticleEffect class.
/// </summary>
ParticleEffect::ParticleEffect(sf::Time& t_deltaTime) : delta(t_deltaTime)
{
	g_particule_position_size_data = new GLfloat[MaxParticles * 4];
	g_particule_color_data = new GLubyte[MaxParticles * 4];
}

/// <summary>
/// Destructor for the ParticleEffect class.
/// </summary>
ParticleEffect::~ParticleEffect()
{
	delete g_particule_position_size_data;
	delete g_particule_color_data;
}

/// <summary>
/// Finds a Particle in ParticlesContainer which isn't used yet.
/// </summary>
int ParticleEffect::FindUnusedParticle()
{
	for (int i = LastUsedParticle; i < MaxParticles; i++)
	{
		if (ParticlesContainer[i].life < 0)
		{
			LastUsedParticle = i;
			return i;
		}
	}

	for (int i = 0; i < LastUsedParticle; i++)
	{
		if (ParticlesContainer[i].life < 0)
		{
			LastUsedParticle = i;
			return i;
		}
	}

	return 0; // All particles are taken, override the first one
}

/// <summary>
/// Sorts semi-transparent objects from back to front for the blending to be correct.
/// </summary>
void ParticleEffect::SortParticles()
{
	std::sort(&ParticlesContainer[0], &ParticlesContainer[MaxParticles]);
}

/// <summary>
/// Generates particles.
/// </summary>
void ParticleEffect::generateParticles(glm::vec3 t_cameraPosition)
{
	// Generate 10 new particles each millisecond but limit to 16 ms (60 fps), or if you have 1 long frame (1 sec) then
	// the new particles will be huge and the next frame even longer
	int newparticles = (int)(delta.asMilliseconds() * 10000.0);

	if (newparticles > (int)(0.016f * 10000.0))
	{
		newparticles = (int)(0.016f * 10000.0);
	}

	for (int i = 0; i < newparticles; i++)
	{
		int particleIndex = FindUnusedParticle();
		ParticlesContainer[particleIndex].life = 5.0f; // This particle will live 5 seconds
		ParticlesContainer[particleIndex].pos = glm::vec3(0, 0, -20.0f);

		float spread = 1.5f;
		glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);

		// Not the best way to generate random directions
		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);

		ParticlesContainer[particleIndex].speed = maindir + randomdir * spread;

		// Another dodgy way to generate random numbers, might use the <random> library instead
		ParticlesContainer[particleIndex].r = rand() % 256;
		ParticlesContainer[particleIndex].g = rand() % 256;
		ParticlesContainer[particleIndex].b = rand() % 256;
		ParticlesContainer[particleIndex].a = (rand() % 256) / 3;

		ParticlesContainer[particleIndex].size = (rand() % 1000) / 2000.0f + 0.1f;
	}

	// Simulate all particles
	int ParticlesCount = 0;

	for (int i = 0; i < MaxParticles; i++)
	{
		// Particle& p = ParticlesContainer[i]; // shortcut

		if (ParticlesContainer[i].life > 0.0f)
		{
			// Decrease life
			ParticlesContainer[i].life -= delta.asMilliseconds();

			if (ParticlesContainer[i].life > 0.0f)
			{
				// Simulate simple physics : gravity only, no collisions
				ParticlesContainer[i].speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)delta.asMilliseconds() * 0.5f;
				ParticlesContainer[i].pos += ParticlesContainer[i].speed * (float)delta.asMilliseconds();
				ParticlesContainer[i].cameradistance = glm::length2(ParticlesContainer[i].pos - t_cameraPosition);

				// Fill the GPU buffer
				g_particule_position_size_data[4 * ParticlesCount + 0] = ParticlesContainer[i].pos.x;
				g_particule_position_size_data[4 * ParticlesCount + 1] = ParticlesContainer[i].pos.y;
				g_particule_position_size_data[4 * ParticlesCount + 2] = ParticlesContainer[i].pos.z;

				g_particule_position_size_data[4 * ParticlesCount + 3] = ParticlesContainer[i].size;

				g_particule_color_data[4 * ParticlesCount + 0] = ParticlesContainer[i].r;
				g_particule_color_data[4 * ParticlesCount + 1] = ParticlesContainer[i].g;
				g_particule_color_data[4 * ParticlesCount + 2] = ParticlesContainer[i].b;
				g_particule_color_data[4 * ParticlesCount + 3] = ParticlesContainer[i].a;
			}
			else
			{
				// Particles that just died will be put at the end of the buffer in SortParticles()
				ParticlesContainer[i].cameradistance = -1.0f;
			}

			ParticlesCount++;
		}
	}

	SortParticles();

	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);

	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);
}

/// <summary>
/// Draw particles.
/// </summary>
void ParticleEffect::drawParticles()
{
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glVertexAttribPointer(
		0, // attribute. No particular reason for 0, but must match the layout in the shader.
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);

	// 2nd attribute buffer : positions of particles' centers
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glVertexAttribPointer(
		1, // attribute. No particular reason for 1, but must match the layout in the shader.
		4, // size : x + y + z + size => 4
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);

	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glVertexAttribPointer(
		2, // attribute. No particular reason for 1, but must match the layout in the shader.
		4, // size : r + g + b + a => 4
		GL_UNSIGNED_BYTE, // type
		GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
		0, // stride
		(void*)0 // array buffer offset
	);

	// These functions are specific to glDrawArrays*Instanced*.
	// The first parameter is the attribute buffer we're talking about.
	// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
	// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
	glVertexAttribDivisor(2, 1); // color : one per quad -> 1

	// Draw the particules !
	// This draws many times a small triangle_strip (which looks like a quad).
	// This is equivalent to :
	// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
	// but faster.
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1000);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}