#ifndef START_GAME_H_
#define START_GAME_H_

#include "Loop.hpp"

namespace Menu
{

class StartGame final : public Common::Loop
{

public:
	StartGame(void);
	~StartGame(void);

private:
	void handleEvent(const SDL_Event& event) noexcept override;
	void draw(void) noexcept override;

}; /*< class StartGame */

} /*< namespace Menu */

#endif /*< START_GAME_H_ */
