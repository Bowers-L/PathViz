#include "Vec3.h"

#include <cmath>

namespace graph {

	vec3::vec3(double x, double y, double z)
		: x(x), y(y), z(z)
	{

	}

	double vec3::calcDistance(vec3 u, vec3 v)
	{
		return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2) + pow(u.z - v.z, 2));
	}

	bool vec3::operator==(const vec3& other)
	{
		return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z));
	}

}