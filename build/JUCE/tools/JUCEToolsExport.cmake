# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6...3.18)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget juce_tools::juceaide)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target juce_tools::juceaide
add_executable(juce_tools::juceaide IMPORTED)

# Import target "juce_tools::juceaide" for configuration "Debug"
set_property(TARGET juce_tools::juceaide APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(juce_tools::juceaide PROPERTIES
  IMPORTED_LOCATION_DEBUG "C:/Users/Kelson/Documents/Projects/math_tool/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide.exe"
  )

# Import target "juce_tools::juceaide" for configuration "Release"
set_property(TARGET juce_tools::juceaide APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(juce_tools::juceaide PROPERTIES
  IMPORTED_LOCATION_RELEASE "C:/Users/Kelson/Documents/Projects/math_tool/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Release/juceaide.exe"
  )

# Import target "juce_tools::juceaide" for configuration "MinSizeRel"
set_property(TARGET juce_tools::juceaide APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(juce_tools::juceaide PROPERTIES
  IMPORTED_LOCATION_MINSIZEREL "C:/Users/Kelson/Documents/Projects/math_tool/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/MinSizeRel/juceaide.exe"
  )

# Import target "juce_tools::juceaide" for configuration "RelWithDebInfo"
set_property(TARGET juce_tools::juceaide APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(juce_tools::juceaide PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "C:/Users/Kelson/Documents/Projects/math_tool/build/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/RelWithDebInfo/juceaide.exe"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
