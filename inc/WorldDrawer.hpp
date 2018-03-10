
#include <SDL.h>

#include <thread>
#include <mutex>
#include "../inc/Defaults.hpp"
#include "../inc/Camera.hpp"
#include "../inc/World.hpp"

namespace rt
{
	class WorldDrawer
	{
	public:
		WorldDrawer(				SDL_Window*			aWindow,
									SDL_Renderer*		aRenderer);

		void DrawPixel(				const rt::Color&	aColor, 
									const int&			aX, 
									const int&			aY);

		void DrawWorldParallel(		const rt::Camera&	aCamera,
									const rt::World&	aWorld,
									const uint32&		aStart,
									const uint32&		aEnd);

		void DrawWorld(				const rt::Camera&	aCamera, 
									const rt::World&	aWorld);

	private: 
		std::mutex		myMutex;

		SDL_Window*		myWindow;
		SDL_Renderer*	myRenderer;

	};
}
