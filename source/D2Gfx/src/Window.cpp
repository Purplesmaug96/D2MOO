#include "Window.h"

#ifdef USE_SDL3
#include <SDL3/SDL_platform.h>
#else
#include <SDL2/SDL_platform.h>
#endif

// Causes issue if not forced off
#define SDL_haptic_h_
#pragma warning(push)
#pragma warning(disable : 4820)

#pragma pack(push, 1)

#include <algorithm>

#include <cstddef>
#include <shellapi.h>
#include <wingdi.h>

#include <Fog.h>

#ifdef USE_SDL3
#include <SDL3/SDL.h>
#include <SDL3/SDL_hidapi.h>

#ifdef SDL_ENABLE
#undef SDL_ENABLE
#endif
#define SDL_ENABLE true

#ifdef SDL_DISABLE
#undef SDL_DISABLE
#endif
#define SDL_DISABLE false

#ifdef SDLK_a
#undef SDLK_a
#endif
#define SDLK_a SDLK_A

#ifdef SDLK_z
#undef SDLK_z
#endif
#define SDLK_z SDLK_Z

#ifdef SDL_KEYDOWN
#undef SDL_KEYDOWN
#endif
#define SDL_KEYDOWN SDL_EVENT_KEY_DOWN

#ifdef SDL_KEYUP
#undef SDL_KEYUP
#endif
#define SDL_KEYUP SDL_EVENT_KEY_UP

#ifdef SDL_MOUSEMOTION
#undef SDL_MOUSEMOTION
#endif
#define SDL_MOUSEMOTION SDL_EVENT_MOUSE_MOTION

#ifdef SDL_MOUSEBUTTONDOWN
#undef SDL_MOUSEBUTTONDOWN
#endif
#define SDL_MOUSEBUTTONDOWN SDL_EVENT_MOUSE_BUTTON_DOWN

#ifdef SDL_MOUSEBUTTONUP
#undef SDL_MOUSEBUTTONUP
#endif
#define SDL_MOUSEBUTTONUP SDL_EVENT_MOUSE_BUTTON_UP

#ifdef SDL_MOUSEWHEEL
#undef SDL_MOUSEWHEEL
#endif
#define SDL_MOUSEWHEEL SDL_EVENT_MOUSE_WHEEL

#ifdef SDL_WINDOWEVENT
#undef SDL_WINDOWEVENT
#endif
#define SDL_WINDOWEVENT SDL_EVENT_WINDOW_FIRST

#ifdef SDL_WINDOWEVENT_RESIZED
#undef SDL_WINDOWEVENT_RESIZED
#endif
#define SDL_WINDOWEVENT_RESIZED SDL_EVENT_WINDOW_RESIZED

#ifdef SDL_WINDOWEVENT_SIZE_CHANGED
#undef SDL_WINDOWEVENT_SIZE_CHANGED
#endif
#define SDL_WINDOWEVENT_SIZE_CHANGED SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED

#ifdef SDL_WINDOWEVENT_CLOSE
#undef SDL_WINDOWEVENT_CLOSE
#endif
#define SDL_WINDOWEVENT_CLOSE SDL_EVENT_WINDOW_CLOSE_REQUESTED

#ifdef SDL_WINDOWEVENT_FOCUS_GAINED
#undef SDL_WINDOWEVENT_FOCUS_GAINED
#endif
#define SDL_WINDOWEVENT_FOCUS_GAINED SDL_EVENT_WINDOW_FOCUS_GAINED

#ifdef SDL_WINDOWEVENT_FOCUS_LOST
#undef SDL_WINDOWEVENT_FOCUS_LOST
#endif
#define SDL_WINDOWEVENT_FOCUS_LOST SDL_EVENT_WINDOW_FOCUS_LOST

#ifdef SDL_WINDOW_SHOWN
#undef SDL_WINDOW_SHOWN
#endif
#define SDL_WINDOW_SHOWN 0

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_hidapi.h>
#include <SDL2/SDL_syswm.h>
#endif

