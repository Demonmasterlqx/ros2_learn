#include <bits/stdc++.h>
#include "my_interface/msg/num.hpp"
#include <rclcpp/rclcpp.hpp>

class Subscribor: public rclcpp::Node{
    public:
    Subscribor():Node("Subscribor"){
        subscription_=this->create_subscription<my_interface::msg::Num>(
            "pub_point_shpere",
            10,
            [this](const my_interface::msg::Num::SharedPtr msg){
                RCLCPP_INFO(this->get_logger(),"Get num %ld",msg->num);
            }
        );
    }
    private:
    rclcpp::Subscription<my_interface::msg::Num>::SharedPtr subscription_;
};

int main (int argc,char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Subscribor>());
    rclcpp::shutdown();
}