D2MOO_prepare_targets(D2Client)

#  SDL2_image::SDL2_image
target_link_libraries(${D2ClientImplName} PUBLIC D2CommonDefinitions)

target_sources(${D2ClientImplName}
  PRIVATE
	src/D2Client.cpp
)

D2MOO_target_source_group(D2Client)
