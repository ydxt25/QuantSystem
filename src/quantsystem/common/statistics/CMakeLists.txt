
# The rest of googleapis is auto-generated.
# Really we'd like this to be part of some other external project.
add_library(quantsystem_common STATIC
  ./global.cc
  ./base/callback.cc
  ./base/once.cc
  ./base/stringprintf.cc
  ./base/strtoint.cc
  ./base/windows_compatability.cc
  ./json/jsoncpp.cc
  ./strings/ascii_ctype.cc
  ./strings/case.cc
  ./strings/escaping.cc
  ./strings/memutil.cc
  ./strings/numbers.cc
  ./strings/split.cc
  ./strings/strcat.cc
  ./strings/stringpiece.cc
  ./strings/strip.cc
  ./strings/util.cc
  ./time/date_time.cc
  ./time/time_span.cc
  ./util/executor.cc
  ./util/file.cc
  ./util/hash.cc
  ./util/status.cc
  )
target_link_libraries(quantsystem_common ${GLOG_LIBRARY})
install(TARGETS quantsystem_common DESTINATION ${QUANTSYSTEM_INSTALL_LIB_DIR})

install(FILES
  global.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common)

install(FILES 
  base/callback-specializations.h
  base/callback-types.h
  base/callback.h
  base/int128.h
  base/integral_types.h
  base/macros.h
  base/mutex.h
  base/once.h
  base/port.h
  base/scoped_ptr.h
  base/scoped_ptr_internals.h
  base/stringprintf.h
  base/strtoint.h
  base/template_util.h
  base/thread_annotations.h
  base/type_traits.h
  base/windows_compatability.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/base)

install(FILES
  json.h
  json-forwards.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/json)

install(FILES 
  strings/ascii_ctype.h
  strings/case.h
  strings/escaping.h
  strings/fastmem.h
  strings/join.h
  strings/memutil.h
  strings/numbers.h
  strings/split.h
  strings/strcat.h
  strings/stringpiece.h
  strings/strip.h
  strings/util.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/strings)

install(FILES
  time/date_time.h
  time/time_span.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/time)

install(FILES 
  util/algorithm.h
  util/case_insensitive_hash.h
  util/executor.h
  util/file.h
  util/hash.h
  util/mock_executor.h
  util/status.h
  util/stl_util.h
  DESTINATION ${QUANTSYSTEM_INSTALL_INCLUDE_DIR}/common/util)

if (quantsystem_build_tests)
  project_test(time date_time_test)
  project_test(time time_span_test)
endif() # quantsystem_build_tests