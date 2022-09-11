include_directories(
  include/
)

# Ommp Hardware Interface
add_library(Assem_fnl_hw_interface
  src/Assem_fnl_hw_interface.cpp
)
target_link_libraries(Assem_fnl_hw_interface
  generic_hw_interface
  ${catkin_LIBRARIES}
)

# Main control executable
add_executable(Assem_fnl_hw_main src/Assem_fnl_hw_main.cpp)
target_link_libraries(Assem_fnl_hw_main
  Assem_fnl_hw_interface
  generic_hw_control_loop
  ${catkin_LIBRARIES}
)

## Install ------------------------------------------------------------

# Install libraries
install(TARGETS
    Assem_fnl_hw_interface
  LIBRARY DESTINATION
    ${CATKIN_PACKAGE_LIB_DESTINATION}
)

# Install executables
install(TARGETS
    Assem_fnl_hw_main
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Install header files
install(DIRECTORY include/Assem_fnl_control/   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
