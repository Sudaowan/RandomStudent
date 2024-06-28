# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\RandomStudent_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\RandomStudent_autogen.dir\\ParseCache.txt"
  "RandomStudent_autogen"
  )
endif()
