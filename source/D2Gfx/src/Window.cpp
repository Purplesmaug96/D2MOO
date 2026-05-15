#include "Window.h"
#include <SDL2/SDL_platform.h>

// Causes issue if not forced off
#define SDL_haptic_h_
#pragma warning(push)
#pragma warning( disable : 4820 )

#pragma pack(push, 1)

#include <algorithm>

#include <cstddef>
#include <shellapi.h>
#include <wingdi.h>

#include <Fog.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_hidapi.h>

#include "CmnSubtile.h"
#include "DisplayType.h"
#include "D2Gfx.h"

#pragma pack(pop, 1)

#pragma warning(pop)

extern DisplayType gnDisplayType;

HWND ghWnd;
int32_t gbIsWindowed;
D2GameResolutionMode gnResolutionMode;
//int32_t dword_6FA8D740;
D2WindowPlacementStrc gWindowPlacement[4];
int32_t gbCursorDisplayed;
int32_t gbNoWindowCreated_6FA8D848;
int32_t gbPaused_6FA8D84C;
int32_t gbWindowState_6FA8D850;
HINSTANCE ghInstance;

SDL_Window* window = NULL;
uint32_t windowFlags = 0;
SDL_SysWMinfo wmInfo;
WNDPROC g_oldProc;
extern WNDPROC gpfWndProc;

static void ShowCursor() {if (!gbCursorDisplayed) {SDL_ShowCursor(SDL_ENABLE); gbCursorDisplayed = 1;}}
static void HideCursor() {if (gbCursorDisplayed) {SDL_ShowCursor(SDL_DISABLE); gbCursorDisplayed = 0;}}

/* Translator is made by AI, but i just wanna get something working, will be replaced with a proper SDL_Event handler later */

// Helper function to map basic SDL keycodes to Win32 Virtual Keys (VK_*)
WPARAM MapSDLKeyToVK(SDL_Keycode key) {
    if (key >= SDLK_a && key <= SDLK_z) return key - SDLK_a + 'A';
    if (key >= SDLK_0 && key <= SDLK_9) return key;

    switch (key) {
        case SDLK_ESCAPE: return VK_ESCAPE;
        case SDLK_RETURN: return VK_RETURN;
        case SDLK_SPACE:  return VK_SPACE;
        case SDLK_BACKSPACE: return VK_BACK;
        case SDLK_TAB:    return VK_TAB;
        case SDLK_UP:     return VK_UP;
        case SDLK_DOWN:   return VK_DOWN;
        case SDLK_LEFT:   return VK_LEFT;
        case SDLK_RIGHT:  return VK_RIGHT;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT: return VK_SHIFT;
        case SDLK_LCTRL:
        case SDLK_RCTRL:  return VK_CONTROL;
        case SDLK_LALT:
        case SDLK_RALT:   return VK_MENU;
        // Add more specific mappings as needed
        default: return 0;
    }
}

