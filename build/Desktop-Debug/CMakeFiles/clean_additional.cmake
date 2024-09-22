# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/sillyTimer_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/sillyTimer_autogen.dir/ParseCache.txt"
  "sillyTimer_autogen"
  )
endif()
