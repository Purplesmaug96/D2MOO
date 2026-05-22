if(${CMAKE_SYSTEM_NAME} MATCHES "NintendoWii")
add_definitions(-Wno-attributes)
endif()

add_subdirectory(D2CommonDefinitions)

if(WIN32)
add_subdirectory(Storm)
endif()

add_subdirectory(Fog)
add_subdirectory(D2Hell)
add_subdirectory(D2CMP)
add_subdirectory(D2Lang)
add_subdirectory(D2Net)
add_subdirectory(D2Common)
add_subdirectory(D2Game)
add_subdirectory(D2Gfx)
add_subdirectory(D2Sound)
add_subdirectory(D2MCPClient)
add_subdirectory(D2Win)

add_subdirectory(Modules)

if (WIN32)
	add_subdirectory(D2Debugger)
endif()

add_subdirectory(Game)
add_subdirectory(D2SDLRender)
