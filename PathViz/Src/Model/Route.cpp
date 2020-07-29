#include "Route.h"

namespace model {
	Route::Route(const Location& start, const Location& dest, SLL<Path> *paths)
		: m_Start(start), m_Dest(dest), m_Paths(paths)
	{
	}

	const SLL<Path> *Route::getPaths() const
	{
		return m_Paths;
	}

	std::string Route::routeDesc() const
	{
		std::string retVal;
		int count = 0;
		if (m_Paths == nullptr) {
			retVal += "A route could not be found from " + m_Start.getLabel() + " to " + m_Dest.getLabel() + "\n";
		} else {
			retVal += "Path from " + m_Start.getLabel() + " to " + m_Dest.getLabel() + ":\n";

			for (Path p : *m_Paths) {	//This is why m_Paths is a forward list and not a straight up stack
				retVal += "\t" + std::to_string(count) + ": Go from " + p.getU().getLabel() + " to " + p.getV().getLabel()
					+ " (distance: " + std::to_string(p.getDistance()) + ")" + "\n";
				count++;
			}

			retVal += "\t" + std::to_string(count) + ": Arrive at " + m_Dest.getLabel() + "\n";
		}

		return retVal;
	}
}

