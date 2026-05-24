set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR X86)

set(MSVC_TRIPLE i686-pc-windows-msvc)

set(CMAKE_C_COMPILER clang-cl CACHE STRING "" FORCE)
set(CMAKE_C_COMPILER_TARGET ${MSVC_TRIPLE} CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER clang-cl CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER_TARGET ${MSVC_TRIPLE} CACHE STRING "" FORCE)
set(CMAKE_LINKER lld-link CACHE STRING "" FORCE)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY" CACHE STRING "" FORCE)

get_filename_component(PROJECT_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(WIN_SDK_DIR "${PROJECT_ROOT_DIR}/win_sdk")

execute_process(
    COMMAND clang -print-resource-dir
    OUTPUT_VARIABLE CLANG_RESOURCE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Fix 1: Stop the compiler from injecting modern security/RTTI stubs
set(CMAKE_C_FLAGS "/Zl /GS- -msse3 /D_MBCS /DSDL_JOYSTICK_XINPUT" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "/Zl /GS- /GR- /EHs- -msse3 /D_MBCS /DSDL_JOYSTICK_XINPUT" CACHE STRING "" FORCE)

include_directories(SYSTEM
    "${WIN_SDK_DIR}/crt/include"
    "${WIN_SDK_DIR}/sdk/include/ucrt"
    "${WIN_SDK_DIR}/sdk/include/um"
    "${WIN_SDK_DIR}/sdk/include/shared"
    "${CLANG_RESOURCE_DIR}/include"
)

set(CRT_LIB_DIR "${WIN_SDK_DIR}/crt/lib/x86")
set(UM_LIB_DIR "${WIN_SDK_DIR}/sdk/lib/um/x86")

set(LINK_FLAGS "/libpath:\"${CRT_LIB_DIR}\" /libpath:\"${UM_LIB_DIR}\" /nodefaultlib")

set(CMAKE_EXE_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)

# Fix 2: Bypass the modern VS startup library entry point completely
# This tells CMake: If the target name is NOT "SDL2", add the entry point.
# If it IS "SDL2", add nothing.
add_link_options("$<IF:$<STREQUAL:$<TARGET_PROPERTY:NAME>,SDL2>,,/entry:DllMain@12>")

set(CMAKE_C_STANDARD_LIBRARIES "kernel32.lib msvcrt.lib oldnames.lib" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_LIBRARIES "kernel32.lib msvcrt.lib oldnames.lib" CACHE STRING "" FORCE)
