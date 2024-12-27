cmake_minimum_required(VERSION 3.8)
project(composable_node)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(my_interface REQUIRED)

add_library(sub_call_me SHARED src/sub.cpp)
add_library(pub_call_me SHARED src/pub.cpp)

ament_target_dependencies(sub_call_me rclcpp my_interface rclcpp_components)
ament_target_dependencies(pub_call_me rclcpp my_interface rclcpp_components)

rclcpp_components_register_node(
  sub_call_me
  PLUGIN "MessageCallMe::GetMessageCallme"
  EXECUTABLE sub_call_me_exe
)

rclcpp_components_register_node(
  pub_call_me #表示库的名称
  PLUGIN "MessageCallMe::SendMessage" #表示库中注册的节点名称
  EXECUTABLE pub_call_me_exe #表示生成可执行文件来调用这个库
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_export_targets(sub_call_me_exe)
ament_export_targets(sub_call_me_exe)

#这是一个用于 ROS 2 构建系统的 CMake 宏，用于导出一个目标（比如库或可执行文件），使得该目标能够被其他依赖此目标的 ROS 2 包使用。通过这种方式，其他包可以链接到该目标，使用它提供的功能。

install(
  TARGETS sub_call_me
  TARGETS pub_call_me
  EXPORT sub_call_me_exe
  EXPORT sub_call_me_exe
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

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
