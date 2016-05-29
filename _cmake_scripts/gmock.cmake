set(GMOCK_ROOT ${MAINFOLDER}/thirdparty/gmock)
add_subdirectory(${GMOCK_ROOT})
set(GMOCK_INCLUDE_DIR ${GMOCK_ROOT}/include)
set(GMOCK_LIBRARIES gmock)
include_directories(${GMOCK_INCLUDE_DIR})

#gtest
set(GTEST_ROOT ${GMOCK_ROOT}/gtest)
set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
set(GTEST_LIBRARIES gtest gtest_main)
include_directories(${GTEST_INCLUDE_DIR})