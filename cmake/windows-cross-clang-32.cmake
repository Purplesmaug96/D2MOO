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

set(CMAKE_C_FLAGS "/Zl /GS- -msse3 /D_MBCS /DSDL_JOYSTICK_XINPUT" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "/Zl /GS- /GR- /EHs- /Gr -msse3 /D_MBCS /DSDL_JOYSTICK_XINPUT" CACHE STRING "" FORCE)

# Keep your previous fallback blocks active
add_compile_definitions(_HAS_NODISCARD=1)
add_compile_definitions(__CLR_ALLOWED=0)

include_directories(SYSTEM
    "${WIN_SDK_DIR}/crt/include"
    "${WIN_SDK_DIR}/sdk/include/ucrt"
    "${WIN_SDK_DIR}/sdk/include/um"
    "${WIN_SDK_DIR}/sdk/include/shared"
    "${CLANG_RESOURCE_DIR}/include"
)

set(CRT_LIB_DIR "${WIN_SDK_DIR}/crt/lib/x86")
set(UM_LIB_DIR "${WIN_SDK_DIR}/sdk/lib/um/x86")
set(UCRT_LIB_DIR "${WIN_SDK_DIR}/sdk/lib/ucrt/x86")

set(LINK_FLAGS "/libpath:\"${CRT_LIB_DIR}\" /libpath:\"${UCRT_LIB_DIR}\" /libpath:\"${UM_LIB_DIR}\" /nodefaultlib")

set(CMAKE_EXE_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)

# This satisfies _malloc, _free, _memset, etc., using the core runtime libraries.
# 1. Provide the exact standard static/import libraries for modern UCRT mapping
# Order matters: ucrt.lib resolves the modern __imp__malloc and stdio macros.
set(STD_LIBS "msvcprt.lib msvcrt.lib vcruntime.lib ucrt.lib user32.lib gdi32.lib shell32.lib kernel32.lib oldnames.lib")
set(CMAKE_C_STANDARD_LIBRARIES "${STD_LIBS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_LIBRARIES "${STD_LIBS}" CACHE STRING "" FORCE)

# 4. Target-Specific Entry Point Logic (The Generator Expression)
# Adds the /entry switch for everything except SDL2
# add_link_options("$<IF:$<STREQUAL:$<TARGET_PROPERTY:NAME>,SDL2>,,/entry:DllMain@12>")