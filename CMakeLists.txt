cmake_minimum_required (VERSION 2.6)
project (pi)

set (pi_VERSION_MAJOR 1)
set (pi_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/pi.hxx"
  "${PROJECT_BINARY_DIR}/pi.generated.h"
  )
  
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/pi.hxx"
  "${PROJECT_BINARY_DIR}/pi.generated.h"
  )

add_executable(pi-server main.cpp queryAnswerType.h queryDnsType.h objectmodel/queryInfo.h objectmodel/queryResult.h)

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

find_package(cpprestsdk CONFIG REQUIRED)

if(WIN32)
    target_link_libraries(pi dnsapi)
endif()

if(UNIX)
    include(~/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif()
