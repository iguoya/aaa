cmake_minimum_required(VERSION 2.8)  
   
# Locate GTest  
find_package(GTest REQUIRED)  
include_directories(${GTEST_INCLUDE_DIRS})  
   
# Link runTests with what we want to test and the GTest and pthread library  
add_executable(runTests T_MF.cpp)  
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)  
