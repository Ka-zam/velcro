set(CMAKE_VERBOSE_MAKEFILE "OFF")

#######################################################################################################
#
#  Add test program
#
#######################################################################################################
add_executable(tvel tvel.c)

target_include_directories(tvel PUBLIC
 ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(tvel PUBLIC
 velcro
)

#######################################################################################################
#
#  Install location
#
#######################################################################################################
set(APPS tvel)
install(TARGETS ${APPS} DESTINATION bin)
