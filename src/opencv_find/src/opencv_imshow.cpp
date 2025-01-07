#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
#include<rclcpp/rclcpp.hpp>
#include <chrono>
#include <functional>
#include <string>

using namespace std::chrono;

class IMshow : public rclcpp::Node{
    public:
        IMshow():Node("Imshow"){
            if(rclcpp::ok()){
                RCLCPP_INFO(this->get_logger(),"IMshow is running");
                this->set_parameter(rclcpp::Parameter("my_parameter","Hello World"));
                // cv::Mat image=cv::imread("/home/lqx/code/ros2_learn/image/yinglang.jpg");
                // cv::imshow("image",image);
                auto callback=[this](){
                    std::string param=this->get_parameter("my_parameter").as_string();
                    RCLCPP_INFO(this->get_logger(),"Param is '%s'",param.c_str());
                };
                timer_=this->create_wall_timer(1000ms, callback);
                // cv::waitKey(0);
            }
            return;
        }
    rclcpp::TimerBase::SharedPtr timer_;
    
};

int main (int argc,char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<IMshow>());
    rclcpp::shutdown();
}