# Install script for directory: C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/JUCE")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/modules/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/extras/Build/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/JUCEConfigVersion.cmake"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/JUCEConfig.cmake"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/JUCECheckAtomic.cmake"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/JUCEHelperTargets.cmake"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/JUCEModuleSupport.cmake"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/JUCEUtils.cmake"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/JuceLV2Defines.h.in"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/LaunchScreen.storyboard"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/PIPAudioProcessorWithARA.cpp.in"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/PIPComponent.cpp.in"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/PIPConsole.cpp.in"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/copyDir.cmake"
    "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.5" TYPE EXECUTABLE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/Debug/juce_lv2_helper.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.5" TYPE EXECUTABLE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/Release/juce_lv2_helper.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.5" TYPE EXECUTABLE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/MinSizeRel/juce_lv2_helper.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.5" TYPE EXECUTABLE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/RelWithDebInfo/juce_lv2_helper.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake"
         "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5/LV2_HELPER-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Kelson/Documents/Projects/lerp_thing/JUCE/cmake-build/tools/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
