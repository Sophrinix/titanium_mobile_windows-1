# FindTitaniumWindows_App
# Author: Chris Williams
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

# Author: Chris Williams
# Created: 2014.12.02

set(TitaniumWindows_App_ARCH "x86")
if(CMAKE_GENERATOR MATCHES "^Visual Studio .+ ARM$")
  set(TitaniumWindows_App_ARCH "arm")
endif()

# Taken and slightly modified from build's TitaniumWindows_App_Targets.cmake file
# INTERFACE_INCLUDE_DIRECTORIES is modified to point to our pre-packaged include dir for module

# Create imported target TitaniumWindows_App
add_library(TitaniumWindows_App SHARED IMPORTED)

set_target_properties(TitaniumWindows_App PROPERTIES
  COMPATIBLE_INTERFACE_STRING "TitaniumWindows_App_MAJOR_VERSION"
  INTERFACE_INCLUDE_DIRECTORIES "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_App/include;$<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_Utility,INTERFACE_INCLUDE_DIRECTORIES>"
  INTERFACE_LINK_LIBRARIES "TitaniumKit;TitaniumWindows_Utility"
  INTERFACE_TitaniumWindows_App_MAJOR_VERSION "0"
)

set_target_properties(TitaniumWindows_App PROPERTIES
  IMPORTED_IMPLIB "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_App/${TitaniumWindows_App_ARCH}/TitaniumWindows_App.lib"
  IMPORTED_LOCATION "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_App/${TitaniumWindows_App_ARCH}/TitaniumWindows_App.dll"
  )
