#pragma once

#include "Vertex.h"

namespace graph {
	struct VertDistPair {
		//Basically an edge without the starting vertex
		//Useful for optimization algorithms

		Vertex vertex;
		double distance;

		VertDistPair(Vertex vertex, double distance);

		std::string toString() const;
	};
}