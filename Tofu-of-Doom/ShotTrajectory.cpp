#include "ShotTrajectory.h"

ShotTrajectory::ShotTrajectory()
{
}

ShotTrajectory::~ShotTrajectory()
{
}

void ShotTrajectory::setAngleOfShot(float t_angle)
{
	angleOfShot = t_angle;
}

void ShotTrajectory::setMaxDistanceOfShot(float t_maxDistance)
{
	maxDistance = t_maxDistance;
}

void ShotTrajectory::setDamageOutput(int t_damageOutput)
{
	damageOutput = t_damageOutput;
}

float ShotTrajectory::getAngleOfShot()
{
	return angleOfShot;
}

float ShotTrajectory::getMaxDistanceOfShot()
{
	return maxDistance;
}

int ShotTrajectory::getDamageOutput()
{
	return damageOutput;
}
