#include "ModelLoader.h"

/// <summary>
/// This function loads an obj format model
/// </summary>
bool tk::ModelLoader::loadOBJ(const char *path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, 
	std::vector<glm::vec3> &out_normals, std::vector<unsigned short> &indices)
{
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<unsigned int> normalIndices;

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE *file = std::fopen(path, "r");

	if (file == NULL)
	{
		std::cout << "File cannot be opened!" << std::endl;

		return false;
	}

	while (true)
	{
		char lineHeader[128];

		// Get the first word of the line
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF)
		{
			break; // EOF = End Of File. Quit the loop.
		}

		if (strcmp(lineHeader, "v") == 0) 
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) 
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate - remove this if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) 
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) 
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			if (matches != 9) 
			{
				printf("File can't be read - make sure file is compatible!\n");
				fclose(file);
				return false;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else 
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}

	fclose(file);

	// Put indices in buffer array
	//tk::VBOIndexer::VBOindexer(temp_out_vertices, temp_out_uvs, temp_out_normals, temp_out_tangents, temp_out_bitangents, indices, out_vertices, out_uvs, out_normals, tangents, bitangents);

	return true;
}
