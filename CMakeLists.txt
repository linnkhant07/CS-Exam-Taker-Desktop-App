cmake_minimum_required (VERSION 3.8)
project (graderCPP)


#. . . . . . . . . . . . . . . . . . . .
include(GNUInstallDirs)
if(MSVC)
    add_compile_options(/W4)
    add_link_options(/W4)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
    # message("compiler: MSVC")
else()
    # message("compiler: NOT MSVC")
    # add_compile_options(-Wall -Wextra -pedantic -Werror -Wl,--fatal-warnings)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})



if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .

# ------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

 
enable_testing() 

# ------------------------------------

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all CPP files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(CPP_INCLUDES_FOLDER includes)
#FILE(GLOB_RECURSE CPP_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${CPP_INCLUDES_FOLDER}/*.cpp" )
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

set(CPP_SOURCE_FILES
    includes/obj_files/poly.cpp.obj
    includes/obj_files/term.cpp.obj
    #includes/array_functions/array_functions.h
   # Add more object files as needed
)


# Add source to this project's executable.
ADD_EXECUTABLE(basic_test
    _tests/_test_files/basic_test.cpp.obj
    ${CPP_SOURCE_FILES}

)
ADD_EXECUTABLE(testB
    _tests/_test_files/testB.cpp.obj
    ${CPP_SOURCE_FILES}

)

TARGET_LINK_LIBRARIES(basic_test gtest)
TARGET_LINK_LIBRARIES(testB gtest)