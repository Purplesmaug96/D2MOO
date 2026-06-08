# Source - https://stackoverflow.com/a/28047073
# Posted by malat, modified by community. See post 'Timeline' for change history
# Retrieved 2026-05-05, License - CC BY-SA 4.0

# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_C_FLAGS "-m32")
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_CXX_FLAGS "-m32")

# Force MinGW headers to be used
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -isystem /usr/i686-w64-mingw32/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem /usr/i686-w64-mingw32/include")

# Prevent system headers from interfering
set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
