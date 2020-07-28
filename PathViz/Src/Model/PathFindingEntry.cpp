#include "PathFindingEntry.h"

namespace model {

	PathFindingQueueEntry::PathFindingQueueEntry(const Location *a_Loc, const Location *a_PrevLoc, double a_DistFromStart, double a_TotalWeight)
		: loc(a_Loc), prevLoc(a_PrevLoc), distFromStart(a_DistFromStart), totalWeight(a_TotalWeight)
	{

	}



	PathFindingMapEntry::PathFindingMapEntry(const Location *a_PrevLoc, double a_DistFromStart, double a_TotalWeight)
		: prevLoc(a_PrevLoc), distFromStart(a_DistFromStart), totalWeight(a_TotalWeight)
	{
	}

}


