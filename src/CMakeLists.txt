file(GLOB HTTP_SOURCE_FILES "http/*.cpp")
file(GLOB CORE_SOURCE_FILES "core/*.cpp")
file(GLOB GLOBAL_SOURCE_FILES "global/*.cpp")
file(GLOB ROUTE_SOURCE_FILES "route/*.cpp")

add_executable(${PROJECT_NAME} main.cpp example/example.cpp ${HTTP_SOURCE_FILES} ${CORE_SOURCE_FILES} ${GLOBAL_SOURCE_FILES} ${ROUTE_SOURCE_FILES})

add_subdirectory(tests)