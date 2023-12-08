file(GLOB HTTP_SOURCE_FILES "http/*.cpp")
file(GLOB CORE_SOURCE_FILES "core/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${HTTP_SOURCE_FILES} ${CORE_SOURCE_FILES})