// The Translator Function
int SDLCALL DispatchSDLToWndProc(void* userdata, SDL_Event* event) {
    UINT uMsg = 0;
    WPARAM wParam = 0;
    LPARAM lParam = 0;

    switch (event->type) {
        // --- WINDOW EVENTS ---
        case SDL_WINDOWEVENT:
            switch (event->window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    uMsg = WM_SIZE;
                    // Windows expects width and height in the low/high words of lParam
                    lParam = MAKELPARAM(event->window.data1, event->window.data2);
                    wParam = SIZE_RESTORED; // Simplified assumption
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

        // --- MOUSE MOVEMENT ---
        case SDL_MOUSEMOTION:
            uMsg = WM_MOUSEMOVE;
            lParam = MAKELPARAM(event->motion.x, event->motion.y);
            // Reconstruct the modifier state for wParam
            if (event->motion.state & SDL_BUTTON_LMASK) wParam |= MK_LBUTTON;
            if (event->motion.state & SDL_BUTTON_RMASK) wParam |= MK_RBUTTON;
            if (event->motion.state & SDL_BUTTON_MMASK) wParam |= MK_MBUTTON;
            break;

        // --- MOUSE CLICKS ---
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            lParam = MAKELPARAM(event->button.x, event->button.y);
            if (event->button.button == SDL_BUTTON_LEFT) {
                uMsg = (event->type == SDL_MOUSEBUTTONDOWN) ? WM_LBUTTONDOWN : WM_LBUTTONUP;
            } else if (event->button.button == SDL_BUTTON_RIGHT) {
                uMsg = (event->type == SDL_MOUSEBUTTONDOWN) ? WM_RBUTTONDOWN : WM_RBUTTONUP;
            } else if (event->button.button == SDL_BUTTON_MIDDLE) {
                uMsg = (event->type == SDL_MOUSEBUTTONDOWN) ? WM_MBUTTONDOWN : WM_MBUTTONUP;
            }
            break;

        // --- MOUSE WHEEL ---
        case SDL_MOUSEWHEEL:
            uMsg = WM_MOUSEWHEEL;
            // Win32 expects wheel delta in the high-order word of wParam.
            // SDL normalizes scrolling (often 1 or -1). Win32 uses WHEEL_DELTA (120).
            wParam = MAKEWPARAM(0, event->wheel.y * WHEEL_DELTA);
            // Note: Win32 lParam normally contains screen coordinates of the cursor here.
            // SDL doesn't package them in the wheel event, so we pass 0 unless you manually
            // track and inject the last known mouse position.
            break;

        // --- KEYBOARD EVENTS ---
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            uMsg = (event->type == SDL_KEYDOWN) ? WM_KEYDOWN : WM_KEYUP;
            wParam = MapSDLKeyToVK(event->key.keysym.sym);

            // Win32 packs a lot of data into the keyboard lParam (repeat count, scancode, flags)
            lParam = 1; // Repeat count (low 16 bits)
            lParam |= (event->key.keysym.scancode << 16); // Scan code

            if (event->type == SDL_KEYUP) {
                lParam |= (1 << 31); // Transition state flag (1 for keyup)
                lParam |= (1 << 30); // Previous key state flag (1 if key was down before)
            } else if (event->key.repeat) {
                lParam |= (1 << 30); // Previous state flag is 1 for repeated down events
            }
            break;

        // --- TEXT INPUT ---
        case SDL_TEXTINPUT:
            // SDL_TEXTINPUT roughly correlates to WM_CHAR, which is usually generated
            // by TranslateMessage() in a standard Win32 loop.
            uMsg = WM_CHAR;
            wParam = (WPARAM)event->text.text[0]; // Naive cast, works for basic ASCII
            lParam = 1; // Repeat count
            break;

        default:
            // Unhandled event types (controllers, touch, dragging)
            return 0;
    }

    // If we successfully translated to a Win32 message, dispatch it
    if (uMsg != 0) {
        return gpfWndProc(ghWnd, uMsg, wParam, lParam);
    }

    return 0;
}

//D2Gfx.0x6FA74450 (#10023)
int32_t __stdcall WINDOW_Create(int32_t bWindowed, D2GameResolutionMode nResolution)
{
    if (FindWindowA("Diablo II", 0))
    {
        MessageBoxA(nullptr, "Only one copy of Diablo II may run at a time.", "Diablo II Critical Error", MB_ICONEXCLAMATION);
        return 0;
    }

    D2_ASSERT(gpGraphicsInterface);

    gbIsWindowed = bWindowed;
    gnResolutionMode = nResolution;

    int32_t nWidth = 0;
    int32_t nHeight = 0;

    switch (nResolution)
    {
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

    //dword_6FA8D740 = Rect.bottom;

	printf("Initializing SDL from WINDOW_Create\n");
	fflush(stdout);
	uint32_t sdlInitFlags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
	const int sdlInitReturn = SDL_Init(sdlInitFlags);
	if (sdlInitReturn != 0)
	{
		static char szLocalBuffer[256];
		static char errBuf[256];
		FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Failed to initialize SDL!\nFlags: %u\nReturn code: %u\nSDL Error: %s\n", sdlInitFlags, sdlInitReturn, SDL_GetErrorMsg(errBuf, 256)), __FILE__, __LINE__);
		exit(-1);
	}

	windowFlags = SDL_WINDOW_SHOWN;
	if (!bWindowed) {
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow("Diablo II", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, nWidth, nHeight, windowFlags);
	if (window == NULL)
    {
        static char szLocalBuffer[256];
		static char errBuf[256];
		FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Failed to open window!\nFlags: %u\nSDL Error: %s\n", windowFlags, SDL_GetErrorMsg(errBuf, 256)), __FILE__, __LINE__);
		exit(-1);
    }

    // if (gbCursorDisplayed)
    // {
    //     while (ShowCursor(0) >= 0);
    //     gbCursorDisplayed = 0;
    // }
	HideCursor();

	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	#ifdef _WIN32
	ghWnd = wmInfo.info.win.window;
	#else
	ghWnd = NULL;
	#endif

	if (ghWnd == NULL)
	{
		static char szLocalBuffer[256];
		FOG_DisplayHalt(FOG_csprintf(szLocalBuffer, "Failed to get ghWnd from SDL (it's NULL)\n"), __FILE__, __LINE__);
		exit(-1);
	}

	SDL_AddEventWatch(DispatchSDLToWndProc, NULL); // g_oldProc = (WNDPROC)SetWindowLongPtr(ghWnd, GWLP_WNDPROC, (LONG_PTR)gpfWndProc);

	#ifndef D2_GLIDE_AS_SDLRENDERER
	BOOL createSurfaceSucceeded = gpGraphicsInterface->pfCreateSurface(ghWnd, gnResolutionMode);
	#else
	BOOL createSurfaceSucceeded;
	if (gnDisplayType == DISPLAYTYPE_GLIDE)
		createSurfaceSucceeded = gpGraphicsInterface->pfCreateSurface((HWND)(void*)window, gnResolutionMode);
	else
		createSurfaceSucceeded = gpGraphicsInterface->pfCreateSurface(ghWnd, gnResolutionMode);
	#endif

    if (createSurfaceSucceeded)
    {

		GdiSetBatchLimit(1u);
        D2GFX_SetContrastAndGamma_6FA710C0();
        return 1;
    }

    gbNoWindowCreated_6FA8D848 = 1;

    WINDOW_Destroy();

    return 0;
}

//D2Gfx.0x6FA74820 (#10024)
int32_t __stdcall WINDOW_Destroy()
{
    D2_ASSERT(gpGraphicsInterface);

    ShowCursor();

    int32_t bWindowDestroyed = 1;
    if (!gpGraphicsInterface->pfCloseSurface())
    {
        bWindowDestroyed = 0;
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    ChangeDisplaySettingsA(nullptr, 0);
    return bWindowDestroyed;
}

//D2Gfx.0x6FA748B0 (#10025)
void __stdcall WINDOW_SetPaused(int32_t bPaused)
{
    gbPaused_6FA8D84C = bPaused;
}

//D2Gfx.0x6FA748C0 (#10026)
int32_t __stdcall WINDOW_GetState()
{
    if (gbWindowState_6FA8D850 == gbPaused_6FA8D84C || !ghWnd)
    {
        return gbWindowState_6FA8D850;
    }

    D2_ASSERT(gpGraphicsInterface);

    int32_t bPaused = gbPaused_6FA8D84C;
    if (!gbPaused_6FA8D84C)
    {
        if (IsIconic(ghWnd))
        {
            return gbWindowState_6FA8D850;
        }
        bPaused = gbPaused_6FA8D84C;
    }

    gbWindowState_6FA8D850 = bPaused;
    if (bPaused)
    {
        SDL_RaiseWindow(window);
        WINDOW_ShowAll();
        ShowCursor();
    }
    else
    {
        WINDOW_UpdatePlacement();
        HideCursor();
    }

	#ifndef D2_GLIDE_AS_SDLRENDERER
	gpGraphicsInterface->pfPauseSurface(ghWnd, gnResolutionMode, gbWindowState_6FA8D850);
	#else
	if (gnDisplayType == DISPLAYTYPE_GLIDE)
		gpGraphicsInterface->pfPauseSurface((HWND)(void*)window, gnResolutionMode, gbWindowState_6FA8D850);
	else
		gpGraphicsInterface->pfPauseSurface(ghWnd, gnResolutionMode, gbWindowState_6FA8D850);
	#endif

    if (!gbWindowState_6FA8D850)
    {
        D2GFX_SetPalette(nullptr);
        D2GFX_SetContrastAndGamma_6FA710C0();
    }

    return gbWindowState_6FA8D850;
}

//D2Gfx.0x6FA749C0 (#10027)
HWND __stdcall WINDOW_GetWindow()
{
    return ghWnd;
}

//D2Gfx.0x6FA749D0 (#10041)
int32_t __stdcall WINDOW_GetDimensions(int32_t* pWidth, int32_t* pHeight)
{
    D2_ASSERT(gpGraphicsInterface);

    return gpGraphicsInterface->pfGetDimensions(pWidth, pHeight);
}

//D2Gfx.0x6FA74A10 (#10029)
void __stdcall WINDOW_ShowCursor(int32_t bShow)
{
    if (!gbIsWindowed || gnDisplayType == DISPLAYTYPE_GLIDE || gnDisplayType == DISPLAYTYPE_OPENGL || gnDisplayType == DISPLAYTYPE_DIRECT3D)
    {
        return;
    }

    if (bShow)
    {
        ShowCursor();
    }
	else
	{
		HideCursor();
	}
}

//D2Gfx.0x6FA74A80 (#10028)
int32_t __stdcall WINDOW_IsFullScreen()
{
    if (gpGraphicsInterface)
    {
        return gbIsWindowed == 0;
    }

    return 0;
}

//D2Gfx.0x6FA74AA0 (#10043)
int32_t __stdcall WINDOW_Activate(int32_t bActive)
{
    D2_ASSERT(gpGraphicsInterface);

    gbIsWindowed = bActive == 0;
    return gpGraphicsInterface->pfActivateWindow();
}

//D2Gfx.0x6FA74AE0 (#10030)
int32_t __stdcall WINDOW_Resize(D2GameResolutionMode nResolution, int32_t bForceResize)
{
    D2_ASSERT(gpGraphicsInterface);

    if (!bForceResize && nResolution == gnResolutionMode)
    {
        return 1;
    }

    gnResolutionMode = nResolution;

	int32_t nWidth = 0;
    int32_t nHeight = 0;

    if (gbIsWindowed == 1)
    {
		switch (nResolution)
		{
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

        SDL_SetWindowSize(window, nWidth, nHeight);
    }

	#ifndef D2_GLIDE_AS_SDLRENDERER
	const int32_t bResult = gpGraphicsInterface->pfChangeRes(ghWnd, nResolution);
	#else
	int32_t bResult;
	if (gnDisplayType == DISPLAYTYPE_GLIDE)
		bResult = gpGraphicsInterface->pfChangeRes((HWND)(void*)window, nResolution);
	else
		bResult = gpGraphicsInterface->pfChangeRes(ghWnd, nResolution);
	#endif
    D2GFX_SetContrastAndGamma_6FA710C0();
    return bResult;
}

//D2Gfx.0x6FA74C60 (#10031)
void __stdcall WINDOW_ClearCaches()
{
    gpGraphicsInterface->pfClearCaches();
}

//D2Gfx.0x6FA74C70 (#10032)
void __stdcall WINDOW_PlayCutscene()
{
    D2_ASSERT(gpGraphicsInterface);

    gpGraphicsInterface->pfPlayCutscene();
}

//D2Gfx.0x6FA74CA0 (#10033)
void __stdcall WINDOW_EndCutScene(D2GameResolutionMode nResolution)
{
    D2_ASSERT(gpGraphicsInterface);

    if (gbWindowState_6FA8D850 != gbPaused_6FA8D84C && ghWnd && (gbPaused_6FA8D84C || !IsIconic(ghWnd)))
    {
        gbWindowState_6FA8D850 = gbPaused_6FA8D84C;
        if (gbPaused_6FA8D84C)
        {
            SDL_RaiseWindow(window);
            WINDOW_ShowAll();
            ShowCursor();
        }
        else
        {
            WINDOW_UpdatePlacement();
            HideCursor();
        }

		#ifndef D2_GLIDE_AS_SDLRENDERER
		gpGraphicsInterface->pfPauseSurface(ghWnd, gnResolutionMode, gbWindowState_6FA8D850);
		#else
		if (gnDisplayType == DISPLAYTYPE_GLIDE)
			gpGraphicsInterface->pfPauseSurface((HWND)(void*)window, gnResolutionMode, gbWindowState_6FA8D850);
		else
			gpGraphicsInterface->pfPauseSurface(ghWnd, gnResolutionMode, gbWindowState_6FA8D850);
		#endif

        if (gbWindowState_6FA8D850)
        {
            gnResolutionMode = nResolution;
            D2GFX_SetPalette(nullptr);
            return;
        }

        D2GFX_SetPalette(nullptr);
        D2GFX_SetContrastAndGamma_6FA710C0();
    }

    if (gbWindowState_6FA8D850)
    {
        gnResolutionMode = nResolution;
    }
    else if (!WINDOW_Resize(nResolution, 1))
    {
        FOG_Trace("Failed to resize window after cutscenes... this is fatal!");
        exit(-1);
    }

    D2GFX_SetPalette(nullptr);
}

//D2Gfx.0x6FA74DE0 (#10034)
void __stdcall WINDOW_OpenSmackCutscene(const char* szFile, D2GameResolutionMode nResolution, void(__cdecl* pfFrame)())
{
    D2_ASSERT(gpGraphicsInterface);

    return gpGraphicsInterface->pfOpenSmackCutscene(szFile, nResolution, (void*)pfFrame);
}

//D2Gfx.0x6FA74E20 (#10035)
int32_t __stdcall WINDOW_CheckCutScene()
{
    D2_ASSERT(gpGraphicsInterface);

    return gpGraphicsInterface->pfCheckCutScene();
}

//D2Gfx.0x6FA74E50 (#10036)
void __stdcall WINDOW_DecodeSmacker(const char* szSmacker, uint8_t* pBuffer, int32_t nVersion)
{
    D2_ASSERT(gpGraphicsInterface);

    return gpGraphicsInterface->pfDecodeSmacker(szSmacker, pBuffer, nVersion);
}

//D2Gfx.0x6FA74E90 (#10037)
void __stdcall WINDOW_PlaySmacker(void* pContext)
{
    D2_ASSERT(gpGraphicsInterface);

    return gpGraphicsInterface->pfPlaySmacker(pContext);
}

//D2Gfx.0x6FA74ED0 (#10038)
void __stdcall WINDOW_CloseSmacker(void* pContext)
{
    D2_ASSERT(gpGraphicsInterface);

    return gpGraphicsInterface->pfCloseSmacker(pContext);
}

//D2Gfx.0x6FA74F10 (#10039)
void __stdcall WINDOW_UpdatePlacement()
{
    if (gbIsWindowed == 1)
    {
        return;
    }

    _AppBarData pData = {};
    pData.cbSize = sizeof(pData);
    pData.hWnd = ghWnd;

    for (int32_t i = 0; i < std::size(gWindowPlacement); ++i)
    {
        pData.uEdge = i;

        D2WindowPlacementStrc* pWindowPlacement = &gWindowPlacement[i];

        pWindowPlacement->hWnd = (HWND)SHAppBarMessage(7u, &pData);

        if (pWindowPlacement->hWnd)
        {
            pWindowPlacement->windowPlacement.length = sizeof(WINDOWPLACEMENT);
            GetWindowPlacement(pWindowPlacement->hWnd, &pWindowPlacement->windowPlacement);
            SDL_HideWindow(window);
        }
    }
}

//D2Gfx.0x6FA74FA0 (#10040)
void __stdcall WINDOW_ShowAll()
{
    if (gbIsWindowed == 1)
    {
        return;
    }

    for (int32_t i = 0; i < std::size(gWindowPlacement); ++i)
    {
        D2WindowPlacementStrc* pWindowPlacement = &gWindowPlacement[i];

        if (pWindowPlacement->hWnd)
        {
            ShowWindow(pWindowPlacement->hWnd, pWindowPlacement->windowPlacement.showCmd);
        }
    }
}
