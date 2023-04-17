#include <memory>
#include <functional>
#include <plog.h>

#include "Multiplayer.hpp"
#include "Cursor.hpp"
#include "Faction.hpp"

namespace Menu
{

Multiplayer::Multiplayer(void) noexcept
	: Loop    {}
	, callback{ nullptr }
{
	plog_trace("Multiplayer is being constructed.");
}

Multiplayer::~Multiplayer(void) noexcept
{
	plog_trace("Multiplayer is being deconstructed.");
}

void Multiplayer::connectionDoneCallback(void) noexcept
{
	std::lock_guard<std::mutex> lock(callbackMutex);
	stopLoop(Scene::GAME);
}

void Multiplayer::draw(void) noexcept
{
	plog_verbose("Multiplayer is being drawn.");
}

void Multiplayer::handleEvent(const SDL_Event& event) noexcept
{
	Coordinate       click      = {};
	uint32_t         mouseState = 0UL;
	Utility::Socket& socket     = Utility::Socket::getInstance();

	plog_verbose("Events is being handled.");
	switch (event.type)
	{
		case SDL_KEYDOWN:
		{
			if (SDLK_a == event.key.keysym.sym)
			{
				try
				{
					callback = std::make_shared<Utility::Socket::CallbackFunction>(std::bind(&Multiplayer::connectionDoneCallback, this));
				}
				catch (std::bad_alloc& exception)
				{
					plog_error("Unable to allocate memory for callback! (exception message: %s)", exception.what());
					return;
				}

				socket.createServer(callback);
				Game::Faction::setFaction(true);
			}
			else if (SDLK_b == event.key.keysym.sym)
			{
				if (true == socket.createClient("127.0.0.1"))
				{
					Game::Faction::setFaction(false);
					std::lock_guard<std::mutex> lock(callbackMutex);
					stopLoop(Scene::GAME);
					return;
				}
			}
			break;
		}
		case SDL_MOUSEMOTION:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_verbose("Mouse (%" PRIu32 ") was moved. (%" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			Utility::Cursor::getInstance().updatePosition(click);
			break;
		}
		case SDL_QUIT:
		{
			plog_info("Command to quit game was given!");
			socket.clean();

			std::lock_guard<std::mutex> lock(callbackMutex);
			stopLoop(Scene::QUIT);
			break;
		}
		default:
		{
			plog_verbose("Event received but not handled.");
			break;
		}
	}
}

} /*< namespace Menu */
