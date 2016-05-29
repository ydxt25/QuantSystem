add_library(quantsystem_engine STATIC
  data_feeds/backtesting_data_feed.cc
  data_feeds/filesystem_data_feed.cc
  data_feeds/live_trading_data_feed.cc
  data_feeds/paper_trading_data_feed.cc
  data_feeds/testlive_trading_data_feed.cc
  real_time/backtesting_real_time_handler.cc
  real_time/live_trading_real_time_handler.cc
  real_time/real_time_event.cc
  results/backtesting_result_handler.cc
  results/console_result_handler.cc
  results/live_trading_result_handler.cc
  setup/backtesting_setup_handler.cc
  setup/console_setup_handler.cc
  setup/paper_trading_setup_handler.cc
  setup/tradier_setup_handler.cc
  transaction_handlers/backtesting_transaction_handler.cc
  transaction_handlers/tradier_transaction_handler.cc
  algorithm_manager.cc
  data_stream.cc
  stream_store.cc
  subscription_data_reader.cc
  subscription_scaling.cc
  subscription_stream_reader.cc
  )

target_link_libraries(quantsystem_engine ${GLOG_LIBRARY})
target_link_libraries(quantsystem_engine quantsystem_common)
target_link_libraries(quantsystem_engine quantsystem_common_data)
target_link_libraries(quantsystem_engine quantsystem_common_packets)
install(TARGETS quantsystem_engine
  DESTINATION ${QUANTSYSTEM_INSTALL_LIB_DIR})

install(FILES
  data_feeds/backtesting_data_feed.h
  data_feeds/filesystem_data_feed.h
  data_feeds/idata_feed.h
  data_feeds/live_trading_data_feed.h
  data_feeds/paper_trading_data_feed.h
  data_feeds/testlive_trading_data_feed.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/engine/data_feeds)

install(FILES
  real_time/backtesting_real_time_handler.h
  real_time/ireal_time_handler.h
  real_time/live_trading_real_time_handler.h
  real_time/real_time_event.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/engine/real_time)

install(FILES
  results/backtesting_result_handler.h
  results/console_result_handler.h
  results/iresult_handler.h
  results/live_trading_result_handler.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/engine/results)

install(FILES
  setup/backtesting_setup_handler.h
  setup/console_setup_handler.h
  setup/isetup_handler.h
  setup/paper_trading_setup_handler.h
  setup/tradier_setup_handler.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/engine/setup)

install(FILES
  transaction_handlers/backtesting_transaction_handler.h
  transaction_handlers/itransaction_handler.h
  transaction_handlers/tradier_transaction_handler.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/engine/transaction_handlers)

install(FILES
  algorithm_manager.h
  data_stream.h
  stream_store.h
  subscription_data_reader.h
  subscription_scaling.h
  subscription_stream_reader.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/engine/)

install(FILES
  config.json
  DESTINATION ${QUANTSYSTEM_INSTALL_DIR})
  
if (quantsystem_build_tests)

endif() # quantsystem_build_tests

SET (project_BIN ${PROJECT_NAME})
ADD_EXECUTABLE(${project_BIN} engine.cc)
SET (project_LIBS
  quantsystem_common
  quantsystem_common_data
  quantsystem_common_securities
  quantsystem_common_packets
  quantsystem_brokerages
  quantsystem_indicators
  quantsystem_engine
  quantsystem
  )

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})
SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION
  "${quantsystem_VERSION_MAJOR}.${quantsystem_VERSION_MINOR}"
  OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${project_BIN} DESTINATION ${QUANTSYSTEM_INSTALL_DIR})

