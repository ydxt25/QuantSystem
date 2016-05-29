#ifndef QUANTSYSTEM_CPP_CONFIG_H_
#define QUANTSYSTEM_CPP_CONFIG_H_

#define quantsystem_VERSION_MAJOR 0
#define quantsystem_VERSION_MINOR 1
#define quantsystem_VERSION_PATCH 0
#define quantsystem_VERSION_DECORATOR ""

// Indicates whether libproc is available. This is used on OSx for process
// information rather than /proc on standard Unix.
/* #undef HAVE_LIBPROC */

// Indicates fstat64 as well as lseek64 since these probably go together
/* #undef HAVE_FSTAT64 */

// Indicates whether File suppports user/group/other permissions.
// In the current windows port, user group permissions are not available.
/* #undef HAVE_UGO_PERMISSIONS */

#endif  // QUANTSYSTEM_CPP_CONFIG_H_
