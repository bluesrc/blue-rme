//////////////////////////////////////////////////////////////////////
// This file is part of Remere's Map Editor
//////////////////////////////////////////////////////////////////////
// Remere's Map Editor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Remere's Map Editor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#ifndef BLUERME_WAYPOINTS_H_
#define BLUERME_WAYPOINTS_H_

#include "position.h"

class Waypoint
{
public:
	std::string name;
	Position pos;
};

typedef std::map<std::string, Waypoint*> WaypointMap;

class Waypoints
{
public:
	Waypoints(Map& map) : map(map) {}
	virtual ~Waypoints();

	void addWaypoint(Waypoint* wp);
	Waypoint* getWaypoint(std::string name);
	Waypoint* getWaypoint(const Position& position);
	void removeWaypoint(std::string name);

	WaypointMap waypoints;

	WaypointMap::iterator begin() { return waypoints.begin(); }
	WaypointMap::const_iterator begin() const { return waypoints.begin(); }
	WaypointMap::iterator end() { return waypoints.end(); }
	WaypointMap::const_iterator end() const { return waypoints.end(); }

private:
	Map& map;
};

#endif
