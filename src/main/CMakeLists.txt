include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(OMOPSO_main OMOPSO_main.cpp)
target_link_libraries(OMOPSO_main jMetalCpp)
