#include <SDL2/SDL_log.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <iostream>
#include <SDL2/SDL.h>

// You shouldn't really use this statement, but it's fine for small programs
using namespace std;

void quit_SDL(SDL_Window* win)
{
  // Destroy the window. This will also destroy the surface
	SDL_DestroyWindow( win );
	
	// Quit SDL
	SDL_Quit();

}

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {

	// Pointers to our window and surface
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;

	// Initialize SDL. SDL_Init will return -1 if it fails.
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		// End the program
		return 1;
	} 

	// Create our window
	window = SDL_CreateWindow( "Neko's Amazing SDL2 Window!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 400, SDL_WINDOW_SHOWN );

	// Make sure creating the window succeeded
	if ( !window ) {
		cout << "Error creating window: " << SDL_GetError()  << endl;
		// End the program
		return 1;
	}

	// Get the surface from the window
	winSurface = SDL_GetWindowSurface( window );

	// Make sure getting the surface succeeded
	if ( !winSurface ) {
		cout << "Error getting surface: " << SDL_GetError() << endl;
		// End the program
		return 1;
	}

	// Fill the window with a white rectangle
	SDL_FillRect( winSurface, NULL, SDL_MapRGB( winSurface->format, 255, 235, 235 ) );

  SDL_Rect header;
  header.x = 0; header.y = 0; header.w = 720; header.h = 60;
  SDL_FillRect(winSurface, &header, SDL_MapRGB(winSurface->format, 255, 200, 200));

	// Update the window display
	SDL_UpdateWindowSurface( window );

	// Wait
	/*system("sleep 4");*/

  SDL_Event test_event;
  short quit_ident;
  quit_ident = 1;
  
  //program loop
  while (quit_ident)
  {
    SDL_PollEvent(&test_event);
    switch (test_event.type)
    {
      case SDL_MOUSEMOTION:
        SDL_Log("Caught a mouse event.");
        SDL_Log("Pos: (%d, %d)", test_event.motion.x, test_event.motion.y);
        break;

      case SDL_QUIT:
        quit_SDL(window);
        quit_ident = 0;
        break;

      default:
        break;
    }
  }

	// End the program
	return 0;
}
