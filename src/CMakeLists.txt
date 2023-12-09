file(GLOB HTTP_SOURCE_FILES "http/*.cpp")
file(GLOB CORE_SOURCE_FILES "core/*.cpp")
file(GLOB GLOBAL_SOURCE_FILES "global/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${HTTP_SOURCE_FILES} ${CORE_SOURCE_FILES} ${GLOBAL_SOURCE_FILES})