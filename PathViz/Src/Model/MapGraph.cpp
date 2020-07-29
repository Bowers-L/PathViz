#include "MapGraph.h"
#include "PathFindingEntry.h"
#include "../Utility/Util.h"

#include <sstream>
#include <limits>


namespace model {

	
	MapGraph::MapGraph() 
		: m_Locations(Set<Location>()), m_Paths(Set<Path>()), m_AdjList(Map<Location, Vector<LocDistPair>>())
	{

	}

	MapGraph::MapGraph(Set<Location> locations, Set<Path> paths)
 		: m_Locations(locations), m_Paths(paths), m_AdjList(Map<Location, Vector<LocDistPair>>())
	{
		constructAdjList();
	}

	MapGraph::~MapGraph()
	{
	}

	
	void MapGraph::addLocation(Location v, Vector<Location> neighbors)
	{
		//Add v to the Location set
		if (m_Locations.find(v) == m_Locations.end()) {
			m_Locations.insert(v);
			m_AdjList[v] = Vector<LocDistPair>();
		}

		//Construct new Paths based on the neighbors
		for (Location neighbor : neighbors) {
			m_Locations.insert(neighbor);
			m_AdjList[neighbor] = Vector<LocDistPair>();

			Path e = Path(v, neighbor);

			m_Paths.insert(e);

			addPathToAdjList(e);
		}
	}

	void MapGraph::addPath(Location u, Location v)
	{
		Path p = { u, v };
		m_Paths.insert(p);

		addPathToAdjList(p);
	}

	void MapGraph::addPath(std::string labelU, std::string labelV)
	{
		const Location* u;
		const Location* v;

		if ((u = findLocation(labelU)) && (v = findLocation(labelV))) {
			addPath(*u, *v);
		}
	}

	void MapGraph::removeLocation(Location v)
	{
		//Erase the Location
		m_Locations.erase(v);

		//Erase all Paths associated with the Location
		for (Path p : m_Paths) {
			if (p.getU() == v || p.getV() == v) {
				m_Paths.erase(p);
			}
		}

		//Erase all map entries that contain the Location
		/*
		For example, deleting D from the following map
		would require removing the key D from the map
		and removing all LocDist pairs with D

		A -> (B, 5), (C, 6), (D, 4)
		B -> (A, 5), (C, 2), (D, 1)
		C -> (A, 6), (B, 2), (D, 3)
		D -> (A, 4), (B, 1), (C, 3)

		A -> (B, 5), (C, 6)
		B -> (A, 5), (C, 2)
		C -> (A, 6), (B, 2)
		*/


		for (LocDistPair ld : m_AdjList[v]) {
			Vector<LocDistPair>& neighborList = m_AdjList[ld.loc];
			for (Vector<LocDistPair>::iterator it = neighborList.begin(); it != neighborList.end(); it++) {
				if (it->loc == v) {
					neighborList.erase(it);
				}
			}
		}

		m_AdjList.erase(v);
	}

	Route MapGraph::findShortestPathFromTo(const Location& start, const Location& dest)
	{
		Set<Location> visited = Set<Location>();

		//Each map key points to a pair containing the distance from the start to that location 
		//and the location that was visited directly before the key location
		//The extra location is used for backtracking once the correct path is found
		auto currShortestPaths = Map<Location, PathFindingMapEntry>();

		auto queue = PQ<PathFindingQueueEntry, Vector<PathFindingQueueEntry>, minHeapPathFindingComp>();

		typedef Map<Location, PathFindingMapEntry>::value_type MapInsert;

		for (Location loc : m_Locations) {
			currShortestPaths.emplace(loc, PathFindingMapEntry(nullptr, std::numeric_limits<double>::max(), std::numeric_limits<double>::max()));
		}
		put(currShortestPaths, start, PathFindingMapEntry(nullptr, 0, vec3::calcDistance(start.getPos(), dest.getPos())));

		queue.push(PathFindingQueueEntry(&start, nullptr, 0, vec3::calcDistance(start.getPos(), dest.getPos())));
	
		while (!queue.empty() && (visited.find(dest) == visited.end())) {
			//queue is not empty & haven't processed the dest location yet

			PathFindingQueueEntry curr = queue.top();
			queue.pop();

			if (visited.find(*curr.loc) == visited.end()) {	//Haven't gotten to curr yet
				visited.insert(*curr.loc);

				for (LocDistPair& neighbor : m_AdjList[*curr.loc]) {
					//calculate total cost
					double distToStartCost = curr.distFromStart + neighbor.dist;
					double totalCost = distToStartCost + vec3::calcDistance(neighbor.loc.getPos(), dest.getPos());

					if (distToStartCost < currShortestPaths.find(neighbor.loc)->second.distFromStart) {

						put(currShortestPaths, neighbor.loc, PathFindingMapEntry(curr.loc, distToStartCost, totalCost));
						queue.push(PathFindingQueueEntry(&neighbor.loc, curr.loc, distToStartCost, totalCost));
					}
				}

			}
		}

		//Using a stack so that backtracking results in the top of the stack being the first path
		SLL<Path> *shortestPath = new SLL<Path>();
		const Location *curr = &dest;
		while (currShortestPaths.find(*curr)->second.prevLoc != nullptr) {

			shortestPath->push_front(Path(*currShortestPaths.find(*curr)->second.prevLoc, *curr));
			curr = currShortestPaths.find(*curr)->second.prevLoc;
		}

		if (shortestPath->empty() || shortestPath->front().getU().getLabel().compare(start.getLabel()) != 0) {
			//The path doesn't start at the start, so it is an illegal path.
			return Route(start, dest, nullptr);
		}

		return Route(start, dest, shortestPath);
	}

