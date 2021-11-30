cmake_minimum_required(VERSION 3.14)

project(tlshc VERSION 1.0.0 LANGUAGES C)

include(GNUInstallDirs)

add_library(tlshc STATIC
        src/tlsh_impl.c
        src/tlsh_util.c
        src/tlsh.c
)

target_compile_options(tlshc PRIVATE -Wall -fpie)
target_compile_features(tlshc PRIVATE c_std_11)

# TLSH uses only half the counting buckets.
# It can use all the buckets now.
set(TLSH_BUCKETS_128 1)

if(TLSH_BUCKETS_48 EQUAL 1)
  set(TLSH_HASH "min hash")
  add_definitions(-DBUCKETS_48)
endif()
if(TLSH_BUCKETS_128 EQUAL 1)
  set(TLSH_HASH "compact hash")
  add_definitions(-DBUCKETS_128)
endif()
if(TLSH_BUCKETS_256 EQUAL 1)
  set(TLSH_HASH "full hash")
  add_definitions(-DBUCKETS_256)
endif()

# TLSH uses 1 byte checksum. The collision rate is 1 in 24.
# It can use 3 bytes checksum now. That collision rate in 1 in 5800.
set(TLSH_CHECKSUM_1B 1)

if(TLSH_CHECKSUM_0B EQUAL 1)
  set(TLSH_CHECKSUM "no checksum")
  add_definitions(-DCHECKSUM_0B)
endif()
if(TLSH_CHECKSUM_1B EQUAL 1)
  set(TLSH_CHECKSUM "1 byte checksum")
endif()
if(TLSH_CHECKSUM_3B EQUAL 1)
  set(TLSH_CHECKSUM "3 bytes checksum")
  add_definitions(-DCHECKSUM_3B)
endif()

# setting TLSH_DISTANCE_PARAMETERS to 1 allows you to set command line arguments
# to set - and hence experiment with the distance parameters
#	by default this is zero
set(TLSH_DISTANCE_PARAMETERS 0)

target_include_directories(tlshc
        PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(
        DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS tlshc
        EXPORT tlshc-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/tlshc)

install(EXPORT tlshc-targets
        FILE "tlshc-targets.cmake"
        DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)

configure_file(
        "tlshc-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/tlshc-config.cmake"
        @ONLY
)
install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/tlshc-config.cmake"
        DESTINATION ${INSTALL_CONFIGDIR}
)

if(BUILD_TESTS) 
        enable_testing()
        add_subdirectory(tests)
endif()
