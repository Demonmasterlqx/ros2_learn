#include <bits/stdc++.h>
#include "my_interface/msg/num.hpp"
#include <rclcpp/rclcpp.hpp>

class Publisher:public rclcpp::Node{
    public:
        Publisher():Node("Publisher"){
            cnt=0;
            publisher_=this->create_publisher<my_interface::msg::Num>("pub_point_shpere",10);
            timer_=this->create_wall_timer(std::chrono::milliseconds(500),std::bind(&Publisher::timer_callback,this));
        }
    private:
    int cnt;
    void timer_callback(){
        auto msg=my_interface::msg::Num();
        msg.num=++cnt;
        RCLCPP_INFO(this->get_logger(),"msg '%ld' is published.",msg.num);
        publisher_->publish(msg);
    }
    rclcpp::Publisher<my_interface::msg::Num>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main (int argc,char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
}