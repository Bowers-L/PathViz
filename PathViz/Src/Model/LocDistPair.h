#pragma once

#include "Location.h"
#include <string>

namespace model {
	struct LocDistPair {
		//Basically an edge without the starting vertex
		//Useful for optimization algorithms

		Location loc;
		double dist;

		LocDistPair(Location location, double distance);

		std::string toString() const;
	};
}