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
    char releasedThisFrame;
} typedef ActionBinding;

ActionBinding (*bindings)[0];
int bindingsCount = 0;

void initializeInputs()
{
    bindings = malloc(0);
}

int setBinding(char *name, char *defaultBindingString)
{
    bindingsCount++;
    bindings = realloc(bindings, bindingsCount*sizeof(ActionBinding));
    if(bindings == NULL)
    {
        printf("ERROR: Couldn't allocate memory for inputs");
        exit(1);
    }
    (*bindings)[bindingsCount-1].name = name;
    (*bindings)[bindingsCount-1].keys[0] = NULL;
    (*bindings)[bindingsCount-1].keys[1] = NULL;
    (*bindings)[bindingsCount-1].keys[2] = defaultBindingString;
    (*bindings)[bindingsCount-1].keys[3] = NULL;
    (*bindings)[bindingsCount-1].keys[4] = NULL;
    (*bindings)[bindingsCount-1].keys[5] = NULL;
}

int bindingPressed(int index);
int bindingPressedThisFrame(int index);
int bindingReleasedThisFrame(int index);

void inputZero()
{
    for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
    {
        (*bindings)[bindingIndex].pressedThisFrame = 0;
        (*bindings)[bindingIndex].releasedThisFrame = 0;
        for (int keyIndex = 0; keyIndex < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; keyIndex++)
        {
            (*bindings)[bindingIndex].keysPressedThisFrame[keyIndex] = 0;
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
                    if((*bindings)[bindingIndex].keys[keyIndex] != NULL)
                    {
                        if(!strcmp(SDL_GetKeyName(event.key.keysym.sym), (*bindings)[bindingIndex].keys[keyIndex]))
                        {
                            printf("A key pressed in binding %s\n", (*bindings)[bindingIndex].name);
                            (*bindings)[bindingIndex].keysPressed[keyIndex] = 1;
                            (*bindings)[bindingIndex].keysPressedThisFrame[keyIndex] = 1;
                        }
                    }   
                }
            }
            break;
        case SDL_KEYUP:
            printf("event keyup %s\n", SDL_GetKeyName(event.key.keysym.sym));
            for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
            {
                for (int keyIndex = 0; keyIndex < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; keyIndex++)
                {
                    if((*bindings)[bindingIndex].keys[keyIndex] != NULL)
                    {
                        if(!strcmp(SDL_GetKeyName(event.key.keysym.sym), (*bindings)[bindingIndex].keys[keyIndex]))
                        {
                            (*bindings)[bindingIndex].keysPressed[keyIndex] = 0;
                        }
                    }
                }
            }
            break;
    }
}

void inputCheck()
{
    for (int bindingIndex = 0; bindingIndex < bindingsCount; bindingIndex++)
    {
        if(!(*bindings)[bindingIndex].pressed) // check if was just pressed
        {
            for (int combinationIndex = 0; combinationIndex < MAX_COMBINATIONS_IN_BINDING; combinationIndex++)
            {
                int pressed = 1;
                for (int keyIndex = combinationIndex*MAX_KEYS_IN_COMBINATON; keyIndex < combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON; keyIndex++)
                {
                    pressed &= (*bindings)[bindingIndex].keysPressed[keyIndex];
                }
                pressed &= (*bindings)[bindingIndex].keysPressedThisFrame[combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON-1];

                if(pressed)
                {
                    (*bindings)[bindingIndex].pressed = 1;
                    (*bindings)[bindingIndex].pressedThisFrame = 1;
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
                    pressed &= (*bindings)[bindingIndex].keysPressed[keyIndex];
                }
                if(pressed)
                {
                    break;
                }
            }
            if(!pressed)
            {
                (*bindings)[bindingIndex].pressed = 0;
                (*bindings)[bindingIndex].releasedThisFrame = 1;
            }
        }
    }
}