package com.purplesmaug96.Diablo2;

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {
    static {
        // Explicitly load SDL2 first
        System.loadLibrary("SDL2");
        
        // This is a native hook trick: By letting Android handle the load natively 
        // through the base context wrapper, it forces visibility flags to align.
        System.loadLibrary("Game");
    }

    @Override
    protected String getMainFunction() {
        // Explicitly defining this overrides the default fallback behaviors in some SDL versions
        return "SDL_main";
    }

    @Override
    protected String[] getLibraries() {
        return new String[] {
            "SDL2",
            "Game" // Tells Android to load libGame.so instead of libmain.so
        };
    }

    @Override
    protected String getMainSharedObject() {
        // This tells SDL which C++ library to load on startup
        return "libGame.so";
    }
}

