find_library(LIBTCOD_LIBRARY NAMES libtcod tcod
             HINTS ../lib/ )

set(LIBTCOD_LIBRARIES ${LIBTCOD_LIBRARY} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBTCOD DEFAULT_MSG
                                  LIBTCOD_LIBRARY)

mark_as_advanced(LIBTCOD_LIBRARY)