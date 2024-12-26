#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

class VideoSubscriber : public rclcpp::Node
{
public:
    VideoSubscriber()
    : Node("video_subscriber")
    {
        cv::namedWindow("Video Frame");
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "video_frame",
            10,
            std::bind(&VideoSubscriber::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const sensor_msgs::msg::Image::SharedPtr msg) const
    {
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        } catch (cv_bridge::Exception& e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        // 在这里处理图像数据
        cv::Mat frame = cv_ptr->image;
        // 例如，显示图像
        cv::imshow("Video Frame", frame);
        cv::waitKey(16);
    }
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VideoSubscriber>());
    rclcpp::shutdown();
    return 0;
}
