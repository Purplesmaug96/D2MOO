
if (ANDROID)
add_library(Game SHARED
  src/Main.cpp
  include/Main.h

  resources/Game.rc
)
set_target_properties(Game PROPERTIES CLEAN_DIRECT_OUTPUT 1)
# Ensure symbols are fully exported for dlsym runtime resolution
set_target_properties(Game PROPERTIES ENABLE_EXPORTS TRUE)
# Block the compiler from stripping symbol visibility on optimizations
target_compile_options(Game PRIVATE -fvisibility=default)
find_library(DL_L_LIB NAMES libdl.so dl)
target_link_libraries(Game PRIVATE ${DL_D_LIB})
else()
add_executable(Game WIN32
  src/Main.cpp
  include/Main.h

  resources/Game.rc
)
endif()

if(EXISTS resources/Game.${D2MOO_ORDINALS_VERSION}.rc)
  target_sources(Game PRIVATE resources/Game.${D2MOO_ORDINALS_VERSION}.rc)
endif()

target_include_directories(Game PRIVATE include)
target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/source/Modules/D2Client/include
    ${CMAKE_SOURCE_DIR}/source/Modules/D2Server/include
    ${CMAKE_SOURCE_DIR}/source/Modules/D2Launch/include
    ${CMAKE_SOURCE_DIR}/source/Modules/D2Multi/include
    ${CMAKE_SOURCE_DIR}/source/Modules/D2MultiLAN/include
    ${CMAKE_SOURCE_DIR}/source/Modules/D2EClient/include
)

target_link_libraries(Game
  PRIVATE
    Fog
	Storm
	D2Win
	D2Gfx
	D2Sound
	D2MCPClient
	SDL
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
find_package(json-c CONFIG QUIET)
if(TARGET json-c::json-c)
  # Check if IMPORTED_LOCATION is set; if not, set it manually
  get_target_property(_jsonc_loc json-c::json-c IMPORTED_LOCATION)
  if(NOT _jsonc_loc)
    find_library(_jsonc_lib NAMES json-c)
    if(_jsonc_lib)
      set_target_properties(json-c::json-c PROPERTIES IMPORTED_LOCATION "${_jsonc_lib}")
    endif()
  endif()
else()
  # Fallback: use pkg-config
  find_library(_jsonc_lib NAMES json-c)
  find_path(_jsonc_inc NAMES json-c/json.h)
  if(_jsonc_lib)
    add_library(json-c::json-c UNKNOWN IMPORTED)
    set_target_properties(json-c::json-c PROPERTIES
      IMPORTED_LOCATION "${_jsonc_lib}"
      INTERFACE_INCLUDE_DIRECTORIES "${_jsonc_inc}"
    )
  endif()
endif()
target_link_libraries(Game PRIVATE json-c::json-c)
target_compile_definitions(Game PRIVATE libwin_has_jsonc)
endif()


if(NOT BUILD_SHARED_LIBS)
target_link_libraries(Game PRIVATE D2Client D2Server D2Multi D2Launch D2MultiLAN D2EClient)
endif()

# On Linux with shared libs, link module shared libraries directly
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND BUILD_SHARED_LIBS)
  target_link_libraries(Game PRIVATE
    D2Client D2Server D2Multi D2Launch D2MultiLAN D2EClient D2SDLRender
  )
endif()

if(NOT ANDROID)
set_target_properties(Game PROPERTIES OUTPUT_NAME Game.D2MOO)
endif()

if(D2MOO_WITH_STATIC_TESTS)
  target_sources(Game
    PRIVATE
      statictests/Game_staticchecks.cpp
  )
endif()
