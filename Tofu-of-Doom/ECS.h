#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

// This function will be put into place whereever we use it
inline ComponentID getComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}