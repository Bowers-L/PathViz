#pragma once

#include <string>

namespace graph {

	struct vec3 {
		double x, y, z;

		vec3(double x, double y, double z);

		static double calcDistance(vec3 u, vec3 v);

		std::string toString() const;

		bool operator==(const vec3& other) const;
	};

}
