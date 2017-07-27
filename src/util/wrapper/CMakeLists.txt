file(GLOB SOURCES "*.cpp" "*.h")
ListToString(SOURCES ";" ${SOURCES})
LIST_APPEND("${SOURCES}")
