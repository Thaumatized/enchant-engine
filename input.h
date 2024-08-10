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

void inputUpdate();