#pragma once


class ShotTrajectory
{
public:
	ShotTrajectory();
	~ShotTrajectory();

	// Setters
	void setAngleOfShot(float t_angle);
	void setMaxDistanceOfShot(float t_maxDistance);
	void setDamageOutput(int t_damageOutput);

	// Getters
	float getAngleOfShot();
	float getMaxDistanceOfShot();
	int getDamageOutput();

private:
	float angleOfShot;
	float maxDistance;
	int damageOutput;

};