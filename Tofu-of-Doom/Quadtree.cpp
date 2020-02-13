#include "Quadtree.h"

Quadtree::Quadtree(float posX,float posY, float height,float width, int currentLevel, int maxLevel)
{
	
	m_posX = posX;
	m_posY = posY;
	m_width = width;
	m_height = height;
	m_currentLevel = currentLevel;
	m_maxLevel = maxLevel;

	shape.setPosition(m_posX, m_posY);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color(64, 128, 255));
	
	// check we aren't at the end
	if (m_currentLevel == maxLevel) 
	{
		return;
	}

	m_topLeft = new Quadtree(m_posX,m_posY, width / 2.0f, height / 2.0f, m_currentLevel + 1, maxLevel);
	m_topRight = new Quadtree(m_posX + width / 2.0f, m_posY, width / 2.0f, height / 2.0f, m_currentLevel + 1, maxLevel);
	m_bottomLeft = new Quadtree(m_posX, m_posX + height / 2.0f, width / 2.0f, height / 2.0f, m_currentLevel + 1, maxLevel);
	m_bottomRight = new Quadtree(m_posX + width / 2.0f, m_posY + height / 2.0f, width / 2.0f, height / 2.0f, m_currentLevel + 1, maxLevel);
}


Quadtree::~Quadtree()
{
	if (m_currentLevel == m_maxLevel)
	{
		return;
	}

	delete m_topLeft;
	delete m_topRight;
	delete m_bottomLeft;
	delete m_bottomRight;
}

// Add objects into tree
void Quadtree::addObject(GameObject* gameObject)
{
	// check we aint at the end
	if (m_currentLevel == m_maxLevel) 
	{
		gameObjectsVec.push_back(gameObject);
		return;
	}

	// TL
	if (containsObject(m_topLeft, gameObject)) 
	{
		m_topLeft->addObject(gameObject); 
		return;
	}

	// TR
	else if (containsObject(m_topRight, gameObject)) 
	{
		m_topRight->addObject(gameObject); 
		return;
	}

	// BL
	else if (containsObject(m_bottomLeft, gameObject)) 
	{
		m_bottomLeft->addObject(gameObject); 
		return;
	}

	//BR
	else if (containsObject(m_bottomRight, gameObject)) 
	{
		m_bottomRight->addObject(gameObject);
		return;
	}

	// contained in self
	if (containsObject(this, gameObject)) 
	{
		gameObjectsVec.push_back(gameObject);
	}
}

std::vector<GameObject*> Quadtree::getObjectsAt(float x, float y)
{

	checks++;
	std::cout << "checks: " << checks << std::endl;

	// break and return all objects found
	if (m_currentLevel == m_maxLevel) 
	{
		std::cout << "exit" << std::endl;
		return gameObjectsVec;
	}

	std::vector<GameObject*> returnObjects, childReturnObjects;

	if (!gameObjectsVec.empty()) 
	{
		returnObjects = gameObjectsVec;
	}
	
	if (x >  m_posX + m_width / 2.0f && x < m_posX + m_width)
	{
		if (y > m_posY + m_height / 2.0f && y < m_posY + m_height) 
		{
			childReturnObjects = m_bottomRight->getObjectsAt(x, y);


			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());

			return returnObjects;
		}
		else if (y > m_posY && y <= m_posY + m_height / 2.0f) 
		{
			childReturnObjects = m_topRight->getObjectsAt(x, y);


			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());

			//
			return returnObjects;
		}
	}

	else if (x > m_posX && x <= m_posX + m_width / 2.0f) 
	{
		if (y > m_posY + m_height / 2.0f && y < m_posY + m_height) 
		{
			childReturnObjects = m_bottomLeft->getObjectsAt(x, y);

			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());

			return returnObjects;
		}
		else if (y > m_posY && y <= m_posY + m_height / 2.0f) 
		{
			childReturnObjects = m_topLeft->getObjectsAt(x, x);

			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());

			return returnObjects;
		}
	}
	return returnObjects;
}

void Quadtree::clear()
{
	checks = 0;
	if (m_currentLevel == m_maxLevel) 
	{
		gameObjectsVec.clear();
		return;
	}
	// delete ptr references
	else 
	{
		m_topLeft->clear();
		m_topRight->clear();
		m_bottomLeft->clear();
		m_bottomRight->clear();
	}
	if (!gameObjectsVec.empty()) 
	{
		gameObjectsVec.clear();
	}

}

bool Quadtree::containsObject(Quadtree *quad, GameObject *gameObject)
{
	if (gameObject != nullptr && quad != nullptr && m_currentLevel < m_maxLevel + 1)
	{
		// check is within bounds
		return	 !(gameObject->position.x < quad->m_posX ||
			gameObject->position.y < quad->m_posY ||
			gameObject->position.x > quad->m_posX + quad->m_width ||
			gameObject->position.y > quad->m_posY + quad->m_height ||
			gameObject->position.x + gameObject->size < quad->m_posX ||
			gameObject->position.y + gameObject->size < quad->m_posY ||
			gameObject->position.x + gameObject->size > quad->m_posX + quad->m_width ||
			gameObject->position.y + gameObject->size > quad->m_posY + quad->m_height);
	} // end if

	// null ptr
	return false;
}

void Quadtree::draw(sf::RenderTarget& canvas, std::vector<GameObject*> returned) 
{
	//stringstream ss;
	//ss << objects.size();
	//string numObjectsStr = ss.str();
	//text.setString(numObjectsStr);
	//canvas.draw(text);


	canvas.draw(shape);

	if (m_currentLevel != m_maxLevel) {

		for (int i = 0; i < returned.size(); i++)
		{


			if ((m_topLeft->containsObject(m_topLeft, returned.at(i))))
			{
				canvas.draw(shape);
				m_topLeft->draw(canvas, returned);
				break;
			}
			if ((m_topRight->containsObject(m_topRight, returned.at(i))))
			{
				canvas.draw(shape);
				m_topRight->draw(canvas, returned);
				break;
			}
			if ((m_bottomLeft->containsObject(m_bottomLeft, returned.at(i))))
			{
				canvas.draw(shape);
				m_bottomLeft->draw(canvas, returned);
				break;
			}

			if ((m_bottomRight->containsObject(m_bottomRight, returned.at(i))))
			{
				canvas.draw(shape);
				m_bottomRight->draw(canvas, returned);
				break;
			}
		}
	}
	else
	{

		canvas.draw(shape);
	}
}
