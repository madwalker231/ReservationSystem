///////////////////////////////////////////////////////////////////////////////////
// file:  Station.cpp
// Job:   holds the Station definitions 
//////////////////////////////////////////////////////////////////////////////////

#include "Station.h"
#include "Pump.h"

using namespace std;

Station::Station(void) : freeMask(0)
{
	pumps = nullptr;
	pumpsInStation = 0;
}

Station::~Station(void)
{
	delete []pumps;
}

int Station::fillUp()
{
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Station for reservation for cars to fill up.
	/////////////////////////////////////////////////////////////////////////////////////////////
	std::unique_lock<std::mutex> pumpMTX(*stationMutex);

	for (int i = 0; i <= pumpsInStation - 1; i++) {

		if ((freeMask & (1 << i)) == 0) {
			freeMask |= (1 << i);
			pumpMTX.unlock();
			pumps[i].fillTankUp();
			pumpMTX.lock();
			stationCondition->notify_all();
			freeMask &= (1 << i);
			pumpMTX.unlock();
			this_thread::sleep_for(chrono::milliseconds((carsInStation * 30)) / pumpsInStation);
			return 1;
		}
	}
	this->stationCondition->wait(pumpMTX);

	return 0;
}

int Station::getPumpFillCount(int num)
{
	if((num >= 0) && (num < pumpsInStation))
	{
		return pumps[num].getFillCount();
	}
	else 
	{
		return -1;
	}
}

void Station::createPumps(int numOfPumps)
{
	pumps = new Pump[numOfPumps];
	pumpsInStation = numOfPumps;
}

int Station::getCarsInStation(void)
{
	return this->carsInStation;
}

void Station::setCarsInStation(int num)
{
	this->carsInStation = num;
}

std::mutex* Station::getstationMutex(void)
{
	return this->stationMutex;
}

std::condition_variable* Station::getStationCondition(void)
{
	return this->stationCondition;
}

void Station::setStationMutex(std::mutex* m)
{
	this->stationMutex = m;
}

void Station::setStationCondition(std::condition_variable* cv)
{
	this->stationCondition = cv;
}
