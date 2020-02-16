#include "VBOIndexer.h"

/// <summary>
/// This function returns true if v1 can be considered equal to v2
/// </summary>
bool tk::VBOIndexer::isNear(float v1, float v2)
{
	return fabs(v1 - v2) < 0.01f;
}

/// <summary>
/// This function searches through all already-exported vertices for a similar one
/// Same position + same UVs + same normal = similar vertex
/// </summary>
bool tk::VBOIndexer::getSimilarVertexIndex(
	glm::vec3& in_vertex,
	glm::vec2& in_uv,
	glm::vec3& in_normal,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals,
	unsigned short& result)
{
	// Crappy linear search
	for (unsigned int i = 0; i < out_vertices.size(); i++)
	{
		if (
			isNear(in_vertex.x, out_vertices[i].x) &&
			isNear(in_vertex.y, out_vertices[i].y) &&
			isNear(in_vertex.z, out_vertices[i].z) &&
			isNear(in_uv.x, out_uvs[i].x) &&
			isNear(in_uv.y, out_uvs[i].y) &&
			isNear(in_normal.x, out_normals[i].x) &&
			isNear(in_normal.y, out_normals[i].y) &&
			isNear(in_normal.z, out_normals[i].z))
		{
			result = i;
			return true;
		}
	}

	// No other vertex could be used instead
	// Vertex is added to VBO
	return false;
}

/// <summary>
/// Create an index VBO (Slow method)
/// </summary>
void tk::VBOIndexer::indexVBO_slow(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals)
{
	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

		// If a similar vertex is already in the VBO, use that vertex instead
		if (found)
		{
			out_indices.push_back(index);
		}
		else // If a similar vertex is not found, then it needs to be added in the output data
		{
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_indices.push_back((unsigned short)out_vertices.size() - 1);
		}
	}
}

/// <summary>
/// This function finds similar vertices (Fast method)
/// </summary>
bool tk::VBOIndexer::getSimilarVertexIndex_fast(PackedVertex& packed, std::map<PackedVertex, unsigned short>& VertexToOutIndex, unsigned short& result)
{
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);

	if (it == VertexToOutIndex.end())
	{
		return false;
	}
	else
	{
		result = it->second;
		return true;
	}
}

/// <summary>
/// Create an index VBO (Fast method)
/// </summary>
void tk::VBOIndexer::indexVBO(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		// If a similar vertex is already in the VBO, use that vertex instead
		if (found)
		{
			out_indices.push_back(index);
		}
		else // If a similar vertex is not found, then it needs to be added in the output data
		{
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

/// <summary>
/// Create an index VBO with tangents and bitangents
/// </summary>
void tk::VBOIndexer::indexVBO_TBN(
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
	std::vector<glm::vec3>& out_bitangents)
{
	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

		// If a similar vertex is already in the VBO, use that vertex instead
		if (found)
		{
			out_indices.push_back(index);

			// Average the tangents and the bitangents
			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];
		}
		else // If a similar vertex is not found, then it needs to be added in the output data
		{
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_tangents.push_back(in_tangents[i]);
			out_bitangents.push_back(in_bitangents[i]);
			out_indices.push_back((unsigned short)out_vertices.size() - 1);
		}
	}
}

void tk::VBOIndexer::VBOindexer(std::vector<glm::vec3>& in_vertices, std::vector<glm::vec2>& in_uvs, std::vector<glm::vec3>& in_normals, std::vector<glm::vec3>& in_tangents, std::vector<glm::vec3>& in_bitangents, std::vector<unsigned short>& out_indices, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, std::vector<glm::vec3>& out_tangents, std::vector<glm::vec3>& out_bitangents)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		// If a similar vertex is already in the VBO, use that vertex instead
		if (found)
		{
			out_indices.push_back(index);

			// Average the tangents and the bitangents
			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];
		}
		else // If a similar vertex is not found, then it needs to be added in the output data
		{
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_tangents.push_back(in_tangents[i]);
			out_bitangents.push_back(in_bitangents[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}