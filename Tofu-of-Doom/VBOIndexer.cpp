#include "VBOIndexer.h"

/// <summary>
/// This function finds similar vertices (Fast method using std::map)
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
/// Create an indexed VBO
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