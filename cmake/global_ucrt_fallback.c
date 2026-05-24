
#include <windows.h>

// Handle modern UCRT tracking variables globally
void* __pRawDllMain = 0;
void* __crt_atexit = 0;
void* __crt_at_quick_exit = 0;

void __cdecl __initterm(void* a, void* b) {}
int __cdecl __initterm_e(void* a, void* b) { return 0; }
void __cdecl __configure_narrow_argv(int a) {}
int __cdecl __initialize_narrow_environment(void) { return 0; }
void __cdecl __initialize_onexit_table(void* a) {}
void* __cdecl __register_onexit_function(void* a, void* b) { return 0; }
int __cdecl __execute_onexit_table(void* a) { return 0; }
void __cdecl __cexit(void) {}
void __cdecl __seh_filter_dll(unsigned long a, void* b) {}
void __cdecl ___std_type_info_destroy_list(void* a) {}

// Pure Win32 Fallback Entry Point (No selectany or macros)
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    (void)hinstDLL; (void)fdwReason; (void)pvReserved;
    return TRUE;
}
