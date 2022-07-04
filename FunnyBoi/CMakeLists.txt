cmake_minimum_required (VERSION 3.15)

add_executable (FunnyBoi "src/FunnyBoi.cpp" "src/FunnyBoi.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FunnyBoi PROPERTY CXX_STANDARD 20)
endif()
 
add_subdirectory(libs/DPP)
target_link_libraries(${PROJECT_NAME}
    dpp
)
 
target_include_directories(${PROJECT_NAME} PRIVATE
    libs/DPP/include
)
 
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)