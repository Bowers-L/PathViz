#pragma once

#include "Location.h"

namespace model {

	class Path
	{
	private:
		Location m_U, m_V;
		double m_Distance;

	public:

		Path(Location u, Location v);

		const Location& getU() const;
		const Location& getV() const;
		double getDistance() const;

		std::string toString() const;

		bool operator==(const Path& other) const;
	};

	//priority_queue by default is a max heap that uses a less than comparator
	//So I am implementing a greater than comparator to make it a min heap
	struct minHeapPathComp : std::binary_function <Path, Path, bool> {

		bool operator() (const Path& x, const Path& y) const {
			return (x.getDistance() > y.getDistance());
		}
	};
}


namespace std
{
	using namespace model;

	//Implementation of hash function (needed to use set and map structures)
	template<>
	struct hash<model::Path>
	{
		size_t
			operator()(const model::Path& obj) const
		{
			return hash<string>()(obj.getU().getLabel()) * 11 + hash<string>()(obj.getV().getLabel());
		}
	};
}


