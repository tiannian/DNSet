
cmake_minimum_required (VERSION 2.6.4)

project (DNSet)

set(CMAKE_CXX_FLAGS "-Wall -O2")

include_directories(dep ${CMAKE_SOURCE_DIR}/dep/libuv)
link_directories(${CMAKE_SOURCE_DIR}/dep/libuv)

set(dnslibf dep/dnslib)

add_library(dns ${dnslibf}/buffer.cpp ${dnslibf}/message.cpp ${dnslibf}/rr.cpp ${dnslibf}/qs.cpp)

add_executable(dnset src/main.cpp src/forwarder.cpp src/config.cpp)
target_link_libraries(dnset uv dns)

add_executable(testmatcher src/matcher.cpp src/testmatcher.cpp)
add_executable(testconfig src/config.cpp src/testconfig.cpp)
target_link_libraries(testconfig uv dns)