	Route MapGraph::findShortestPathFromTo(const std::string& start, const std::string& dest)
	{
		const Location* startLoc;
		const Location* endLoc;
		if ((startLoc = findLocation(start)) && (endLoc = findLocation(dest))) {
			return findShortestPathFromTo(*startLoc, *endLoc);
		}

	}

	const Set<Location>& MapGraph::getLocations() const
	{
		return m_Locations;
	}

	const Set<Path>& MapGraph::getPaths() const
	{
		return m_Paths;
	}

	Set<Path> MapGraph::getMST(Location start) const
	{
		//Returns a minimum spanning tree of this MapGraph
		//using Prim's algorithm (requires a starting Location)

		//Keep track of Locices that have been visited 
		Set<Location> visited = Set<Location>();

		//Output set
		Set<Path> mst = Set<Path>();

		//Min. priority queue of all the considered Paths
		auto queue = PQ<Path, Vector<Path>, minHeapPathComp>();

		//Add all Paths from the start to the queue
		//Need this messy const_cast syntax because the [] operator isn't allowed on const maps
		//even though the map is not being modified
		for (LocDistPair ld : (*const_cast<Map<Location, Vector<LocDistPair>>*>(&m_AdjList))[start]) {
			queue.push(Path(start, ld.loc));
		}
		visited.insert(start);

		//Still items in the queue and have not visited all of the Locations yet
		while (queue.size() > 0 && visited.size() != m_Locations.size()) {

			Path currPath = queue.top();	//Get reference to the Path
			queue.pop();	//Remove the Path from the queue
			Location currLoc = currPath.getV();


			if (visited.find(currLoc) == visited.end()) {

				//Add the Path to the mst if the destination Location hasn't been visited yet
				visited.insert(currLoc);
				mst.insert(Path(currPath));

				//Push all Paths from currLoc to Locices that haven't been visited yet
				for (LocDistPair ld : (*const_cast<Map<Location, Vector<LocDistPair>>*>(&m_AdjList))[currLoc]) {
					if (visited.find(ld.loc) == visited.end()) {
						queue.push(Path(currLoc, ld.loc));
					}

				}
			}
		}

		return mst;
	}

	std::string MapGraph::getMSTDesc(const Set<Path>& mst) const
	{
		std::string retVal = "";

		for (Path e : mst) {
			retVal += e.toString() + "\n";
		}

		return retVal;
	}

	std::string MapGraph::toString() const
	{
		std::string retVal = "";

		retVal += "Locations: \n";
		for (Location v : m_Locations) {
			retVal += v.toString();
			retVal += "\n";
		}

		retVal += "\nPaths: \n";
		for (Path e : m_Paths) {
			retVal += e.toString();
			retVal += "\n";
		}

		retVal += "\nAdjacency List: \n";
		for (auto pair : m_AdjList) {
			retVal += pair.first.toString();
			retVal += "\n";

			for (LocDistPair ld : pair.second) {
				retVal += "\t" + ld.toString() + "\n";
			}
			retVal += "\n";
		}

		return retVal;
	}
	
	double MapGraph::totalDistance(const Set<Path>& paths)
	{
		double total = 0;
		for (Path p : paths) {
			total += p.getDistance();
		}

		return total;
	}

	const Location* MapGraph::findLocation(const std::string& label)
	{
		for (const Location& l : m_Locations) {
			if (l.getLabel().compare(label) == 0) {
				return &l;
			}
		}

		return nullptr;
	}

	void MapGraph::constructAdjList()
	{
		for (Location v : m_Locations)
		{
			//Add Locices to the map with empty lists
			m_AdjList[v] = Vector<LocDistPair>();
		}

		for (Path p : m_Paths) {	
			//Populate the adj list based on the MapGraph's Paths.
			if (m_AdjList.find(p.getU()) != m_AdjList.end()) {
				m_AdjList[p.getU()].push_back(LocDistPair(p.getV(), p.getDistance()));
			}
		}
	}

	//Need to call this every time a Path is added to the MapGraph
	void MapGraph::addPathToAdjList(Path p)
	{
		//Adds an entry into the adj list for both Locices in the Path
		m_AdjList[p.getU()].push_back(LocDistPair(p.getV(), p.getDistance()));
		m_AdjList[p.getV()].push_back(LocDistPair(p.getU(), p.getDistance()));
	}
	
}