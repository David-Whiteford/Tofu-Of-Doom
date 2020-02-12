#ifndef MY_ENUMS
#define MY_ENUMS

// author Kevin Andersen
// and David Whiteford

/// <summary>
/// our animatiuons will go from appear to none to disappear
/// </summary>
enum class AnimationState
{
	None,
	Appear,
	Disappear
};


/// <summary>
/// different mode game can be 
/// starting with splash
/// </summary>
enum class GameState
{
	//different game states
	None,
	Options,
	Exit,
	Licence,
	HighScore,
	Splash,
	Main,
	Credits,
	Level1,
	GameOver
};

#endif // !MY_ENUMS

