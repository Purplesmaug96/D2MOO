D2MOO_prepare_targets(D2Server)

# D2Server C++ wrapper (module interface bridge)
target_sources(${D2ServerImplName}
  PRIVATE
	src/D2Server.cpp

    include/D2Server.h
)

# D2Server decompiled source (Ghidra output, compiled as C++ to use libwin headers)
target_sources(${D2ServerImplName}
  PRIVATE
    src/d2server.cpp
    src/d2server_globals.cpp
)

# Link against the imported libraries
target_link_libraries(${D2ServerImplName} PRIVATE Fog Storm D2Common D2Net D2Game D2MCPClient)

# Suppress warnings for the whole target, but only the decompiled GDI/msg-loop
# d2server.cpp needs -fpermissive (GCC only) to downgrade pointer-int errors.
# D2Server.cpp (the strict wrapper) must never see -fpermissive.
# Clang doesn't have -fpermissive, so suppress the specific error categories instead
target_compile_options(${D2ServerImplName} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-w>
    $<$<CXX_COMPILER_ID:Clang>:-w -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-pointer-sign -Wno-literal-conversion -ferror-limit=0>
)
set_source_files_properties(src/d2server.cpp PROPERTIES COMPILE_FLAGS "-w -fpermissive")
set_source_files_properties(src/d2server_globals.cpp PROPERTIES COMPILE_FLAGS "-w")

D2MOO_target_source_group(D2Server)
