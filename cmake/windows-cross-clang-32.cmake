set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR X86)

# Force MSVC target triple
set(MSVC_TRIPLE i686-pc-windows-msvc)

# Configure the clang-cl driver
set(CMAKE_C_COMPILER clang-cl CACHE STRING "" FORCE)
set(CMAKE_C_COMPILER_TARGET ${MSVC_TRIPLE} CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER clang-cl CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER_TARGET ${MSVC_TRIPLE} CACHE STRING "" FORCE)

set(CMAKE_LINKER lld-link CACHE STRING "" FORCE)

# Force CMake to test the compiler using static libraries to avoid execution tests
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY" CACHE STRING "" FORCE)

# Dynamic root calculation via the toolchain file path
get_filename_component(PROJECT_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(WIN_SDK_DIR "${PROJECT_ROOT_DIR}/win_sdk")

# Get internal Clang resource directory for compiler-specific headers
execute_process(
    COMMAND clang -print-resource-dir
    OUTPUT_VARIABLE CLANG_RESOURCE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Use /Zl to omit default library names from the .obj files.
# This prevents the compiler from automatically injecting modern library dependencies.
set(CMAKE_C_FLAGS "/Zl /D_MBCS" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "/Zl /D_MBCS" CACHE STRING "" FORCE)

# Set up include directories
include_directories(SYSTEM
    "${WIN_SDK_DIR}/crt/include"
    "${WIN_SDK_DIR}/sdk/include/ucrt"
    "${WIN_SDK_DIR}/sdk/include/um"
    "${WIN_SDK_DIR}/sdk/include/shared"
    "${CLANG_RESOURCE_DIR}/include"
)

# Define exact paths to the library directories
set(CRT_LIB_DIR "${WIN_SDK_DIR}/crt/lib/x86")
set(UM_LIB_DIR "${WIN_SDK_DIR}/sdk/lib/um/x86")

# Set up explicit linker library paths and drop the default library requirements
set(LINK_FLAGS "/libpath:\"${CRT_LIB_DIR}\" /libpath:\"${UM_LIB_DIR}\" /nodefaultlib")

# Set the entry point to the standard legacy DLL initialization function
# instead of the modern Visual Studio dllmain wrapper.
string(APPEND LINK_FLAGS " /entry:_DllMainCRTStartup@12")

set(CMAKE_EXE_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS "${LINK_FLAGS}" CACHE STRING "" FORCE)

# Explicitly pass the specific legacy libraries you intend to resolve symbols against
set(CMAKE_C_STANDARD_LIBRARIES "kernel32.lib msvcrt.lib oldnames.lib" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD_LIBRARIES "kernel32.lib msvcrt.lib oldnames.lib" CACHE STRING "" FORCE)