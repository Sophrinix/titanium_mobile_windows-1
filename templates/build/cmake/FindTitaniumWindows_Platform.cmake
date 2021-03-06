# FindTitaniumWindows_Platform
# Author: Chris Williams
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

# Author: Chris Williams
# Created: 2014.12.02

set(TitaniumWindows_Platform_ARCH "x86")
if(CMAKE_GENERATOR MATCHES "^Visual Studio .+ ARM$")
  set(TitaniumWindows_Platform_ARCH "arm")
endif()

# Taken and slightly modified from build's TitaniumWindows_Platform_Targets.cmake file
# INTERFACE_INCLUDE_DIRECTORIES is modified to point to our pre-packaged include dir for module

# Create imported target TitaniumWindows_Platform
add_library(TitaniumWindows_Platform SHARED IMPORTED)

set_target_properties(TitaniumWindows_Platform PROPERTIES
  COMPATIBLE_INTERFACE_STRING "TitaniumWindows_Platform_MAJOR_VERSION"
  INTERFACE_INCLUDE_DIRECTORIES "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_Platform/include;$<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>"
  INTERFACE_LINK_LIBRARIES "TitaniumKit"
  INTERFACE_TitaniumWindows_Platform_MAJOR_VERSION "0"
)

set_target_properties(TitaniumWindows_Platform PROPERTIES
  IMPORTED_IMPLIB "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_Platform/${TitaniumWindows_Platform_ARCH}/TitaniumWindows_Platform.lib"
  IMPORTED_LOCATION "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_Platform/${TitaniumWindows_Platform_ARCH}/TitaniumWindows_Platform.dll"
  )
