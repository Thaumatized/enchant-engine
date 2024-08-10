#include <SDL2/SDL.h>

#define MAX_KEYS_IN_COMBINATON 3
#define MAX_COMBINATIONS_IN_BINDING 2

struct ActionBinding
{
	char* name; // Important for settings menu and saving
	char* keys[MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING];
    char keysPressed[MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING];
    char keysPressedThisFrame[MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING];
    char pressed;
    char pressedThisFrame;
} typedef ActionBinding;

ActionBinding *bindings[] = {
    {"testbind1", {"A", NULL, NULL, NULL, NULL, NULL}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, 0, 0}
};
int bindingsCount;

void inputUpdate()
{
    for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
    {
        bindings[bindingIndex]->pressedThisFrame = 0;
        for (int keyIndex = 0; keyIndex < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; keyIndex++)
        {
            bindings[bindingIndex]->keysPressedThisFrame[keyIndex] = 0;
        }
    }

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				closeGame();
				break;
			case SDL_KEYDOWN:
                for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
                {
                    for (int keyIndex = 0; keyIndex < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; keyIndex++)
                    {
                        if(!strcmp(SDL_GetKeyName(event.key.keysym.sym), bindings[bindingIndex]->keys[keyIndex]))
                        {
                            bindings[bindingIndex]->keysPressed[keyIndex] = 1;
                            bindings[bindingIndex]->keysPressedThisFrame[keyIndex] = 1;
                        }
                    }
                }
				break;
			case SDL_KEYUP:
                for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
                {
                    for (int keyIndex = 0; keyIndex < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; keyIndex++)
                    {
                        if(!strcmp(SDL_GetKeyName(event.key.keysym.sym), bindings[bindingIndex]->keys[keyIndex]))
                        {
                            bindings[bindingIndex]->keysPressed[keyIndex] = 0;
                        }
                    }
                }
				break;
		}
	}

    for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
    {
        if(!bindings[bindingIndex]->pressed) // check if pressed
        {
            for (int combinationIndex = 0; combinationIndex < MAX_COMBINATIONS_IN_BINDING; combinationIndex++)
            {
                int pressed = 1;
                for (int keyIndex = combinationIndex*MAX_KEYS_IN_COMBINATON; keyIndex < MAX_KEYS_IN_COMBINATON; keyIndex++)
                {
                    pressed &= bindings[bindingIndex]->keysPressed[keyIndex];
                }
                pressed &= bindings[bindingIndex]->keysPressedThisFrame[combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON-1];
                if(pressed)
                {
                    bindings[bindingIndex]->pressed = 1;
                    bindings[bindingIndex]->pressedThisFrame = 1;
                }
            }
        }
        else // check if released
        {
            int pressed = 1;
            for (int combinationIndex = 0; combinationIndex < MAX_COMBINATIONS_IN_BINDING; combinationIndex++)
            {
                pressed = 1;
                for (int keyIndex = combinationIndex*MAX_KEYS_IN_COMBINATON; keyIndex < MAX_KEYS_IN_COMBINATON; keyIndex++)
                {
                    pressed &= bindings[bindingIndex]->keysPressed[keyIndex];
                }
                if(pressed)
                {
                    break;
                }
            }
            if(!pressed)
            {
                bindings[bindingIndex]->pressed = 0;
            }
        }
    }
}