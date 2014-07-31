find_library(LIBPROTOBUF_LIBRARY NAMES libprotobuf
             HINTS ../../lib/ )

set(LIBPROTOBUF_LIBRARIES ${LIBPROTOBUF_LIBRARY} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBPROTOBUF DEFAULT_MSG
                                  LIBPROTOBUF_LIBRARY)

mark_as_advanced(LIBPROTOBUF_LIBRARY)