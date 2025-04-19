# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ProccessControlTool_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ProccessControlTool_autogen.dir/ParseCache.txt"
  "ProccessControlTool_autogen"
  )
endif()
