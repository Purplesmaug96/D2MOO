D2MOO_prepare_targets(D2Server)

#  SDL2_image::SDL2_image
target_link_libraries(${D2ServerImplName} PUBLIC D2CommonDefinitions)

target_sources(${D2ServerImplName}
  PRIVATE
	src/D2Server.cpp
)

D2MOO_target_source_group(D2Server)
