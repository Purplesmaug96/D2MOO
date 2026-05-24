
D2MOO_prepare_targets(Storm)

target_link_libraries(${StormImplName} PUBLIC D2CommonDefinitions squall::Storm)
if(WIN32)
target_compile_definitions(${StormImplName} PUBLIC)
else()
target_compile_definitions(${StormImplName} PUBLIC WITH_SQUALL=1)
endif()

target_sources(${StormImplName}
  PRIVATE
    src/Storm.cpp

    include/Storm.h
    include/StormHandles.h
)

D2MOO_target_source_group(Storm)