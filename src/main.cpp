/* 
 * File:   main.cpp
 * Author: carlos
 *
 * Created on 20 de junio de 2012, 01:27 AM
 */

#include <cstdlib>
#include <SDL.h>
#include <cairo/cairo.h>
#include <math.h>

using namespace std;

#define SPRITE1	"/home/carlos/Descargas/imagefactory.php3.bmp"
#define SPRITE2	"/home/carlos/Descargas/kyo.bmp"

int testCairo( SDL_Surface *screen )
{
	Uint32 color;

	SDL_Surface* sdlsurf = SDL_CreateRGBSurface(
												 SDL_SWSURFACE | SDL_RLEACCEL, screen->w, screen->h, 32,
												 0x00FF0000, /* Rmask */
												 0x0000FF00, /* Gmask */
												 0x000000FF, /* Bmask */
												 0 ); /* Amask */
	color = SDL_MapRGB( sdlsurf->format, 10, 255, 100 );

	SDL_FillRect( sdlsurf, NULL, color );

	if ( SDL_MUSTLOCK( sdlsurf ) )
	{
		SDL_LockSurface( sdlsurf );
	}

	cairo_surface_t *cairosurf = cairo_image_surface_create_for_data(
																	 (unsigned char*) ( sdlsurf->pixels ),
																	 CAIRO_FORMAT_RGB24,
																	 sdlsurf->w,
																	 sdlsurf->h,
																	 sdlsurf->pitch );

	cairo_t* cr = cairo_create( cairosurf );
	cairo_surface_destroy( cairosurf );
	//--------------------------------------------------------------------------------
	cairo_pattern_t *pat;

	pat = cairo_pattern_create_linear( 0.0, 0.0, 0.0, 256.0 );
	cairo_pattern_add_color_stop_rgba( pat, 1, 0, 0, 0, 1 );
	cairo_pattern_add_color_stop_rgba( pat, 0, 1, 1, 1, 1 );
	cairo_rectangle( cr, 0, 0, 256, 256 );
	cairo_set_source( cr, pat );
	cairo_fill( cr );
	cairo_pattern_destroy( pat );

	pat = cairo_pattern_create_radial( 115.2, 102.4, 25.6,
									   102.4, 102.4, 128.0 );
	cairo_pattern_add_color_stop_rgba( pat, 0, 1, 1, 1, 1 );
	cairo_pattern_add_color_stop_rgba( pat, 1, 0, 0, 0, 1 );
	cairo_set_source( cr, pat );
	cairo_arc( cr, 128.0, 128.0, 76.8, 0, 2 * M_PI );
	cairo_fill( cr );
	cairo_pattern_destroy( pat );

	//--------------------------------------------------------------------------------

	double xc = 128.0;
	double yc = 128.0;
	double radius = 100.0;
	double angle1 = 45.0 * ( M_PI / 180.0 ); /* angles are specified */
	double angle2 = 180.0 * ( M_PI / 180.0 ); /* in radians           */

	cairo_set_line_width( cr, 10.0 );
	cairo_arc( cr, xc, yc, radius, angle1, angle2 );
	cairo_stroke( cr );

	/* draw helping lines */
	cairo_set_source_rgba( cr, 1, 0.2, 0.2, 0.6 );
	cairo_set_line_width( cr, 6.0 );

	cairo_arc( cr, xc, yc, 10.0, 0, 2 * M_PI );
	cairo_fill( cr );

	cairo_arc( cr, xc, yc, radius, angle1, angle1 );
	cairo_line_to( cr, xc, yc );
	cairo_arc( cr, xc, yc, radius, angle2, angle2 );
	cairo_line_to( cr, xc, yc );
	cairo_stroke( cr );


	//--------------------------------------------------------------------------------
	cairo_destroy( cr );


	if ( SDL_MUSTLOCK( sdlsurf ) )
	{
		SDL_UnlockSurface( sdlsurf );
	}


	SDL_BlitSurface( sdlsurf, NULL, screen, NULL );

	SDL_free( sdlsurf );

	return 1;
}

/*
 * 
 */
int main( int argc, char** argv )
{
	SDL_Surface *screen;
	SDL_Surface* sprite;
	SDL_Rect dstRect;
	Uint32 orangeColor;
	SDL_Event event;
	bool running = true;


	if ( SDL_Init( SDL_INIT_AUDIO | SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Unable to init SDL: %s\n", SDL_GetError( ) );
		exit( 1 );
	}

	atexit( SDL_Quit );

	screen = SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF );

	if ( screen == NULL )
	{
		fprintf( stderr, "Unable to set 640x480 video: %s\n", SDL_GetError( ) );
		exit( 1 );
	}

	if ( SDL_MUSTLOCK( screen ) )
	{
		SDL_LockSurface( screen );
	}

	orangeColor = SDL_MapRGB( screen->format, 250, 190, 0 );

	SDL_FillRect( screen, NULL, orangeColor );


	// test cairo
	testCairo( screen );



	if ( SDL_MUSTLOCK( screen ) )
	{
		SDL_UnlockSurface( screen );
	}




	dstRect.x = 100;
	dstRect.y = 100;

	sprite = SDL_LoadBMP( SPRITE1 );

	if ( sprite == 0 )
	{
		fprintf( stderr, "Err %s\n",
				 SDL_GetError( ) );

		exit( 1 );
	}

	SDL_SetColorKey( sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB( sprite->format, 0, 255, 0 ) );
	printf( "Size %d,%d\n",
		 sprite->w,
		 sprite->h );
	SDL_BlitSurface( sprite, NULL, screen, &dstRect );
	SDL_free( sprite );


	dstRect.x = 200;
	dstRect.y = 100;


	sprite = SDL_LoadBMP( SPRITE2 );

	if ( sprite == 0 )
	{
		fprintf( stderr, "Err %s\n",
				 SDL_GetError( ) );

		exit( 1 );
	}

	SDL_SetColorKey( sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB( sprite->format, 255, 255, 255 ) );
	printf( "Size %d,%d\n",
		 sprite->w,
		 sprite->h );
	SDL_BlitSurface( sprite, NULL, screen, &dstRect );
	SDL_free( sprite );


	//SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip( screen );

	while (running)
	{
		while (SDL_PollEvent( &event ))
		{
			switch (event.type)
			{
				case SDL_MOUSEMOTION:
					printf( "Mouse moved by %d,%d to (%d,%d)\n",
						 event.motion.xrel, event.motion.yrel,
						 event.motion.x, event.motion.y );
					break;
				case SDL_MOUSEBUTTONDOWN:
					printf( "Mouse button %d pressed at (%d,%d)\n",
						 event.button.button, event.button.x, event.button.y );
					break;
				case SDL_QUIT:
					//exit( 0 );
					running = false;
					break;
			}
		}


	}



	return 0;
}

