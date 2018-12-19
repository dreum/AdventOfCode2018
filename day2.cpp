#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct OffByOneComparison
{
	bool operator()(string const& first, string const& second)
	{
		vector<int> diffCharIndices;
		for(auto i{0u}; i < first.size(); ++i)
		{
			if(first[i] != second[i])
				diffCharIndices.push_back(i);
		}
		
		if(diffCharIndices.size() < 2)
		{
			diffIndex = diffCharIndices.front();
			return false;
		}
		
		return true;
	}
	
	size_t diffIndex{0};
};

bool checkForMultiples(string const& input, unsigned int const numberOf)
{
	for(auto const& c : input)
	{
		auto number = count(
			begin(input),
			end(input),
			c);
		if(numberOf == number)
			return true;
	}
	return false;
}
bool hasDuplicate(string const& input)
{
	return checkForMultiples(input, 2);
}

bool hasTriplicate(string const& input)
{
	return checkForMultiples(input, 3);
}

// puzzle input https://adventofcode.com/2018/day/2/input
int main() 
{
	vector<string> boxIDs;
	string ID;
	while(cin >> ID)
		boxIDs.push_back(ID);
		
	auto countOfStringsWithDuplicates{0u};
	auto countOfStringsWithTriplicates{0u};
	for(auto const& id : boxIDs)
	{
		if(hasDuplicate(id))
			++countOfStringsWithDuplicates;
		
		if(hasTriplicate(id))
			++countOfStringsWithTriplicates;
	}
	
	cout << countOfStringsWithDuplicates * countOfStringsWithTriplicates << '\n';
	
	OffByOneComparison comp;
	string id1,id2;
	for(auto first = boxIDs.cbegin(); first != boxIDs.cend(); ++first)
	{
		for(auto second = first + 1; second != boxIDs.cend(); ++second)
		{
			if(!comp(*first, *second))
			{
				id1 = *first;
				id2 = *second;
				break;
			}
		}
	}
	
	cout 
		<< id1 << '\n'
		<< id2 << '\n'
		<< id1.substr(0, comp.diffIndex) 
		<< id1.substr(comp.diffIndex + 1, id1.size() - comp.diffIndex) << '\n';
	return 0;
}
