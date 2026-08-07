
# Disable clang-tidy for external dependencies.
# This should really be avoided but that's what we get for including deps directly...
set(CMAKE_CXX_CLANG_TIDY "")
set(CMAKE_FOLDER external)

# SDL2
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)

if(${CMAKE_SYSTEM_NAME} MATCHES "NintendoWii")
add_compile_definitions(STDC_HEADERS HAVE_STDDEF_H HAVE_STDINT_H HAVE_STRING_H HAVE_STDIO_H LACKS_SYS_MMAN_H)
add_definitions(-DHAVE_MMAP=false	)
add_subdirectory(sdl2-wii EXCLUDE_FROM_ALL)
else()

if(USE_SDL3)
	set(SDL_LIBC ON FORCE)
    add_subdirectory(sdl3 EXCLUDE_FROM_ALL)
    
    if(WIN32 AND TARGET SDL3-shared)

        target_link_options(SDL3-shared PRIVATE "-nodefaultlib:dll_dllmain_stub.obj")
    endif()
    
    if(WIN32 AND TARGET SDL3-shared)
        add_custom_target(SDL3-copy-to-bin ALL
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:SDL3-shared>
                ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
            DEPENDS SDL3-shared
        )
    endif()
    
    add_library(SDL INTERFACE)
    target_link_libraries(SDL INTERFACE SDL3::SDL3)

else()
    add_subdirectory(sdl2 EXCLUDE_FROM_ALL)
    
    if(WIN32 AND TARGET SDL2-shared)
        target_link_options(SDL2-shared PRIVATE "-nodefaultlib:dll_dllmain_stub.obj")
    endif()
    
    add_library(SDL INTERFACE)
    target_link_libraries(SDL INTERFACE SDL2::SDL2)
endif()

endif()
# add_subdirectory(sdl2_image EXCLUDE_FROM_ALL)

set(BUILD_SHARED_LIBS_BACKUP ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF) # Build external libs as static libs (or their default settings) for now

if(ENABLE_D2DETOURS_EMBEDDED_PATCHES)
  add_subdirectory(D2.Detours)

  # Look for D2SE first, then Diablo II.
  find_program(D2_EXE NAMES D2SE.exe "Game.exe" "Diablo II.exe"
    HINTS $ENV{D2INSTALL} $ENV{D2SE}
    PATH_SUFFIXES "Diablo II"
  )
  if(D2_EXE)
    get_filename_component(D2_PATH ${D2_EXE} DIRECTORY CACHE)
  else()
    message(STATUS "D2 executable was not found, please set the `D2_EXE` CMake variable for debugging if your game executable is not at the install location.")
  endif()
endif()




#Doctest for unit tests
add_library(doctest INTERFACE)
target_include_directories(doctest SYSTEM
    INTERFACE
    doctest/doctest # note : will expose the parts/ folder...
)
add_library(doctest::doctest ALIAS doctest)

if(WIN32)
	add_library(imgui
		#source files
		imgui/imgui.cpp
		imgui/imgui_draw.cpp
		imgui/imgui_demo.cpp
		imgui/imgui_tables.cpp
		imgui/imgui_widgets.cpp

		#headers
		imgui/imgui.h
		imgui/imgui_internal.h

		#backend
		imgui/backends/imgui_impl_win32.cpp
		imgui/backends/imgui_impl_win32.h
		imgui/backends/imgui_impl_dx9.cpp
		imgui/backends/imgui_impl_dx9.h
	)
	target_include_directories(imgui SYSTEM
		PUBLIC imgui
		PUBLIC imgui/backends/
	)
	add_library(imgui::imgui ALIAS imgui)
endif()

if(WIN32)

# Note: we only use squall for a few headers
# We may want to use the whole library at some point though.

add_library(squallstorm
	squall/storm/thread/CCritSect.cpp
	squall/storm/Memory.cpp
	squall/storm/Error.cpp
	squall/storm/error/win/Error.cpp
	squall/storm/hash/Hashkey.cpp
	squall/storm/String.cpp
	squall/storm/string/bjhash.cpp
)

target_include_directories(squallstorm SYSTEM PUBLIC squall)
add_compile_definitions(WHOA_SYSTEM_WIN WHOA_STORM_FLAVOR_DIABLO2)
add_library(squall::Storm ALIAS squallstorm)


else()

add_subdirectory(squall)
add_library(squallstorm INTERFACE)
target_link_libraries(squallstorm INTERFACE storm)
target_include_directories(squallstorm SYSTEM INTERFACE squall)
add_library(squall::Storm ALIAS squallstorm)
add_library(Storm ALIAS squallstorm)

endif()

#STB for image writing
add_library(stb INTERFACE)
target_include_directories(stb SYSTEM
    INTERFACE
    stb # note : will expose the parts/ folder...
)
add_library(stb::stb ALIAS stb)

if(NOT WIN32 AND NOT MINGW)
set(LIBWIN_HEADER_ONLY FALSE)
add_subdirectory(libwin)
endif()

# Restore BUILD_SHARED_LIBS
set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_BACKUP})