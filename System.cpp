#include "System.h"

// private System data:
static SDL_Window* Window;
static SDL_GLContext Context;

void Initalize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
		printf("SDL initalization error:\n%s\n", SDL_GetError());
		throw - 1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	Window = SDL_CreateWindow(SYSTEM_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SYSTEM_WIDTH, SYSTEM_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (Window == NULL) {
		printf("SDL window creation error:\n%s\n", SDL_GetError());
		throw - 1;
	}
	Context = SDL_GL_CreateContext(Window);
	if (Context == NULL) {
		printf("SDL OpenGL context creation error:\n%s\n", SDL_GetError());
		throw - 1;
	}
	#ifdef _WIN32
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		puts("GLEW initalization error.");
		throw - 1;
	}
	#endif
}

void Free()
{
	SDL_GL_DeleteContext(Context);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

int System::execute(const char* file)
{
	// TODO: read file
	Initalize();
	SDL_Event event;
	const Uint8* Keyboard = SDL_GetKeyboardState(NULL);
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}
		if (Keyboard[SDL_SCANCODE_ESCAPE]) running = false;
		SDL_GL_SwapWindow(Window);
	}
	Free();
	return 0;
}
