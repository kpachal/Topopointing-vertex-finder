cmake_minimum_required(VERSION 3.7)

project(topopointing)

find_package(ROOT REQUIRED COMPONENTS ROOTDataFrame)

add_definitions(-Wfatal-errors -Wall -Wextra -Werror)

include(${ROOT_USE_FILE})
include_directories(BEFORE extern/include)
include_directories(include)
include_directories(tests)


root_generate_dictionary(G__dictionary
                         topopointing/objects.h
                         topopointing/topo_fitter.h
                         LINKDEF
                         LinkDef.h)

# Add other .cxx files here if/when they exist
# and dont' forget to set classes in LinkDef
set(test_stoppedparticles_SRC
    src/objects.cxx
    src/topo_fitter.cxx
    tests/test_stoppedparticles.cxx)

set(test_AOD_SRC
    src/objects.cxx
    src/topo_fitter.cxx
    tests/test_AOD.cxx)

# Make me a setup script directly in the build directory
configure_file(tools/setup.sh.in setup.sh @ONLY)

# Tell CMake to create the executables
add_executable(test_StoppedParticles
               ${test_stoppedparticles_SRC}
               G__dictionary.cxx)

add_executable(test_AOD
               ${test_AOD_SRC}
               G__dictionary.cxx)


target_link_libraries(test_StoppedParticles ${ROOT_LIBRARIES})
target_link_libraries(test_AOD ${ROOT_LIBRARIES})