#include "CmnSubtile.h"
#include "D2Gfx.h"
#include "DisplayType.h"

#pragma pack(pop, 1)

#pragma warning(pop)

extern DisplayType gnDisplayType;

HWND ghWnd;
int32_t gbIsWindowed;
D2GameResolutionMode gnResolutionMode;
// int32_t dword_6FA8D740;
D2WindowPlacementStrc gWindowPlacement[4];
int32_t gbCursorDisplayed;
int32_t gbNoWindowCreated_6FA8D848;
int32_t gbPaused_6FA8D84C;
int32_t gbWindowState_6FA8D850;
HINSTANCE ghInstance;

SDL_Window* gpWindow = NULL;
uint32_t windowFlags = 0;
WNDPROC g_oldProc;
extern WNDPROC gpfWndProc;

static void ShowCursor() {
	if (!gbCursorDisplayed) {
		#ifdef USE_SDL3
		SDL_ShowCursor();
		#else
		SDL_ShowCursor(SDL_ENABLE);
		#endif
		gbCursorDisplayed = 1;
	}
}
static void HideCursor() {
	if (gbCursorDisplayed) {
		#ifdef USE_SDL3
		SDL_HideCursor();
		#else
		SDL_ShowCursor(SDL_DISABLE);
		#endif
		gbCursorDisplayed = 0;
	}
}

/* Translator is made by AI, but i just wanna get something working, will be replaced with a proper SDL_Event handler later */

// Helper function to map basic SDL keycodes to Win32 Virtual Keys (VK_*)
WPARAM MapSDLKeyToVK(SDL_Keycode key) {
	if (key >= SDLK_a && key <= SDLK_z) {
		return key - SDLK_a + 'A';
	}
	if (key >= SDLK_0 && key <= SDLK_9) {
		return key;
	}

	switch (key) {
	case SDLK_ESCAPE:
		return VK_ESCAPE;
	case SDLK_RETURN:
		return VK_RETURN;
	case SDLK_SPACE:
		return VK_SPACE;
	case SDLK_BACKSPACE:
		return VK_BACK;
	case SDLK_TAB:
		return VK_TAB;
	case SDLK_UP:
		return VK_UP;
	case SDLK_DOWN:
		return VK_DOWN;
	case SDLK_LEFT:
		return VK_LEFT;
	case SDLK_RIGHT:
		return VK_RIGHT;
	case SDLK_LSHIFT:
	case SDLK_RSHIFT:
		return VK_SHIFT;
	case SDLK_LCTRL:
	case SDLK_RCTRL:
		return VK_CONTROL;
	case SDLK_LALT:
	case SDLK_RALT:
		return VK_MENU;
	// Add more specific mappings as needed
	default:
		return 0;
	}
}

