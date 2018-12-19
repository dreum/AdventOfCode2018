#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <set>
#include <utility>
using namespace std;

// puzzle input https://adventofcode.com/2018/day/1/input
int main() 
{
	std::vector<int> frequencyChanges;
	auto freq{0};
	while(cin >> freq)
		frequencyChanges.push_back(freq);
		
	cout << accumulate(
		begin(frequencyChanges),
		end(frequencyChanges),
		0) << '\n';
	
	set<int> foundFrequencies { 0 };
	pair<set<int>::iterator, bool> returnPair{ foundFrequencies.begin(), false };
	do
	{
		size_t index = (foundFrequencies.size()-1) % frequencyChanges.size();
		auto newFrequency = 
			*returnPair.first + frequencies[index];
		returnPair = foundFrequencies.emplace(std::move(newFrequency));
	} while (returnPair.second);
	
	cout << *returnPair.first << '\n';
	return 0;
}
