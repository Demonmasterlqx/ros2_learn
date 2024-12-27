#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <thread>
#include <rclcpp_components/register_node_macro.hpp>

namespace VideoSUBPUB{

class VideoPublisher : public rclcpp::Node
{
public:
    VideoPublisher(rclcpp::NodeOptions options)
    : Node("video_publisher",options)
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("video_frame", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(33),  // 30fps
            std::bind(&VideoPublisher::timer_callback, this));

        // 打开视频文件
        cap_.open("/home/lqx/code/ros2_learn/image/xuejieyuan.mp4");
        if (!cap_.isOpened()) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open video file");
            rclcpp::shutdown();
        }
    }

private:
    void timer_callback()
    {
        cv::Mat frame;
        cap_ >> frame;  // 读取一帧视频

        if (frame.empty()) {
            RCLCPP_INFO(this->get_logger(), "End of video reached");
            rclcpp::shutdown();
            return;
        }
        // cv::imshow("Video Frame", frame);
        // cv::waitKey(0.016);
        sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
        publisher_->publish(*msg);
    }

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
};

}

// int main(int argc, char * argv[])
// {
//     rclcpp::init(argc, argv);
//     rclcpp::spin(std::make_shared<VideoPublisher>());
//     rclcpp::shutdown();
//     return 0;
// }

RCLCPP_COMPONENTS_REGISTER_NODE(VideoSUBPUB::VideoPublisher)