// The Translator Function
#ifdef USE_SDL3
bool SDLCALL DispatchSDLToWndProc(void* userdata, SDL_Event* event)
#else
int SDLCALL DispatchSDLToWndProc(void* userdata, SDL_Event* event)
#endif
{
	UINT uMsg = 0;
	WPARAM wParam = 0;
	LPARAM lParam = 0;

	switch (event->type) {
#ifdef USE_SDL3
	// --- WINDOW EVENTS (SDL3) ---
	case SDL_EVENT_WINDOW_RESIZED:
	case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
		uMsg = WM_SIZE;
		lParam = MAKELPARAM(event->window.data1, event->window.data2);
		wParam = SIZE_RESTORED;
		break;
	case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
		uMsg = WM_CLOSE;
		break;
	case SDL_EVENT_WINDOW_FOCUS_GAINED:
		uMsg = WM_SETFOCUS;
		break;
	case SDL_EVENT_WINDOW_FOCUS_LOST:
		uMsg = WM_KILLFOCUS;
		break;
#else
	// --- WINDOW EVENTS (SDL2) ---
	case SDL_WINDOWEVENT:
		switch (event->window.event) {
		case SDL_WINDOWEVENT_RESIZED:
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			uMsg = WM_SIZE;
			lParam = MAKELPARAM(event->window.data1, event->window.data2);
			wParam = SIZE_RESTORED;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			uMsg = WM_CLOSE;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			uMsg = WM_SETFOCUS;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			uMsg = WM_KILLFOCUS;
			break;
		}
		break;
#endif

		// --- MOUSE MOVEMENT ---
#ifdef USE_SDL3
	case SDL_EVENT_MOUSE_MOTION:
#else
	case SDL_MOUSEMOTION:
#endif
		uMsg = WM_MOUSEMOVE;
		lParam = MAKELPARAM(event->motion.x, event->motion.y);
		if (event->motion.state & SDL_BUTTON_LMASK) {
			wParam |= MK_LBUTTON;
		}
		if (event->motion.state & SDL_BUTTON_RMASK) {
			wParam |= MK_RBUTTON;
		}
		if (event->motion.state & SDL_BUTTON_MMASK) {
			wParam |= MK_MBUTTON;
		}
		break;

		// --- MOUSE CLICKS ---
#ifdef USE_SDL3
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	case SDL_EVENT_MOUSE_BUTTON_UP:
#else
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
#endif
		lParam = MAKELPARAM(event->button.x, event->button.y);
		if (event->button.button == SDL_BUTTON_LEFT) {
#ifdef USE_SDL3
			uMsg = (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) ? WM_LBUTTONDOWN : WM_LBUTTONUP;
#else
			uMsg = (event->type == SDL_MOUSEBUTTONDOWN) ? WM_LBUTTONDOWN : WM_LBUTTONUP;
#endif
		} else if (event->button.button == SDL_BUTTON_RIGHT) {
#ifdef USE_SDL3
			uMsg = (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) ? WM_RBUTTONDOWN : WM_RBUTTONUP;
#else
			uMsg = (event->type == SDL_MOUSEBUTTONDOWN) ? WM_RBUTTONDOWN : WM_RBUTTONUP;
#endif
		} else if (event->button.button == SDL_BUTTON_MIDDLE) {
#ifdef USE_SDL3
			uMsg = (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) ? WM_MBUTTONDOWN : WM_MBUTTONUP;
#else
			uMsg = (event->type == SDL_MOUSEBUTTONDOWN) ? WM_MBUTTONDOWN : WM_MBUTTONUP;
#endif
		}
		break;

		// --- MOUSE WHEEL ---
#ifdef USE_SDL3
	case SDL_EVENT_MOUSE_WHEEL:
#else
	case SDL_MOUSEWHEEL:
#endif
		uMsg = WM_MOUSEWHEEL;
		wParam = MAKEWPARAM(0, event->wheel.y * WHEEL_DELTA);
		break;

		// --- KEYBOARD EVENTS ---
#ifdef USE_SDL3
	case SDL_EVENT_KEY_DOWN:
	case SDL_EVENT_KEY_UP:
		uMsg = (event->type == SDL_EVENT_KEY_DOWN) ? WM_KEYDOWN : WM_KEYUP;
		wParam = MapSDLKeyToVK(event->key.key);

		lParam = 1;
		lParam |= (event->key.scancode << 16);

		if (event->type == SDL_EVENT_KEY_UP) {
			lParam |= (1 << 31);
			lParam |= (1 << 30);
		} else if (event->key.repeat) {
			lParam |= (1 << 30);
		}
		break;
#else
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		uMsg = (event->type == SDL_KEYDOWN) ? WM_KEYDOWN : WM_KEYUP;
		wParam = MapSDLKeyToVK(event->key.keysym.sym);

		lParam = 1;
		lParam |= (event->key.keysym.scancode << 16);

		if (event->type == SDL_KEYUP) {
			lParam |= (1 << 31);
			lParam |= (1 << 30);
		} else if (event->key.repeat) {
			lParam |= (1 << 30);
		}
		break;
#endif

		// --- TEXT INPUT ---
#ifdef USE_SDL3
	case SDL_EVENT_TEXT_INPUT:
#else
	case SDL_TEXTINPUT:
#endif
		uMsg = WM_CHAR;
		wParam = (WPARAM)event->text.text[0];
		lParam = 1;
		break;

	default:
		return 0;
	}

	if (uMsg != 0) {
		return gpfWndProc(ghWnd, uMsg, wParam, lParam);
	}

	return 0;
}
// D2Gfx.0x6FA74450 (#10023)
int32_t __stdcall WINDOW_Create(int32_t bWindowed, D2GameResolutionMode nResolution) {
	if (FindWindowA("Diablo II", 0)) {
		MessageBoxA(nullptr, "Only one copy of Diablo II may run at a time.", "Diablo II Critical Error", MB_ICONEXCLAMATION);
		return 0;
	}

	D2_ASSERT(gpGraphicsInterface);

	gbIsWindowed = bWindowed;
	gnResolutionMode = nResolution;

	int32_t nWidth = 0;
	int32_t nHeight = 0;

	switch (nResolution) {
	case D2GAMERES_640x480:
		nWidth = 640;
		nHeight = 480;
		break;

	case D2GAMERES_800x600:
	case NUM_GAME_RESOLUTIONS:
		nWidth = 800;
		nHeight = 600;
		break;

	case D2GAMERES_1344x700:
		nWidth = 1344;
		nHeight = 700;
		break;

	default:
		static char szLocalBuffer[256];
		FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Unknown resolution %d", nResolution), __FILE__, __LINE__);
		exit(-1);
	}

	// dword_6FA8D740 = Rect.bottom;

	printf("Initializing SDL from WINDOW_Create\n");
	fflush(stdout);
	uint32_t sdlInitFlags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
	#ifdef USE_SDL3
	const bool sdlInitReturn = SDL_Init(sdlInitFlags);
	if (!sdlInitReturn) {
	#else
	const int sdlInitReturn = SDL_Init(sdlInitFlags);
	if (sdlInitReturn != 0) {
	#endif
		static char szLocalBuffer[256];
		FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Failed to initialize SDL!\nFlags: %u\nReturn code: %u\nSDL Error: %s\n", sdlInitFlags, sdlInitReturn, SDL_GetError()), __FILE__, __LINE__);
		exit(-1);
	}

	windowFlags = SDL_WINDOW_SHOWN;
	if (!bWindowed) {
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	}

	#ifdef USE_SDL3
	gpWindow = SDL_CreateWindow("Diablo II", nWidth, nHeight, windowFlags);
	#else
	gpWindow = SDL_CreateWindow("Diablo II", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, nWidth, nHeight, windowFlags);
	#endif
	if (gpWindow == NULL) {
		static char szLocalBuffer[256];
		FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Failed to open window!\nFlags: %u\nSDL Error: %s\n", windowFlags, SDL_GetError()), __FILE__, __LINE__);
		exit(-1);
	}

	// if (gbCursorDisplayed)
	// {
	//     while (ShowCursor(0) >= 0);
	//     gbCursorDisplayed = 0;
	// }
	HideCursor();

#ifdef USE_SDL3
#ifdef _WIN32
    // SDL3 uses properties to fetch platform handles cleanly without types
    ghWnd = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(gpWindow), SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
    if (ghWnd == NULL) {
        static char szLocalBuffer[256];
        FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Failed to get ghWnd from SDL3 (it's NULL)\n"), __FILE__, __LINE__);
        exit(-1);
    }
#else
    ghWnd = NULL;
#endif
#else
    // Legacy SDL2 path
	SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(gpWindow, &wmInfo);
#ifdef _WIN32
    ghWnd = wmInfo.info.win.window;
    if (ghWnd == NULL) {
        static char szLocalBuffer[256];
        FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Failed to get ghWnd from SDL (it's NULL)\n"), __FILE__, __LINE__);
        exit(-1);
    }
#else
    ghWnd = NULL;
#endif
#endif

	SDL_AddEventWatch(DispatchSDLToWndProc, NULL); // g_oldProc = (WNDPROC)SetWindowLongPtr(ghWnd, GWLP_WNDPROC, (LONG_PTR)gpfWndProc);

#ifndef D2_GLIDE_AS_SDLRENDERER
	BOOL createSurfaceSucceeded = gpGraphicsInterface->pfCreateSurface(ghWnd, gnResolutionMode);
#else
	BOOL createSurfaceSucceeded;
	if (gnDisplayType == DISPLAYTYPE_GLIDE) {
		createSurfaceSucceeded = gpGraphicsInterface->pfCreateSurface((HWND)(void*)gpWindow, gnResolutionMode);
	} else {
		createSurfaceSucceeded = gpGraphicsInterface->pfCreateSurface(ghWnd, gnResolutionMode);
	}
#endif

	if (createSurfaceSucceeded) {
		GdiSetBatchLimit(1u);
		D2GFX_SetContrastAndGamma_6FA710C0();
		return 1;
	}

	gbNoWindowCreated_6FA8D848 = 1;

	WINDOW_Destroy();

	return 0;
}

// D2Gfx.0x6FA74820 (#10024)
int32_t __stdcall WINDOW_Destroy() {
	D2_ASSERT(gpGraphicsInterface);

	ShowCursor();

	int32_t bWindowDestroyed = 1;
	if (!gpGraphicsInterface->pfCloseSurface()) {
		bWindowDestroyed = 0;
	}

	if (gpWindow != NULL) {
		SDL_DestroyWindow(gpWindow);
	}

	ChangeDisplaySettingsA(nullptr, 0);
	return bWindowDestroyed;
}

// D2Gfx.0x6FA748B0 (#10025)
void __stdcall WINDOW_SetPaused(int32_t bPaused) {
	gbPaused_6FA8D84C = bPaused;
}

// D2Gfx.0x6FA748C0 (#10026)
int32_t __stdcall WINDOW_GetState() {
	if (gbWindowState_6FA8D850 == gbPaused_6FA8D84C || !ghWnd) {
		return gbWindowState_6FA8D850;
	}

	D2_ASSERT(gpGraphicsInterface);

	int32_t bPaused = gbPaused_6FA8D84C;
	if (!gbPaused_6FA8D84C) {
		if (IsIconic(ghWnd)) {
			return gbWindowState_6FA8D850;
		}
		bPaused = gbPaused_6FA8D84C;
	}

	gbWindowState_6FA8D850 = bPaused;
	if (bPaused) {
		SDL_RaiseWindow(gpWindow);
		WINDOW_ShowAll();
		ShowCursor();
	} else {
		WINDOW_UpdatePlacement();
		HideCursor();
	}

#ifndef D2_GLIDE_AS_SDLRENDERER
	gpGraphicsInterface->pfPauseSurface(ghWnd, gnResolutionMode, gbWindowState_6FA8D850);
#else
	if (gnDisplayType == DISPLAYTYPE_GLIDE) {
		gpGraphicsInterface->pfPauseSurface((HWND)(void*)gpWindow, gnResolutionMode, gbWindowState_6FA8D850);
	} else {
		gpGraphicsInterface->pfPauseSurface(ghWnd, gnResolutionMode, gbWindowState_6FA8D850);
	}
#endif

	if (!gbWindowState_6FA8D850) {
		D2GFX_SetPalette(nullptr);
		D2GFX_SetContrastAndGamma_6FA710C0();
	}

	return gbWindowState_6FA8D850;
}

// D2Gfx.0x6FA749C0 (#10027)
HWND __stdcall WINDOW_GetWindow() {
	return ghWnd;
}

// D2Gfx.0x6FA749D0 (#10041)
int32_t __stdcall WINDOW_GetDimensions(int32_t* pWidth, int32_t* pHeight) {
	D2_ASSERT(gpGraphicsInterface);

	return gpGraphicsInterface->pfGetDimensions(pWidth, pHeight);
}

// D2Gfx.0x6FA74A10 (#10029)
void __stdcall WINDOW_ShowCursor(int32_t bShow) {
	if (!gbIsWindowed || gnDisplayType == DISPLAYTYPE_GLIDE || gnDisplayType == DISPLAYTYPE_OPENGL || gnDisplayType == DISPLAYTYPE_DIRECT3D) {
		return;
	}

	if (bShow) {
		ShowCursor();
	} else {
		HideCursor();
	}
}

// D2Gfx.0x6FA74A80 (#10028)
int32_t __stdcall WINDOW_IsFullScreen() {
	if (gpGraphicsInterface) {
		return gbIsWindowed == 0;
	}

	return 0;
}

// D2Gfx.0x6FA74AA0 (#10043)
int32_t __stdcall WINDOW_Activate(int32_t bActive) {
	D2_ASSERT(gpGraphicsInterface);

	gbIsWindowed = bActive == 0;
	return gpGraphicsInterface->pfActivateWindow();
}

// D2Gfx.0x6FA74AE0 (#10030)
int32_t __stdcall WINDOW_Resize(D2GameResolutionMode nResolution, int32_t bForceResize) {
	D2_ASSERT(gpGraphicsInterface);

	if (!bForceResize && nResolution == gnResolutionMode) {
		return 1;
	}

	gnResolutionMode = nResolution;

	int32_t nWidth = 0;
	int32_t nHeight = 0;

	if (gbIsWindowed == 1) {
		switch (nResolution) {
		case D2GAMERES_640x480:
			nWidth = 640;
			nHeight = 480;
			break;

		case D2GAMERES_800x600:
		case NUM_GAME_RESOLUTIONS:
			nWidth = 800;
			nHeight = 600;
			break;

		case D2GAMERES_1344x700:
			nWidth = 1344;
			nHeight = 700;
			break;

		default:
			static char szLocalBuffer[256];
			FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Unknown resolution %d", nResolution), __FILE__, __LINE__);
			exit(-1);
		}

		SDL_SetWindowSize(gpWindow, nWidth, nHeight);
	}

#ifndef D2_GLIDE_AS_SDLRENDERER
	const int32_t bResult = gpGraphicsInterface->pfChangeRes(ghWnd, nResolution);
#else
	int32_t bResult;
	if (gnDisplayType == DISPLAYTYPE_GLIDE) {
		bResult = gpGraphicsInterface->pfChangeRes((HWND)(void*)gpWindow, nResolution);
	} else {
		bResult = gpGraphicsInterface->pfChangeRes(ghWnd, nResolution);
	}
#endif
	D2GFX_SetContrastAndGamma_6FA710C0();
	return bResult;
}

// D2Gfx.0x6FA74C60 (#10031)
void __stdcall WINDOW_ClearCaches() {
	gpGraphicsInterface->pfClearCaches();
}

// D2Gfx.0x6FA74C70 (#10032)
void __stdcall WINDOW_PlayCutscene() {
	D2_ASSERT(gpGraphicsInterface);

	gpGraphicsInterface->pfPlayCutscene();
}

// D2Gfx.0x6FA74CA0 (#10033)
void __stdcall WINDOW_EndCutScene(D2GameResolutionMode nResolution) {
	D2_ASSERT(gpGraphicsInterface);

	if (gbWindowState_6FA8D850 != gbPaused_6FA8D84C && ghWnd && (gbPaused_6FA8D84C || !IsIconic(ghWnd))) {
		gbWindowState_6FA8D850 = gbPaused_6FA8D84C;
		if (gbPaused_6FA8D84C) {
			SDL_RaiseWindow(gpWindow);
			WINDOW_ShowAll();
			ShowCursor();
		} else {
			WINDOW_UpdatePlacement();
			HideCursor();
		}

#ifndef D2_GLIDE_AS_SDLRENDERER
		gpGraphicsInterface->pfPauseSurface(ghWnd, gnResolutionMode, gbWindowState_6FA8D850);
#else
		if (gnDisplayType == DISPLAYTYPE_GLIDE) {
			gpGraphicsInterface->pfPauseSurface((HWND)(void*)gpWindow, gnResolutionMode, gbWindowState_6FA8D850);
		} else {
			gpGraphicsInterface->pfPauseSurface(ghWnd, gnResolutionMode, gbWindowState_6FA8D850);
		}
#endif

		if (gbWindowState_6FA8D850) {
			gnResolutionMode = nResolution;
			D2GFX_SetPalette(nullptr);
			return;
		}

		D2GFX_SetPalette(nullptr);
		D2GFX_SetContrastAndGamma_6FA710C0();
	}

	if (gbWindowState_6FA8D850) {
		gnResolutionMode = nResolution;
	} else if (!WINDOW_Resize(nResolution, 1)) {
		FOG_Trace("Failed to resize window after cutscenes... this is fatal!");
		exit(-1);
	}

	D2GFX_SetPalette(nullptr);
}

// D2Gfx.0x6FA74DE0 (#10034)
void __stdcall WINDOW_OpenSmackCutscene(const char* szFile, D2GameResolutionMode nResolution, void(__cdecl* pfFrame)()) {
	D2_ASSERT(gpGraphicsInterface);

	return gpGraphicsInterface->pfOpenSmackCutscene(szFile, nResolution, (void*)pfFrame);
}

// D2Gfx.0x6FA74E20 (#10035)
int32_t __stdcall WINDOW_CheckCutScene() {
	D2_ASSERT(gpGraphicsInterface);

	return gpGraphicsInterface->pfCheckCutScene();
}

// D2Gfx.0x6FA74E50 (#10036)
void __stdcall WINDOW_DecodeSmacker(const char* szSmacker, uint8_t* pBuffer, int32_t nVersion) {
	D2_ASSERT(gpGraphicsInterface);

	return gpGraphicsInterface->pfDecodeSmacker(szSmacker, pBuffer, nVersion);
}

// D2Gfx.0x6FA74E90 (#10037)
void __stdcall WINDOW_PlaySmacker(void* pContext) {
	D2_ASSERT(gpGraphicsInterface);

	return gpGraphicsInterface->pfPlaySmacker(pContext);
}

// D2Gfx.0x6FA74ED0 (#10038)
void __stdcall WINDOW_CloseSmacker(void* pContext) {
	D2_ASSERT(gpGraphicsInterface);

	return gpGraphicsInterface->pfCloseSmacker(pContext);
}

// D2Gfx.0x6FA74F10 (#10039)
void __stdcall WINDOW_UpdatePlacement() {
	if (gbIsWindowed == 1) {
		return;
	}

	_AppBarData pData = {};
	pData.cbSize = sizeof(pData);
	pData.hWnd = ghWnd;

	for (int32_t i = 0; i < std::size(gWindowPlacement); ++i) {
		pData.uEdge = i;

		D2WindowPlacementStrc* pWindowPlacement = &gWindowPlacement[i];

		pWindowPlacement->hWnd = (HWND)SHAppBarMessage(7u, &pData);

		if (pWindowPlacement->hWnd) {
			pWindowPlacement->windowPlacement.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(pWindowPlacement->hWnd, &pWindowPlacement->windowPlacement);
			SDL_HideWindow(gpWindow);
		}
	}
}

// D2Gfx.0x6FA74FA0 (#10040)
void __stdcall WINDOW_ShowAll() {
	if (gbIsWindowed == 1) {
		return;
	}

	for (int32_t i = 0; i < std::size(gWindowPlacement); ++i) {
		D2WindowPlacementStrc* pWindowPlacement = &gWindowPlacement[i];

		if (pWindowPlacement->hWnd) {
			ShowWindow(pWindowPlacement->hWnd, pWindowPlacement->windowPlacement.showCmd);
		}
	}
}
