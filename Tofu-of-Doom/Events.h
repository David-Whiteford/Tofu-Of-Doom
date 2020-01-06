#ifndef AIMOVEEVENTS_H
#define AIMOVEEVENTS_H

namespace en
{
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
			PATROL
		};

		void currentEvent(AIEVENT);
		AIEVENT getCurrentEvent();

	private:
		AIEVENT m_currentAiEvent;
	};
}



#endif
