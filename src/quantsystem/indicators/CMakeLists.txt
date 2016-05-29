add_library(quantsystem_indicators STATIC
  aroon_oscillator.cc
  average_true_range.cc
  delay.cc
  exponential_indicator.cc
  identity.cc
  indicator_data_point.cc
  indicator_extension.cc
  maximum.cc
  minimum.cc
  momentum.cc
  momentum_percent.cc
  moving_average_converagence_divergence.cc
  moving_average_type_extensions.cc
  relative_strength_index.cc
  simple_moving_average.cc
  tradebar_indicator.cc
 )

target_link_libraries(quantsystem_indicators ${GLOG_LIBRARY})
target_link_libraries(quantsystem_indicators quantsystem_common)
install(TARGETS quantsystem_indicators
  DESTINATION ${QUANTSYSTEM_INSTALL_LIB_DIR})

install(FILES
  aroon_oscillator.h
  average_true_range.h
  constant_indicator.h
  delay.h
  exponential_indicator.h
  functional_indicator.h
  identity.h
  indicator_base.h
  indicator_data_point.h
  indicator_extension.h
  indicator.h
  iread_only_window.h
  maximum.h
  minimum.h
  momentum.h
  momentum_percent.h
  moving_average_converagence_divergence.h
  moving_average_type_extensions.h
  moving_average_type.h
  relative_strength_index.h
  rolling_window.h
  sequential_indicator.h
  simple_moving_average.h
  tradebar_indicator.h
  window_indicator.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/indicators)

if (quantsystem_build_tests)

endif() # quantsystem_build_tests