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


// draws a rounded box with…
// corner radius of ‘r’
// width of ‘w’
// and height of ‘h’
// draws the box right and down of…
// x-offset xo
// y-offset yo

// returns 0 if 2*r is bigger than w or h
// and draws nothing
// returns 1 on success

int fill_rounded_box_b( SDL_Surface* dst, int xo, int yo, int w, int h, int r, Uint32 color )
{
  int yd = dst->pitch / dst->format->BytesPerPixel;
  Uint32* pixels = NULL;

  int x,y,i,j;
  int rpsqrt2 = (int) (r / sqrt( 2 ) );
  double r2 = r*r;

  w /= 2;
  h /= 2;

  xo += w;
  yo += h;

  w -= r;
  h -= r;

  if( w < 0 || h < 0 ){
  return 0;}

  SDL_LockSurface( dst );
  pixels = (Uint32*)( dst->pixels );

  int sy = (yo-h)*yd;
  int ey = (yo+h)*yd;
  int sx = (xo-w);
  int ex = (xo+w);
  for( i = sy; i<=ey; i+=yd ){
  for( j = sx-r; j<=ex+r; j++ ){
  pixels[i+j] = color;}}

  int d = -r;
  int x2m1 = -1;
  y = r;
  for( x=0; x <= rpsqrt2; x++ ) {
  x2m1 += 2;
  d+= x2m1;
  if( d >= 0 ) {
  y = y - 1;
  d -= (y*2);
  }

  for( i=sx-x; i<=ex+x; i++ )
    pixels[sy-y*yd + i] = color;

  for( i=sx-y; i<=ex+y; i++ )
    pixels[sy-x*yd + i] = color;

  for( i=sx-y; i<=ex+y; i++ )
    pixels[ey+x*yd + i] = color;

  for( i=sx-x; i<=ex+x; i++ )
    pixels[ey+y*yd + i] = color;
  }
  SDL_UnlockSurface( dst );
  return 1;
}


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
  fill_rounded_box_b(winSurface, 10, 70, 160, 320, 12, SDL_MapRGB(winSurface->format, 255, 100, 100));
  fill_rounded_box_b(winSurface, 180, 70, 530, 320, 12, SDL_MapRGB(winSurface->format, 255, 100, 100));

	// Wait
	/*system("sleep 4");*/

  SDL_Event test_event;
  short quit_ident;
  quit_ident = 1;
  
  //program loop
  while (quit_ident)
  {

    // Update the window display
    SDL_UpdateWindowSurface( window );

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
