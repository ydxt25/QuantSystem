add_library(quantsystem_common_data STATIC
  ./base_data.cc
  ./dynamic_data.cc
  ./subscription_data_config.cc
  ./subscription_manager.cc
  ./consolidators/data_consolidator.cc
  ./consolidators/identity_data_consolidator.cc
  ./consolidators/sequential_consolidator.cc
  ./consolidators/tradebar_consolidator.cc
  ./custom/quandl.cc
  ./market/tick.cc
  ./market/ticks.cc
  ./market/tradebar.cc
  ./market/tradebars.cc
  )

target_link_libraries(quantsystem_common_data ${GLOG_LIBRARY})
target_link_libraries(quantsystem_common_data quantsystem_common)
install(TARGETS quantsystem_common_data
  DESTINATION ${QUANTSYSTEM_INSTALL_LIB_DIR})

install(FILES
  ./base_data.h
  ./dynamic_data.h
  ./subscription_data_config.h
  ./subscription_manager.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/data)

install(FILES
  ./consolidators/data_consolidator.h
  ./consolidators/identity_data_consolidator.h
  ./consolidators/sequential_consolidator.h
  ./consolidators/tradebar_consolidator.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/data/consolidators)

install(FILES
  ./custom/quandl.cc
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/custom)

install(FILES
  ./market/tick.h
  ./market/ticks.h
  ./market/tradebar.h
  ./market/tradebars.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/market)


if (quantsystem_build_tests)

endif() # quantsystem_build_tests