
#include <SDL.h>
#include <cuda_runtime.h>
#include <cuda.h>

#include <thread>
#include <mutex>
#include "../inc/Defaults.hpp"
#include "../inc/Camera.hpp"
#include "../inc/World.hpp"
#include "../inc/DrawPixel.hpp"

namespace rt
{
	class WorldDrawer
	{
	public:
		WorldDrawer(				SDL_Window*			aWindow,
									SDL_Renderer*		aRenderer,
									SDL_Texture*		aTexture);

		void DrawPixel(				const rt::Color&	aColor, 
									const int&			aX, 
									const int&			aY);

		void DrawWorldParallel(
									const rt::Camera&	aCamera, 
									const rt::World&	aWorld, 
									uint32				aStart, 
									uint32				aEnd);

		void DrawWorld(				const rt::Camera&	aCamera,
									const rt::World&	aWorld);

	private: 
		std::mutex		myMutex;

		SDL_Window*		myWindow;
		SDL_Renderer*	myRenderer;
		SDL_Texture*	myTexture;

		std::vector<rt::DrawPixel> myDrawCanvas;
	};
}
