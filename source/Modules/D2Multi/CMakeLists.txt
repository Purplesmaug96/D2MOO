D2MOO_prepare_targets(D2Multi)

#  SDL2_image::SDL2_image
target_link_libraries(${D2MultiImplName} PUBLIC D2CommonDefinitions)

target_sources(${D2MultiImplName}
  PRIVATE
	src/D2Multi.cpp
)

D2MOO_target_source_group(D2Multi)
