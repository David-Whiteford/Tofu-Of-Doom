#pragma warning(disable : 4996)

#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "libs/glew/glew.h"
#include "libs/glm/glm.hpp"
#include "VBOIndexer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace tk
{
	class ModelLoader
	{
	public:
		static bool loadOBJ(const char *path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, 
			std::vector<glm::vec3> &out_normals, std::vector<unsigned short> &out_indices);
	};
}

#endif // !MODELLOADER_H
