
D2MOO_prepare_targets(D2SDLRender)

#  SDL2_image::SDL2_image
target_link_libraries(${D2SDLRenderImplName} PUBLIC SDL D2Gfx D2CommonDefinitions)

target_sources(${D2SDLRenderImplName}
  PRIVATE
	src/D2SDLRender.cpp
	src/Cutscene.cpp
	src/Surface.cpp
	src/Perspective.cpp
	src/Options.cpp
	src/Utils.cpp
	src/Draw.cpp
	src/Texture.cpp
	src/Cell.cpp
	src/Tile.cpp
)

D2MOO_target_source_group(D2SDLRender)
