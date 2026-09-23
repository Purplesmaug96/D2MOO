#ifndef D2SERVER_H
#define D2SERVER_H

// D2Server module header
// Provides the interface for the D2Server module

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Server control functions
void D2Server_SetPort(int gamePort, int serverPort);
void D2Server_RequestShutdown(void);
int D2Server_IsRunning(void);

// D2ServerInterface - main entry point called by Game.D2MOO
void* __stdcall D2ServerInterface(void* pCfg);

#ifdef __cplusplus
}
#endif

#endif // D2SERVER_H
