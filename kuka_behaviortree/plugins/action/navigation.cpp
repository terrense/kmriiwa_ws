// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <memory>
#include <string>

#include "geometry_msgs/msg/pose.hpp"
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include "kuka_behaviortree/bt_action_node.hpp"

namespace kmr_behavior_tree
{

class NavigationAction : public BtActionNode<nav2_msgs::action::NavigateToPose>
{
public:
  NavigationAction(
    const std::string & xml_tag_name,
    const std::string & action_name,
    const BT::NodeConfiguration & conf)
  : BtActionNode<nav2_msgs::action::NavigateToPose>(xml_tag_name, action_name, conf)
  {
  }

  void on_tick() override
  {
    // Use the position and orientation fields from the XML attributes to initialize the goal
    geometry_msgs::msg::PoseStamped current_goalpose;

    config().blackboard->get("current_goalpose", current_goalpose);

    goal_.pose.pose.position = current_goalpose.pose.position;
    goal_.pose.pose.orientation = current_goalpose.pose.orientation;
  }

};

}  // namespace kmr_behavior_tree

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  BT::NodeBuilder builder =
    [](const std::string & name, const BT::NodeConfiguration & config)
    {
      return std::make_unique<kmr_behavior_tree::NavigationAction>(
        name, "navigate_to_pose", config);
    };

  factory.registerBuilder<kmr_behavior_tree::NavigationAction>(
    "Navigation", builder);
}
