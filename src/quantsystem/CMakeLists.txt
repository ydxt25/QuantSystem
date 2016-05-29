add_library(quantsystem STATIC
  algorithm/qsalgorithm.cc
  api/api.cc
  compression/compression.cc
  configuration/configuration.cc
  messaging/messaging.cc
  queues/queue.cc
  )

target_link_libraries(quantsystem quantsystem_common)
target_link_libraries(quantsystem quantsystem_common_data)
target_link_libraries(quantsystem quantsystem_common_packets)
target_link_libraries(quantsystem ${GLOG_LIBRARY})
install(TARGETS  quantsystem DESTINATION
  ${QUANTSYSTEM_INSTALL_LIB_DIR})

install(FILES
  algorithm/qsalgorithm.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/algorithm)

install(FILES
  api/api.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/api)

install(FILES
  compression/compression.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/compression)

install(FILES
  configuration/configuration.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/configuration)

install(FILES
  interfaces/ialgorithm.h
  interfaces/iapi.h
  interfaces/ibrokerage.h
  interfaces/imessaging_handler.h
  interfaces/iqueue_handler.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/interfaces)

install(FILES
  messaging/messaging.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/messaging)

install(FILES
  queues/queue.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/queues)

# Test
# Some gtest enhancements to facilitate test setup and cleanup.
add_library(quantsystem_gtest_main STATIC
  configuration/test/quantsystem_gtest_main.cc)
target_link_libraries(quantsystem_gtest_main quantsystem_common)
target_link_libraries(quantsystem_gtest_main ${GLOG_LIBRARY})
target_link_libraries(quantsystem_gtest_main gtest_main)

# Define an executable and adds a test for it using the most basic libraries
# Args:
#    name  - name of test. Must have a source file in test/<name>.cc
#    ...   - optional list of additional library dependencies
function(project_test module name)
  add_executable(${name} ${module}/test/${name}.cc)
  foreach (lib "${ARGN}")
    target_link_libraries(${name} ${lib})
  endforeach()
  target_link_libraries(${name} quantsystem_common)
  target_link_libraries(${name} ${GLOG_LIBRARY})
  target_linK_libraries(${name} quantsystem_gtest_main)
  target_linK_libraries(${name} ${GMOCK_LIBRARIES})
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
endfunction()

if (quantsystem_build_tests)
  project_test(configuration configuration_test quantsystem)
  file(COPY configuration/test/config.json
    DESTINATION ${EXECUTABLE_OUTPUT_PATH})
  project_test(compression compression_test quantsystem)
endif() # quantsystem_build_tests

add_subdirectory(brokerages)
add_subdirectory(common)
add_subdirectory(engine)
add_subdirectory(indicators)

