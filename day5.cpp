#include <iostream>
#include <list>
#include <climits>
#include <algorithm>
using namespace std;

size_t FindReactedSize(list<char>& polymer)
{
	size_t oldsize{0};
	while(oldsize != polymer.size())
	{
		oldsize = polymer.size();
		for(auto iter = polymer.begin(); iter != (--polymer.end());)
		{
			if((*iter + 32) == *(next(iter)) ||
			   (*iter - 32) == *(next(iter)))
			{
			   	polymer.erase(iter++);
			   	polymer.erase(iter++);
			}
			else
			{
				++iter;
			}
		}
	}
	return oldsize;
}

// puzzle input: https://adventofcode.com/2018/day/5/input
int main() {
	list<char> polymer;
	char c;
	while(cin >> c)
		polymer.push_back(c);
	
	size_t minSize{UINT_MAX};
	for(auto c = 'A'; c <= 'Z'; ++c)
	{
		auto tmpPolymer = polymer;
		tmpPolymer.remove_if(
			[c](auto const& elem)
			{
				return (c == elem) || ((c+32) == elem);
			});
			
		auto reducedSize = FindReactedSize(tmpPolymer);
		if(reducedSize < minSize)
			minSize = reducedSize;
			
	}
	cout << FindReactedSize(polymer) << '\n';
	cout << minSize << '\n';
	return 0;
}
