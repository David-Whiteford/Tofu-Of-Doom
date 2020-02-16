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
		static bool isNear(float v1, float v2);
		static bool getSimilarVertexIndex(
			glm::vec3& in_vertex,
			glm::vec2& in_uv,
			glm::vec3& in_normal,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals,
			unsigned short& result);
		void indexVBO_slow(
			std::vector<glm::vec3>& in_vertices,
			std::vector<glm::vec2>& in_uvs,
			std::vector<glm::vec3>& in_normals,

			std::vector<unsigned short>& out_indices,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals);
		static bool getSimilarVertexIndex_fast(PackedVertex& packed, std::map<PackedVertex, unsigned short>& VertexToOutIndex, unsigned short& result);
		void indexVBO(
			std::vector<glm::vec3>& in_vertices,
			std::vector<glm::vec2>& in_uvs,
			std::vector<glm::vec3>& in_normals,

			std::vector<unsigned short>& out_indices,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals);
		static void indexVBO_TBN(
			std::vector<glm::vec3>& in_vertices,
			std::vector<glm::vec2>& in_uvs,
			std::vector<glm::vec3>& in_normals,
			std::vector<glm::vec3>& in_tangents,
			std::vector<glm::vec3>& in_bitangents,

			std::vector<unsigned short>& out_indices,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals,
			std::vector<glm::vec3>& out_tangents,
			std::vector<glm::vec3>& out_bitangents);
		static void VBOindexer(
			std::vector<glm::vec3>& in_vertices,
			std::vector<glm::vec2>& in_uvs,
			std::vector<glm::vec3>& in_normals,
			std::vector<glm::vec3>& in_tangents,
			std::vector<glm::vec3>& in_bitangents,

			std::vector<unsigned short>& out_indices,
			std::vector<glm::vec3>& out_vertices,
			std::vector<glm::vec2>& out_uvs,
			std::vector<glm::vec3>& out_normals,
			std::vector<glm::vec3>& out_tangents,
			std::vector<glm::vec3>& out_bitangents);
	};
}

#endif // !VBOINDEXER_H
