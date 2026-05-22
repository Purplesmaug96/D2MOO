D2MOO_prepare_targets(D2MultiLAN)

#  SDL2_image::SDL2_image
target_link_libraries(${D2MultiLANImplName} PUBLIC D2CommonDefinitions)

target_sources(${D2MultiLANImplName}
  PRIVATE
	src/D2MultiLAN.cpp
)

D2MOO_target_source_group(D2MultiLAN)
