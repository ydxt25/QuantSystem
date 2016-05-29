add_library(quantsystem_common_securities STATIC
  security_cache.cc
  security.cc
  security_data_filter.cc
  security_exchange.cc
  security_holding.cc
  security_manager.cc
  security_portfolio_manager.cc
  security_transaction_manager.cc
  security_transaction_model.cc
  equity/equity_cache.cc
  equity/equity_data_filter.cc
  equity/equity_exchange.cc
  equity/equity.cc
  equity/equity_holding.cc
  equity/equity_transaction_model.cc
  forex/forex_cache.cc
  forex/forex_data_filter.cc
  forex/forex_exchange.cc
  forex/forex.cc
  forex/forex_holding.cc
  forex/forex_transaction_model.cc
  )

target_link_libraries(quantsystem_common_securities ${GLOG_LIBRARY})
target_link_libraries(quantsystem_common_securities quantsystem_common)
target_link_libraries(quantsystem_common_securities quantsystem_common_data)
install(TARGETS quantsystem_common_securities
  DESTINATION ${QUANTSYSTEM_INSTALL_LIB_DIR})

install(FILES
  security_cache.h
  security_data_filter.h
  security_exchange.h
  security.h
  security_holding.h
  security_manager.h
  security_portfolio_manager.h
  security_transaction_manager.h
  security_transaction_model.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/securities)

install(FILES
  equity/equity_cache.h
  equity/equity_data_filter.h
  equity/equity_exchange.h
  equity/equity.h
  equity/equity_holding.h
  equity/equity_transaction_model.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/securities/equity)

install(FILES
  forex/forex_cache.h
  forex/forex_data_filter.h
  forex/forex_exchange.h
  forex/forex.h
  forex/forex_holding.h
  forex/forex_transaction_model.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/securities/forex)

install(FILES
  interfaces/isecurity_data_filter.h
  interfaces/isecurity_transaction_model.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/securities/interfaces)


if (quantsystem_build_tests)

endif() # quantsystem_build_tests