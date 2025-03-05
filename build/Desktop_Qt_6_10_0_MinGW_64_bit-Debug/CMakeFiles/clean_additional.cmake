# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMSC437Booking_autogen"
  "CMakeFiles\\CMSC437Booking_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CMSC437Booking_autogen.dir\\ParseCache.txt"
  )
endif()
