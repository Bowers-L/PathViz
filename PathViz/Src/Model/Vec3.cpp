#include "Vec3.h"

#include <cmath>

namespace model {

	vec3::vec3(double x, double y, double z)
		: x(x), y(y), z(z)
	{

	}

	double vec3::calcDistance(const vec3& u, const vec3& v)
	{
		return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2) + pow(u.z - v.z, 2));
	}

	std::string vec3::toString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

	bool vec3::operator==(const vec3& other) const
	{
		return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z));
	}

	bool vec3::operator!=(const vec3& other) const
	{
		return !(*this == other);
	}

}