# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BookingApp_autogen"
  "CMakeFiles\\BookingApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BookingApp_autogen.dir\\ParseCache.txt"
  )
endif()
