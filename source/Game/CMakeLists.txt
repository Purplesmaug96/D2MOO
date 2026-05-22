
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

target_link_libraries(Game
  PRIVATE
    Fog
	Storm
	D2Win
	D2Gfx
	D2Sound
	D2MCPClient
	SDL2::SDL2
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
find_package(json-c CONFIG)
target_link_libraries(Game PRIVATE json-c::json-c)
target_compile_definitions(Game PRIVATE __windows_shim_has_jsonc)
endif()


if(NOT BUILD_SHARED_LIBS)
target_link_libraries(Game PRIVATE D2Client D2Server D2Multi D2Launch D2MultiLAN D2EClient)
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
