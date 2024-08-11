#include <SDL2/SDL.h>
#include <string.h>

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

ActionBinding *bindings[1];
int bindingsCount = 1;

void inputInitialize()
{ 
    printf("Initializing Input\n");
    ActionBinding binding;
    memset(&binding, 0, sizeof(ActionBinding));
    binding.name = "testbind1";
    binding.keys[0] = "A";
    binding.keys[3] = "B";
    bindings[0] = &binding;
}

void inputZero()
{
    for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
    {
        bindings[bindingIndex]->pressedThisFrame = 0;
        for (int keyIndex = 0; keyIndex < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; keyIndex++)
        {
            bindings[bindingIndex]->keysPressedThisFrame[keyIndex] = 0;
        }
    }
}

void inputEvent(SDL_Event event)
{
    switch (event.type) {
        case SDL_KEYDOWN:
            printf("event keydown %s\n", SDL_GetKeyName(event.key.keysym.sym));
            for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
            {
                for (int keyIndex = 0; keyIndex < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; keyIndex++)
                {
                    if(!strcmp(SDL_GetKeyName(event.key.keysym.sym), bindings[bindingIndex]->keys[keyIndex]))
                    {
                        //bindings[bindingIndex]->keysPressed[keyIndex] = 1;
                        //bindings[bindingIndex]->keysPressedThisFrame[keyIndex] = 1;
                    }
                }
            }
            break;
        case SDL_KEYUP:
            printf("event keyup %s\n", SDL_GetKeyName(event.key.keysym.sym));
            /*for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
            {
                for (int keyIndex = 0; keyIndex < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; keyIndex++)
                {
                    if(!strcmp(SDL_GetKeyName(event.key.keysym.sym), bindings[bindingIndex]->keys[keyIndex]))
                    {
                        bindings[bindingIndex]->keysPressed[keyIndex] = 0;
                    }
                }
            }*/
            break;
    }
}

void inputCheck()
{

    /*
    for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
    {
        if(!bindings[bindingIndex]->pressed) // check if was just pressed
        {
            for (int combinationIndex = 0; combinationIndex < MAX_COMBINATIONS_IN_BINDING; combinationIndex++)
            {
                int pressed = 1;
                for (int keyIndex = combinationIndex*MAX_KEYS_IN_COMBINATON; keyIndex < combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON; keyIndex++)
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
        else // check if was just released
        {
            int pressed = 1;
            for (int combinationIndex = 0; combinationIndex < MAX_COMBINATIONS_IN_BINDING; combinationIndex++)
            {
                pressed = 1;
                for (int keyIndex = combinationIndex*MAX_KEYS_IN_COMBINATON; keyIndex < combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON; keyIndex++)
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
    */
}