#pragma once

#include "Location.h"

namespace model {
	/*
	Data to store in a priority queue for the path finding algorithm in MapGraph
	*/
	struct PathFindingQueueEntry {
		const Location *loc;
		const Location *prevLoc;	//The location that resulted in the creation of this entry

		double distFromStart;
		double totalWeight;	//distance from start + the distance from loc to the destination in the algorithm

		PathFindingQueueEntry(const Location *a_Loc, const Location *a_PrevLoc, double a_DistFromStart, double a_TotalWeight);

	};

	/*
	The map entry is basically the exact same as the queue entry, except the loc is used as the key in the hash table, 
	so it is not a part of the entry itself.
	*/
	struct PathFindingMapEntry {
		const Location *prevLoc;

		double distFromStart;
		double totalWeight;

		PathFindingMapEntry(const Location *a_PrevLoc, double a_DistFromStart, double a_TotalWeight);
	};

	//priority_queue by default is a max heap that uses a less than comparator
	//So I am implementing a greater than comparator to make it a min heap
	struct minHeapPathFindingComp : std::binary_function <PathFindingQueueEntry, PathFindingQueueEntry, bool> {

		bool operator() (const PathFindingQueueEntry& x, const PathFindingQueueEntry& y) const {
			//Order the entrys in the priority queue by total weight
			return (x.totalWeight > y.totalWeight);
		}
	};
}
