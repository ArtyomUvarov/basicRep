cmake_minimum_required(VERSION 3.5)

project(03.homework)



add_executable(
	check_value
	check_value.cpp
	random_value.cpp
    random_value.h 
	high_scores.cpp
	high_scores.h )

set_target_properties(check_value PROPERTIES
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON)
