cmake_minimum_required (VERSION 2.8)

project (tinyraytracer)

file(GLOB SOURCES *.h *.cpp)

ADD_EXECUTABLE (tinyraytracer tinyraytracer.cpp)

