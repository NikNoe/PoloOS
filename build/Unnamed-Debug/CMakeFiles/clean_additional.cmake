# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appPoloOS_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appPoloOS_autogen.dir/ParseCache.txt"
  "appPoloOS_autogen"
  )
endif()
