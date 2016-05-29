add_library(quantsystem_brokerages STATIC
  brokerage.cc
  paper/paper_brokerage.cc
  tradier/tradier_brokerage.cc
  tradier/tradier_gain_loss.cc
  tradier/tradier_orders.cc
  tradier/tradier_positions.cc
  tradier/tradier_tokens.cc
  tradier/tradier_user_profile.cc
  )

target_link_libraries(quantsystem_brokerages ${GLOG_LIBRARY})
target_link_libraries(quantsystem_brokerages quantsystem_common)
install(TARGETS quantsystem_brokerages
  DESTINATION ${QUANTSYSTEM_INSTALL_LIB_DIR})

install(FILES
  brokerage.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/brokerages)

install(FILES
  paper/paper_brokerage.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/brokerages/paper)

install(FILES
  tradier/tradier_balance.h
  tradier/tradier_brokerage.h
  tradier/tradier_common.h
  tradier/tradier_data.h
  tradier/tradier_event.h
  tradier/tradier_fault.h
  tradier/tradier_gain_loss.h
  tradier/tradier_orders.h
  tradier/tradier_positions.h
  tradier/tradier_tokens.h
  tradier/tradier_user_profile.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/brokerages/tradier)

if (quantsystem_build_tests)

endif() # quantsystem_build_tests