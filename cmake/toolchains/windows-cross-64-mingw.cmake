# Source - https://stackoverflow.com/a/28047073
# Posted by malat, modified by community. See post 'Timeline' for change history
# Retrieved 2026-05-05, License - CC BY-SA 4.0

# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_C_FLAGS "-m64")
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_CXX_FLAGS "-m64")