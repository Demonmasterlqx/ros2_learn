#include <bits/stdc++.h>
#include "my_interface/srv/add_three_ints.hpp"
#include <rclcpp/rclcpp.hpp>

class Service:public rclcpp::Node{
    public:
    Service():Node("Service"){
        service_=this->create_service<my_interface::srv::AddThreeInts>("add_three_ints",std::bind(&Service::callback,this,std::placeholders::_1,std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(),"Creat a service successfully!");
    }
    private:
    rclcpp::Service<my_interface::srv::AddThreeInts>::SharedPtr service_;
    void callback(const std::shared_ptr<my_interface::srv::AddThreeInts_Request> request,
    std::shared_ptr<my_interface::srv::AddThreeInts_Response> response){
        response->sum=request->a+request->b+request->c;
        RCLCPP_INFO(this->get_logger(),"Get %ld , %ld ,%ld",request->a,request->b,request->c);
        RCLCPP_INFO(this->get_logger(),"Return %ld",response->sum);
    }
};

int main (int argc,char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<Service>());
    rclcpp::shutdown();
}