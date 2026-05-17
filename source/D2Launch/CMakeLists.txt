
D2MOO_prepare_targets(D2Launch)

#  SDL2_image::SDL2_image
# target_link_libraries(${D2SDLRenderImplName} PUBLIC SDL2::SDL2 D2Gfx D2CommonDefinitions)

target_sources(${D2LaunchImplName}
  PRIVATE
	src/D2Launch.cpp
)

D2MOO_target_source_group(D2Launch)
