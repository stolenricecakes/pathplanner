#pragma once

#include "pathplanner/lib/PathPlannerTrajectory.h"
#include "pathplanner/lib/PathConstraints.h"
#include <units/velocity.h>
#include <units/acceleration.h>
#include <string>
#include <vector>
#include <initializer_list>
#include <wpi/json.h>

namespace pathplanner{
    class PathPlanner {
        public:
            static double resolution;

            /**
             * @brief Load a path file from storage
             * 
             * @param name The name of the path to load
             * @param constraints The max velocity and acceleration of the path
             * @param reversed Should the robot follow the path reversed
             * @return The generated path
             */
            static PathPlannerTrajectory loadPath(std::string name, PathConstraints constraints, bool reversed = false);
            
            /**
             * @brief Load a path file from storage
             * 
             * @param name The name of the path to load
             * @param maxVel Max velocity of the path
             * @param maxAccel Max acceleration of the path
             * @param reversed Should the robot follow the path reversed
             * @return The generated path
             */
            static PathPlannerTrajectory loadPath(std::string name, units::meters_per_second_t maxVel, units::meters_per_second_squared_t maxAccel, bool reversed = false){
                return loadPath(name, PathConstraints(maxVel, maxAccel), reversed);
            }

            /**
             * @brief Load a path file from storage as a path group. This will separate the path into multiple paths based on the waypoints marked as "stop points"
             * 
             * @param name The name of the path group to load
             * @param constraints Initializer list of path constraints for each path in the group. This requires at least one path constraint. If less constraints than paths are provided, the last constraint will be used for the rest of the paths.
             * @param reversed Should the robot follow the path group reversed
             * @return Vector of all generated paths in the group
             */
            static std::vector<PathPlannerTrajectory> loadPathGroup(std::string name, std::initializer_list<PathConstraints> constraints, bool reversed = false);

            /**
             * @brief Load a path file from storage as a path group. This will separate the path into multiple paths based on the waypoints marked as "stop points"
             * 
             * @param name The name of the path group to load
             * @param maxVel Max velocity of every path in the group
             * @param maxAccel Max acceleration of every path in the group
             * @param reversed Should the robot follow the path group reversed
             * @return Vector of all generated paths in the group
             */
            static std::vector<PathPlannerTrajectory> loadPathGroup(std::string name, units::meters_per_second_t maxVel, units::meters_per_second_squared_t maxAccel, bool reversed = false){
                return loadPathGroup(name, {PathConstraints(maxVel, maxAccel)}, reversed);
            }

            /**
             * Load path constraints from a path file in storage. This can be used to change path max vel/accel in the
             * GUI instead of updating and rebuilding code. This requires that max velocity and max acceleration have been
             * explicitly set in the GUI.
             * 
             * Throws a runtime error if constraints are not present in the file
             * @param name The name of the path to load constraints from
             * @return The constraints from the path file
             */
            static PathConstraints getConstraintsFromPath(std::string name);

        private:
            static std::vector<PathPlannerTrajectory::Waypoint> getWaypointsFromJson(wpi::json json);
            static std::vector<PathPlannerTrajectory::EventMarker> getMarkersFromJson(wpi::json json);
            static int indexOfWaypoint(std::vector<PathPlannerTrajectory::Waypoint> waypoints, PathPlannerTrajectory::Waypoint waypoint);
    };
}