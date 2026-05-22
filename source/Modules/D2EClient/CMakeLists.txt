D2MOO_prepare_targets(D2EClient)

#  SDL2_image::SDL2_image
target_link_libraries(${D2EClientImplName} PUBLIC D2CommonDefinitions)

target_sources(${D2EClientImplName}
  PRIVATE
	src/D2EClient.cpp
)

D2MOO_target_source_group(D2EClient)
