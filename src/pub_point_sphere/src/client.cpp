#include <rclcpp/rclcpp.hpp>
#include "my_interface/srv/add_three_ints.hpp"
#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

class Client:public rclcpp::Node{
    public:
        Client():Node("Client"){
            client_=this->create_client<my_interface::srv::AddThreeInts>("add_three_ints");
            RCLCPP_INFO(this->get_logger(),"Creat Client!");
        }
        void send_msg();
    private:
    rclcpp::Client<my_interface::srv::AddThreeInts>::SharedPtr client_;
    // rclcpp::WallTimer
};

void Client::send_msg(){
    auto request=std::make_shared<my_interface::srv::AddThreeInts::Request>();
    request->a=1;
    request->b=2;
    request->c=3;
    while(!client_->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
            return;
        }
        RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
    }
    auto result=client_->async_send_request(request);
    if(rclcpp::spin_until_future_complete(this->shared_from_this(),result)==rclcpp::FutureReturnCode::SUCCESS){
        RCLCPP_INFO(this->get_logger(),"Sum : %ld",result.get()->sum);
    }
    else RCLCPP_ERROR(this->get_logger(), "Failed to call service add_two_ints");
}

int main (int argc,char * argv[]){
    rclcpp::init(argc,argv);
    auto client_node = std::make_shared<Client>();
    while(1) client_node->send_msg();
    rclcpp::spin(client_node);
    rclcpp::shutdown();
}