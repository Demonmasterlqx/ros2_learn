cmake_minimum_required(VERSION 3.8)
project(pub_point_sphere)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(my_interface REQUIRED)
# find_package(rosidl_interface_packages REQUIRED)


# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(pub src/main.cpp)
add_executable(sub src/sub.cpp)
add_executable(service src/service.cpp)
add_executable(client src/client.cpp)
ament_target_dependencies(pub rclcpp my_interface)
ament_target_dependencies(sub rclcpp my_interface)
ament_target_dependencies(service rclcpp my_interface)
ament_target_dependencies(client rclcpp my_interface)
# ament_target_dependencies(sub rclcpp rosidl_interface_packages)
# ament_target_dependencies(sub rclcpp rosidl_interface_packages)

install(TARGETS
  pub
  sub
  client
  service
  DESTINATION lib/${PROJECT_NAME})

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
