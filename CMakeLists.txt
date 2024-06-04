cmake_minimum_required(VERSION 3.5)

project(container_templates)
add_executable(container_templates   "main.cpp" "serial_container.h" "list_container.h")
set_target_properties(
        container_templates
    PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)
