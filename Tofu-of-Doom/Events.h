#ifndef AIMOVEEVENTS_H
#define AIMOVEEVENTS_H


class Events
{

public:
	Events();
	~Events();

	enum class AIEVENT
	{
		NONE,
		LEFT,
		RIGHT,
		UP,
		ATTACK,
		FOLLOW,
	};

	void currentEvent(AIEVENT);
	AIEVENT getCurrentEvent();

private:
	AIEVENT m_currentAiEvent;
};



#endif
