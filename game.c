/**
 * @file game.c
 * @author Leo Dubosclard
 * @date March 09, 2020
 * @brief A simple game which is a Duck Hunt in C
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

int main( void )
{
    int duckWidth = 100, duckHeight = 100;
    const int max = 380, min = 0;
    int turn = 1, life = 3;
    SDL_Event event;

    SDL_Surface *screen = NULL, *background = NULL, *duck = NULL;
    SDL_Rect backgroundPosition, duckPosition;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("My Duck Hunt", NULL);

    background = IMG_Load("background.jpg");
    duck = IMG_Load("duck.png");

    backgroundPosition.x = 0;
    backgroundPosition.y = 0;
    
    while(turn) // main game loop
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                turn = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.x >= duckPosition.x && event.button.x <= duckPosition.x + duckWidth &&
                   event.button.y >= duckPosition.y && event.button.y <= duckPosition.y + duckHeight)
                {
                    srand(time(NULL));
                    duckPosition.x = 0;
                    duckPosition.y = (rand() %  (max - min + 1)) + min;
                }
                break;
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        SDL_BlitSurface(background, NULL, screen, &backgroundPosition);

        // duck moves
        duckPosition.x++;
        if(duckPosition.x >= 640)
        {
            life--;
            srand(time(NULL));
            duckPosition.x = 0;
            duckPosition.y = (rand() %  (max - min + 1)) + min;

        }
        if(life == 0)
        {
            turn = 0;
        }

        SDL_BlitSurface(duck, NULL, screen, &duckPosition);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(background);
    SDL_FreeSurface(duck);
    SDL_Quit();
    return 0;
}
