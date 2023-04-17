#include <memory>
#include <plog.h>

#include "Map1.hpp"
#include "Cursor.hpp"
#include "Socket.hpp"
#include "Faction.hpp"

namespace Game
{

Map1::Map1(void)
	: Loop            {}
	, chat            {}
	, tiles           {}
	, grid            {}
	, timer           {}
	, receivingThread { std::bind(&Map1::receivingFunction, this) }
	, receivingUpdates{ true }
{
	Timer::Callback callback = nullptr;

	plog_trace("Map1 is being constructed.");
	Utility::Cursor::getInstance().setFaction(Faction::getFaction());
	Utility::Cursor::getInstance().setTexture(Utility::CursorType::IDLE);

	if (true == Faction::getFaction())
	{
		try
		{
			callback = std::make_shared<Utility::Socket::CallbackFunction>(std::bind(&Map1::onTimesUp, this));
		}
		catch (std::bad_alloc& exception)
		{
			plog_error("Unable to allocate memory for callback! (exception message: %s)", exception.what());
		}
		timer.start(30U, callback);
	}
}

Map1::~Map1(void)
{
	plog_trace("Map1 is being destructed.");

	receivingUpdates = false;
	Utility::Socket::getInstance().clean();
	if (true == receivingThread.joinable())
	{
		plog_trace("Receiving updates thread is joining.");
		receivingThread.join();
	}

	Utility::Cursor::getInstance().setFaction(true);
	Utility::Cursor::getInstance().setTexture(Utility::CursorType::IDLE);
}

void Map1::draw(void) noexcept
{
	plog_verbose("Map1 is being drawn.");
	menu.draw();
	chat.draw();
	tiles.draw();
	m_buildings.draw();
	grid.draw();
	timer.draw();
}

void Map1::receivingFunction(void) noexcept
{
	Utility::Message receivedMessage = {};
	Timer::Callback  callback        = nullptr;

	while (true == receivingUpdates)
	{
		Utility::Socket::getInstance().receiveUpdates(receivedMessage);
		switch (receivedMessage.type)
		{
			case Utility::MessageType::TEXT:
			{
				plog_trace("Text message received!");
				chat.receivedMessage(receivedMessage.payload.text);
				break;
			}
			case Utility::MessageType::TIME:
			{
				plog_verbose("Time update message received!");
				timer.updateEnemyTime(receivedMessage.payload.timeLeft);
				break;
			}
			case Utility::MessageType::END_TURN:
			{
				plog_info("Opponent turn ended!");
				try
				{
					callback = std::make_shared<Utility::Socket::CallbackFunction>(std::bind(&Map1::onTimesUp, this));
				}
				catch (std::bad_alloc& exception)
				{
					plog_error("Unable to allocate memory for callback! (exception message: %s)", exception.what());
				}
				timer.start(30U, callback);
				break;
			}
			case Utility::MessageType::END_COMMUNICATION:
			{
				plog_info("End communication message received!");
				receivingUpdates = false;
				stopLoop(Scene::MAIN_MENU);
				break;
			}
			case Utility::MessageType::VERSION:
			{
				plog_error("Version message type received! (opponent version: %s)", receivedMessage.payload.version);
				break;
			}
			default:
			{
				plog_error("Invalid message type! (message type: %" PRId32 ")", static_cast<int32_t>(receivedMessage.type));
				break;
			}
		}
	}
}

void Map1::onTimesUp(void) noexcept
{
	Utility::Message message = {};

	message.type = Utility::MessageType::END_TURN;
	Utility::Socket::getInstance().sendUpdate(message);
}

void Map1::handleEvent(const SDL_Event& event) noexcept
{
	Coordinate       click      = {};
	Utility::Message message    = {};
	uint32_t         mouseState = 0UL;
	size_t           index      = 0ULL;

	plog_verbose("Event is being handled.");
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_trace("Mouse (%" PRIu32 ") was clicked. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			if (LEFT_CLICK != SDL_BUTTON(mouseState))
			{
				plog_trace("Mouse click is not left click.");
				return;
			}

			chat.handleClick(click);
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_trace("Mouse (%" PRIu32 ") was released. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_verbose("Mouse (%" PRIu32 ") was moved. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			Utility::Cursor::getInstance().updatePosition(click);

			if (LEFT_CLICK == SDL_BUTTON(mouseState))
			{
				plog_verbose("Mouse left click is pressed.");
				return;
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			chat.handleButtonPress(event);

			// TODO: remove this
			switch (event.key.keysym.sym)
			{
				case SDLK_a:
				{
					tiles.changeTexture(Season::SUMMER);
					m_buildings.changeWeather(false);
					break;
				}
				case SDLK_s:
				{
					tiles.changeTexture(Season::AUTUMN);
					m_buildings.changeWeather(false);
					break;
				}
				case SDLK_d:
				{
					tiles.changeTexture(Season::WINTER);
					m_buildings.changeWeather(true);
					break;
				}
				case SDLK_f:
				{
					tiles.changeTexture(Season::SPRING);
					m_buildings.changeWeather(false);
					break;
				}
			}
			break;
		}
		case SDL_WINDOWEVENT:
		{
			if (SDL_WINDOWEVENT_FOCUS_LOST == event.window.event)
			{
				plog_debug("Window lost focus.");
				click.x = -1L;
				click.y = -1L;
				Utility::Cursor::getInstance().updatePosition(click);
			}
			break;
		}
		case SDL_QUIT:
		{
			plog_info("Command to quit game was given!");

			message.type = Utility::MessageType::END_COMMUNICATION;
			Utility::Socket::getInstance().sendUpdate(message);

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

} /*< namespace Game */
