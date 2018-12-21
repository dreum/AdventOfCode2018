#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct SleepDetails
{
	int minute;
	string note;
};

struct GuardDetails
{
	unsigned int totalSleep;
	unsigned int maxMinute;
};

// puzzle input: https://adventofcode.com/2018/day/4/input
int main() {
	tm inputTime;
	string note;
	map<time_t, SleepDetails> timeNotes;
	
	while(cin >> get_time(&inputTime, "[%Y-%m-%d %R]") && getline(cin, note))
	{
		auto timeSinceEpoch = mktime(&inputTime);
		timeNotes.insert({timeSinceEpoch, {inputTime.tm_min, note}});
	}
	
	cout << timeNotes.size() << '\n';
	
	map<unsigned int, vector<unsigned int>> timePlots;
	
	unsigned int guardId;
	int timeStart, timeEnd;
	
	for(auto const& timeNotePair : timeNotes)
	{
		if(timeNotePair.second.note.find("Guard") != string::npos)
		{
			istringstream s(timeNotePair.second.note);
			string guard;
			char hash;
			s >> guard >> hash >> guardId;
			
			timePlots.insert({guardId, vector<unsigned int>(60u)});
		}
		else if(timeNotePair.second.note.find("wakes") != string::npos)
		{
			timeEnd = timeNotePair.second.minute;
			
			for(; timeStart < timeEnd; ++timeStart)
				++timePlots[guardId][timeStart];
		}
		else if(timeNotePair.second.note.find("falls") != string::npos)
		{
			timeStart = timeNotePair.second.minute;
		}
	}
	
	map<unsigned int, GuardDetails> allDetails;
	for(auto const& timePlot : timePlots)
	{
		auto totalSleep = accumulate(
			cbegin(timePlot.second),
			cend(timePlot.second),
			0u);
		auto maxMinute = max_element(
			cbegin(timePlot.second),
			cend(timePlot.second));
			
		allDetails.insert({
			timePlot.first, 
			GuardDetails{
				totalSleep, 
				distance(timePlot.second.begin(), maxMinute)}});
	}
	
	auto chosenGuard = max_element(
		cbegin(allDetails),
		cend(allDetails),
		[](auto const& first, auto const& second)
		{
			return first.second.totalSleep < second.second.totalSleep;
		});
		
	cout 
		<< chosenGuard->first << ' '
		<< chosenGuard->second.maxMinute << ' '
		<< chosenGuard->first * chosenGuard->second.maxMinute << '\n';
	return 0;
}
