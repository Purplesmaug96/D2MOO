
D2MOO_prepare_targets(D2SDLRender)

target_link_libraries(${D2SDLRenderImplName} PUBLIC SDL2::SDL2-static)

target_sources(${D2SDLRenderImplName}
  PRIVATE
	src/D2SDLRender.cpp
)

D2MOO_target_source_group(D2SDLRender)
