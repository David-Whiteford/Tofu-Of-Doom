#pragma once
#include <iostream>

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

	void setTag(std::string tag) { m_tag = tag; }
	std::string getTag(){ return m_tag; }


private:
	std::string m_tag = "";
};