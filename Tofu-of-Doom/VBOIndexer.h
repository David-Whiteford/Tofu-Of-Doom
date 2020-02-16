#ifndef VBOINDEXER_H
#define VBOINDEXER_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <map>
#include <string.h>
#include <SFML/Graphics.hpp>

namespace tk
{
	class VBOIndexer
	{
	private:
		struct PackedVertex
		{
			glm::vec3 position;
			glm::vec2 uv;
			glm::vec3 normal;

			bool operator<(const PackedVertex that) const
			{
				return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
			};
		};

	public:
		static bool getSimilarVertexIndex_fast(PackedVertex& packed, std::map<PackedVertex, unsigned short>& VertexToOutIndex, unsigned short& result);
		static void indexVBO(
			std::vector<glm::vec3>& in_vertices,
			std::vector<glm::vec2>& in_uvs,
			std::vector<glm::vec3>& in_normals,
			std::vector<unsigned short>& out_indices,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals);
	};
}

#endif // !VBOINDEXER_H
