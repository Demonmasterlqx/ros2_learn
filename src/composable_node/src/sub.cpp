#include <bits/stdc++.h>
#include "my_interface/msg/call_me.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include <functional>
#include <memory>
#include <thread>

namespace MessageCallMe{

class GetMessageCallme:public rclcpp::Node{

    public:
    using callme=my_interface::msg::CallMe;
    // using std::placeholders::_1;
    // using namespace std::placeholders;
    GetMessageCallme(const rclcpp::NodeOptions&options):Node("SubCallMe",options){
        subscription_=this->create_subscription<callme>("CallMe",10,std::bind(&GetMessageCallme::callback,this,std::placeholders::_1));
    }

    private:
    rclcpp::Subscription<callme>::SharedPtr subscription_;
    void callback(const callme::SharedPtr msg){
        RCLCPP_INFO(this->get_logger(),"Sub msg %s %s %s",msg->id.c_str(),msg->phone.c_str(),msg->name.c_str());
    }

};//class GetMessageCallme

}//MessageCallMe

RCLCPP_COMPONENTS_REGISTER_NODE(MessageCallMe::GetMessageCallme)