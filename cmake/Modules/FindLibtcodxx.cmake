find_path(LIBTCODXX_INCLUDE_DIR libtcod.hpp
          HINTS ../include/ )

find_library(LIBTCODXX_LIBRARY NAMES libtcodxx tcodxx
             HINTS ../lib/ )

set(LIBTCODXX_LIBRARIES ${LIBTCODXX_LIBRARY} )
set(LIBTCODXX_INCLUDE_DIRS ${LIBTCODXX_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBTCODXX DEFAULT_MSG
                                  LIBTCODXX_LIBRARY LIBTCODXX_INCLUDE_DIR)

mark_as_advanced(LIBTCODXX_INCLUDE_DIR LIBTCODXX_LIBRARY)