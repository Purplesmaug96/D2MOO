# Source - https://stackoverflow.com/a/28047073
# Posted by malat, modified by community. See post 'Timeline' for change history
# Retrieved 2026-05-05, License - CC BY-SA 4.0

# the name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "-m32")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-m32")

# here is the target environment located
set(CMAKE_FIND_ROOT_PATH   /usr/i486-linux-gnu)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
