cmake_minimum_required(VERSION 3.8)
project(sub_pub_video)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rclcpp_components REQUIRED)


# 添加可执行文件
add_library(video_publisher SHARED src/publisher.cpp)
add_library(video_subscriber SHARED src/subscriber.cpp)

# 链接库
ament_target_dependencies(video_publisher rclcpp rclcpp_components sensor_msgs cv_bridge OpenCV)
ament_target_dependencies(video_subscriber rclcpp rclcpp_components sensor_msgs cv_bridge OpenCV)

# 注册组件
rclcpp_components_register_node(video_publisher 
  PLUGIN "VideoSUBPUB::VideoPublisher" 
  EXECUTABLE video_publisher_exe)
rclcpp_components_register_node(video_subscriber 
  PLUGIN "VideoSUBPUB::VideoSubscriber" 
  EXECUTABLE video_subscriber_exe)

# 导出目标
# ament_export_targets(video_subscriber_exe)
# ament_export_targets(video_publisher_exe)

install(
  TARGETS video_publisher
  TARGETS video_subscriber
  # EXPORT video_subscriber_exe
  # EXPORT video_publisher_exe
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()