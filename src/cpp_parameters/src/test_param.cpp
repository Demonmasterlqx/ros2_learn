#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

template<typename T>
void output(const std::shared_ptr<rclcpp::Node> node,const T& C,const std::string & Be="",const std::string & Af=""){
    std::stringstream out;
    out<<Be<<C<<Af;
    RCLCPP_INFO(node->get_logger(),"%s",out.str().c_str());
}



int main (int argc, char ** argv){
    rclcpp::init(argc, argv);

   auto node=std::make_shared<rclcpp::Node>("test_para");
    node->declare_parameter<int>("TEST1",21);
    //用于监控参数变化
    auto param_subscriber_=std::make_shared<rclcpp::ParameterEventHandler>(node);
    auto cb_handle_=param_subscriber_->add_parameter_callback(
        "TEST1",
        [node](const rclcpp::Parameter & p){
            output(node,p.get_type_name(),"type=");
            output(node,p.get_name(),"name=");
            output(node,p.as_int(),"TEST1=");
        }
    );
    auto cb_handle_2=param_subscriber_->add_parameter_callback("my_parameter",
            [node](const rclcpp::Parameter & p){
            output(node,p.get_type_name(),"type=");
            output(node,p.get_name(),"name=");
            output(node,p.as_string(),"TEST1=");
            },
            "minimal_param_node"
    );
    rclcpp::spin(node);
    rclcpp::shutdown();
}
