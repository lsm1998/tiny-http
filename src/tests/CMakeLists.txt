enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

link_libraries(${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

add_executable(string_util_test string_util_test.cpp ../global/string_util.cpp)

# 将Google Test库链接到测试目标
target_link_libraries(string_util_test PRIVATE gtest gtest_main)

# 添加测试
add_test(NAME string_util_test COMMAND string_util_test)