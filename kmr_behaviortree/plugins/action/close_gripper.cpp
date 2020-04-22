#include "kmr_behaviortree/bt_action_node.hpp"
#include "kmr_msgs/action/close_gripper.hpp"


namespace kmr_behavior_tree
{
class CloseGripperAction : public BtActionNode<kmr_msgs::action::CloseGripper>
{
public:
  CloseGripperAction(
    const std::string & xml_tag_name,
    const std::string & action_name,
    const BT::NodeConfiguration & conf)
  : BtActionNode<kmr_msgs::action::CloseGripper>(xml_tag_name, action_name, conf)
  {
  }

  void on_tick() override
  {
  }
};

}  // namespace kmr_behavior_tree

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  BT::NodeBuilder builder =
    [](const std::string & name, const BT::NodeConfiguration & config)
    {
      return std::make_unique<kmr_behavior_tree::CloseGripperAction>(
        name, "close_gripper", config);
    };

  factory.registerBuilder<kmr_behavior_tree::CloseGripperAction>(
    "CloseGripper", builder);
}