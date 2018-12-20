#include <iostream>
#include <array>
#include <set>
#include <numeric>
#include <algorithm>
#include <iterator>
using namespace std;

struct SqInchStats
{
	unsigned int CurrentOwner = 0;
	unsigned int Overlap = 0;
};

constexpr size_t fabricSize = 1000;
int main() {
	
	array<array<SqInchStats, fabricSize>, fabricSize> sheet;
	set<unsigned int> overlappedIds;
	set<unsigned int> allIds;
	char hash,at,comma,colon,by;
	unsigned int id;
	size_t x,y,width,height;
	while(cin >> hash >> id >> at >> x >> at >> y >> colon >> width >> by >> height)
	{
		allIds.insert(id);
		for(auto column = x; column < x+width; ++column)
			for(auto row = y; row < y+height; ++row)
			{
				auto& sheetPos = sheet.at(column).at(row);
				if(0 != sheetPos.CurrentOwner)
				{
					overlappedIds.insert(sheetPos.CurrentOwner);
					overlappedIds.insert(id);
				}
				sheetPos.CurrentOwner = id;
				++sheetPos.Overlap;
			}
	}
	
	cout << accumulate(
		cbegin(sheet),
		cend(sheet),
		0,
		[](auto const& sum, auto const& row)
		{
			return sum + accumulate(
				cbegin(row),
				cend(row),
				0,
				[](auto const& sum, auto const& sheetPos)
				{
					return (sheetPos.Overlap > 1) ? sum + 1 : sum;
				});
		}) << '\n';
		
	set<unsigned int> nonOverlappingIds;
	set_difference(
		cbegin(allIds),
		cend(allIds),
		cbegin(overlappedIds),
		cend(overlappedIds),
		inserter(
			nonOverlappingIds, 
			nonOverlappingIds.end()));
		
	for(auto const id : nonOverlappingIds)
	{
		cout << id << ' ';
	}
	
	return 0;
}
