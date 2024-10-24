#include <SDL2/SDL.h>
#include <string.h>

#define MAX_KEYS_IN_COMBINATON 3
#define MAX_COMBINATIONS_IN_BINDING 2

struct ActionBinding
{
	char* name; // used for settings menu and saving
	SDL_Keycode keys[MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING];
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

int bindAction(char *name, char *defaultBindingString)
{
    bindingsCount++;
    bindings = realloc(bindings, bindingsCount*sizeof(ActionBinding));
    if(bindings == NULL)
    {
        printf("ERROR: Couldn't allocate memory for inputs");
        exit(1);
    }

    (*bindings)[bindingsCount-1].name = name;


    int defaultBindingStringIndex = 0;
    for (int combinationIndex = 0; combinationIndex < MAX_COMBINATIONS_IN_BINDING; combinationIndex++)
    {
        int keysInCombination = 0;

        //get key codes
        for (int keyIndex = combinationIndex*MAX_KEYS_IN_COMBINATON; keyIndex < combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON; keyIndex++)
        {
            char keyName[1024];
            memset(keyName, '\0', 1024);
            int keyNameIndex = 0;
            int escaping = 0;
            while (defaultBindingString[defaultBindingStringIndex] != '\0')
            {
                if(
                    (
                        defaultBindingString[defaultBindingStringIndex] == ';'
                        || defaultBindingString[defaultBindingStringIndex] ==  '+'
                    )
                    && !escaping
                )
                {
                    break;
                }
                if(defaultBindingString[defaultBindingStringIndex] == '\\' && !escaping)
                {
                    escaping = 1;
                    defaultBindingStringIndex++;
                    continue;
                }

                keyName[keyNameIndex] = defaultBindingString[defaultBindingStringIndex];
                keyNameIndex++;
                defaultBindingStringIndex++;
            }
            
            SDL_KeyCode keyCode = SDL_GetKeyFromName(keyName);
            (*bindings)[bindingsCount-1].keys[keyIndex] = keyCode;
            if(keyCode != SDLK_UNKNOWN)
            {
                keysInCombination++;
            }

            if(defaultBindingString[defaultBindingStringIndex] == ';' || defaultBindingString[defaultBindingStringIndex] == '\0')
            {
                break;
            }
            else
            {
                defaultBindingStringIndex++;
            }
        }

        //move SDLK_UNKNOWNs to start
        int shift = MAX_KEYS_IN_COMBINATON - keysInCombination;
        if(keysInCombination > 0 && shift > 0)
        {
            for(int keyIndex = MAX_KEYS_IN_COMBINATON*combinationIndex + MAX_KEYS_IN_COMBINATON-1; keyIndex > MAX_KEYS_IN_COMBINATON*combinationIndex + shift-1; keyIndex--)
            {
                (*bindings)[bindingsCount-1].keys[keyIndex] = (*bindings)[bindingsCount-1].keys[keyIndex-shift];
            }
            for(int keyIndex = MAX_KEYS_IN_COMBINATON*combinationIndex; keyIndex < MAX_KEYS_IN_COMBINATON*combinationIndex + shift; keyIndex++)
            {
                (*bindings)[bindingsCount-1].keys[keyIndex] = SDLK_UNKNOWN;
            }
        }

        //clear pressed state
        for (int i = 0; i < MAX_KEYS_IN_COMBINATON * MAX_COMBINATIONS_IN_BINDING; i++)
        {
            (*bindings)[bindingsCount-1].keysPressed[i] = 0;
            (*bindings)[bindingsCount-1].keysPressedThisFrame[i] = 0;
        }
        (*bindings)[bindingsCount-1].pressed = 0;
        (*bindings)[bindingsCount-1].pressedThisFrame = 0;
        (*bindings)[bindingsCount-1].releasedThisFrame = 0;

        for (int keyIndex = combinationIndex*MAX_KEYS_IN_COMBINATON; keyIndex < combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON; keyIndex++)
        {
            printf("Binding %s Key %i: %i - %s\n", name, keyIndex, (*bindings)[bindingsCount-1].keys[keyIndex], SDL_GetKeyName((*bindings)[bindingsCount-1].keys[keyIndex]));
        }

        if(defaultBindingString[defaultBindingStringIndex] == '\0')
        {
            break;
        }
        else
        {
            defaultBindingStringIndex++;
        }
    }

    return bindingsCount - 1;
}

int actionPressed(int index)
{
    return (*bindings)[index].pressed;
}

int actionPressedThisFrame(int index)
{
    return (*bindings)[index].pressedThisFrame;
}

int actionReleasedThisFrame(int index)
{
    return (*bindings)[index].releasedThisFrame;
}

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
                    if((*bindings)[bindingIndex].keys[keyIndex] != SDLK_UNKNOWN)
                    {
                        if(event.key.keysym.sym == (*bindings)[bindingIndex].keys[keyIndex])
                        {
                            // We only want to set this if they key isn't already pressed beacause letter keys that write a symbol repeat
                            (*bindings)[bindingIndex].keysPressedThisFrame[keyIndex] = !(*bindings)[bindingIndex].keysPressed[keyIndex];
                            (*bindings)[bindingIndex].keysPressed[keyIndex] = 1;
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
                    if((*bindings)[bindingIndex].keys[keyIndex] != SDLK_UNKNOWN)
                    {
                        if(event.key.keysym.sym == (*bindings)[bindingIndex].keys[keyIndex])
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
                    pressed &= (*bindings)[bindingIndex].keys[keyIndex] == SDLK_UNKNOWN || (*bindings)[bindingIndex].keysPressed[keyIndex];
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
                // If last key in combination is SDLK_UNKNOWN it is unbound
                if((*bindings)[bindingIndex].keys[combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON-1] == SDLK_UNKNOWN)
                {
                    pressed = 0;
                }
                else
                {
                    for (int keyIndex = combinationIndex*MAX_KEYS_IN_COMBINATON; keyIndex < combinationIndex*MAX_KEYS_IN_COMBINATON+MAX_KEYS_IN_COMBINATON; keyIndex++)
                    {
                        pressed &= 
                        (*bindings)[bindingIndex].keys[keyIndex] == SDLK_UNKNOWN
                        || (*bindings)[bindingIndex].keysPressed[keyIndex];
                    }
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