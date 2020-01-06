#include "Events.h"

en::Events::Events()
{
	m_currentAiEvent = AIEVENT::PATROL;

}

en::Events::~Events()
{
}

void en::Events::currentEvent(en::Events::AIEVENT event)
{
}

en::Events::AIEVENT en::Events::getCurrentEvent()
{
	return AIEVENT();
}
