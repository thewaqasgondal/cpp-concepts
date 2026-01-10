# Install script for directory: /workspaces/cpp-concepts

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/workspaces/cpp-concepts/build/examples/basics/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/data_types/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/control_flow/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/functions/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/arrays_vectors/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/pointers_references/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/strings/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/exceptions/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/oop/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/memory_management/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/stl/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/advanced/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/file_io/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/move_semantics/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/algorithms/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/design_patterns/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/serialization/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/memory_pools/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/template_metaprogramming/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/performance_optimization/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/plugin_system/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/coroutines/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/concepts/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/ranges/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/parallel_algorithms/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/examples/simd_operations/cmake_install.cmake")
  include("/workspaces/cpp-concepts/build/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/workspaces/cpp-concepts/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
