D2MOO_prepare_targets(D2Server)

# D2GS_ENGINE=1 (default) drives the world with the real decompiled D2Game
# engine (M2 host: MPQ data tables + game creation + network-message pump).
# D2GS_ENGINE=0 keeps the capture-replay mini-server fallback.
option(D2GS_ENGINE "Drive D2Server with the decompiled D2Game engine" ON)
target_compile_definitions(${D2ServerImplName} PRIVATE D2GS_ENGINE=$<IF:$<BOOL:${D2GS_ENGINE}>,1,0>)

# D2Server C++ wrapper (module interface bridge)
target_sources(${D2ServerImplName}
  PRIVATE
	src/D2Server.cpp
	src/EngineHost.cpp

    include/D2Server.h
)

# Link against the imported libraries
target_link_libraries(${D2ServerImplName} PRIVATE Fog Storm D2Common D2Net D2Game D2MCPClient)

# D2Server.cpp and EngineHost.cpp are compiled with warnings on.

D2MOO_target_source_group(D2Server)
