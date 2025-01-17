#include <functional>
#include <memory>
#include <thread>

#include "my_interface/action/fibonacci.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace action_tutorials_cpp{

class FibonacciActionServer : public rclcpp::Node{
    public:
    using Fibonacci = my_interface::action::Fibonacci;
    using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;
    explicit FibonacciActionServer(
        const rclcpp::NodeOptions & options = rclcpp::NodeOptions()
    ):Node("fibonacci_action_server",options){
        using namespace std::placeholders;
        this->action_server_=rclcpp_action::create_server<Fibonacci>(
            this,
            "Fibonacci",
            std::bind(&FibonacciActionServer::handle_goal,this,_1,_2),
            std::bind(&FibonacciActionServer::handle_cancel,this,_1),
            std::bind(&FibonacciActionServer::handle_accepted,this,_1)
        );
    }
    private:
    rclcpp_action::Server<Fibonacci>::SharedPtr action_server_;

    /*
    const rclcpp_action::GoalUUID & uuid 是每一个action请求的唯一标识符
    */
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        std::shared_ptr<const Fibonacci::Goal> goal);
    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<GoalHandleFibonacci> goal_handle
    );
    void handle_accepted(
        const std::shared_ptr<GoalHandleFibonacci> goal_handle
    );
    void execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle);
};

rclcpp_action::GoalResponse FibonacciActionServer::handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        std::shared_ptr<const Fibonacci::Goal> goal){
        RCLCPP_INFO(this->get_logger(),"Received goal request with order %d",goal->order);
        (void)uuid;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

rclcpp_action::CancelResponse FibonacciActionServer::handle_cancel(
        const std::shared_ptr<GoalHandleFibonacci> goal_handle
    ){
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
}

void FibonacciActionServer::handle_accepted(
        const std::shared_ptr<GoalHandleFibonacci> goal_handle
    ){
    using namespace std::placeholders;
    std::thread{std::bind(&FibonacciActionServer::execute,this,goal_handle)}.detach();
} 

void FibonacciActionServer::execute(
    const std::shared_ptr<GoalHandleFibonacci> goal_handle
){
    RCLCPP_INFO(this->get_logger(),"Executing goal");
    rclcpp::Rate loop_rate(1);
    const auto goal=goal_handle->get_goal();
    auto feedback=std::make_shared<Fibonacci::Feedback>();
    auto result=std::make_shared<Fibonacci::Result>();
    auto & sequence=feedback->partial_sequence;
    sequence.push_back(0);
    sequence.push_back(1);
    for(int i=1;(i<goal->order)&&rclcpp::ok();++i){
        if(goal_handle->is_canceling()){
            result->sequence=sequence;
            goal_handle->canceled(result);
            RCLCPP_INFO(this->get_logger(),"Goal canceled");
            return;
        }
        sequence.push_back(sequence[i]+sequence[i-1]);
        goal_handle->publish_feedback(feedback);
        RCLCPP_INFO(this->get_logger(), "Publish feedback");
        loop_rate.sleep();
    }

    if(rclcpp::ok()){
        result->sequence=sequence;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(),"Goal succeeded");
    }
}

}// namespace action_tutorials_cpp

RCLCPP_COMPONENTS_REGISTER_NODE(action_tutorials_cpp::FibonacciActionServer)
//注册为组件