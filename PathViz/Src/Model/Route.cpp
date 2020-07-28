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

	const std::string& Route::routeDesc() const
	{
		std::string retVal;
		if (m_Paths == nullptr) {
			retVal += "A route could not be found from " + m_Start.getLabel() + " to " + m_Dest.getLabel() + "\n";
		} else {
			retVal += "Path from " + m_Start.getLabel() + " to " + m_Dest.getLabel() + "\n";

			for (Path p : *m_Paths) {	//This is why m_Paths is a forward list and not a straight up stack
				retVal += "Go from " + p.getU().getLabel() + " to " + p.getV().getLabel() + "\n";
			}

			retVal += "Arrive at " + m_Dest.getLabel() + "\n";
		}

		return retVal;
	}
}

