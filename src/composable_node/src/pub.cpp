#include <bits/stdc++.h>
#include "my_interface/msg/call_me.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace MessageCallMe{
    class SendMessage:public rclcpp::Node{
        using callme=my_interface::msg::CallMe;
        public:
        SendMessage(const rclcpp::NodeOptions& options):Node("PubCallMe",options){
            publisher_=this->create_publisher<callme>("CallMe",10);
            timer_=this->create_wall_timer(std::chrono::milliseconds(33),std::bind(&SendMessage::callback,this));
        }
        private:
        rclcpp::Publisher<callme>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        void callback(){
            callme msg;
            msg.id="1001";
            msg.phone="110";
            msg.name="LQX";
            RCLCPP_INFO(this->get_logger(),"Pub msg");
            publisher_->publish(msg);
        }
    };
}

RCLCPP_COMPONENTS_REGISTER_NODE(MessageCallMe::SendMessage)