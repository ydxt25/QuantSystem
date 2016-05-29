add_library(quantsystem_common_packets STATIC
  backtest_node_packet.cc
  live_node_packet.cc
  algorithm_node_packet.cc
  algorithm_status_packet.cc
  backtest_result_packet.cc
  debug_packet.cc
  live_result_packet.cc
  log_packet.cc
  market_today_packet.cc
  order_event_packet.cc
  packet.cc
  runtime_error_packet.cc
  security_types_packet.cc
  )

target_link_libraries(quantsystem_common_packets ${GLOG_LIBRARY})
target_link_libraries(quantsystem_common_packets quantsystem_common)
target_link_libraries(quantsystem_common_packets quantsystem_common_data)
target_link_libraries(quantsystem_common_packets quantsystem_common_securities)

install(TARGETS quantsystem_common_packets
  DESTINATION ${QUANTSYSTEM_INSTALL_LIB_DIR})

install(FILES
  algorithm_node_packet.h
  algorithm_status_packet.h
  backtest_node_packet.h
  backtest_result_packet.h
  debug_packet.h
  live_node_packet.h
  live_result_packet.h
  log_packet.h
  market_today_packet.h
  order_event_packet.h
  packet.h
  runtime_error_packet.h
  security_types_packet.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/packets)


if (quantsystem_build_tests)

endif() # quantsystem_build_tests