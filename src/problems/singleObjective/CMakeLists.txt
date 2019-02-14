file(GLOB SOURCES "*.cpp" "*.h")
ListToString(SOURCES ";" ${SOURCES})
LIST_APPEND("${SOURCES}")
add_subdirectory(cec2005Competition)