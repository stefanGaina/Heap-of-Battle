#ifndef HOB_GOLD_HPP_
#define HOB_GOLD_HPP_

#include "hob_TextureInitializer.hpp"
#include "hob_SoundInitializer.hpp"
#include "hob_AsyncQueue.hpp"

namespace hob
{

/**
 * @brief
*/
class Gold final : public TextureInitializer<11ULL, 4ULL>
				 , public SoundInitializer<1ULL>
{
public:
	/**
	 * @brief
	 * @param amount:
	*/
	Gold(uint8_t amount) noexcept;

	/**
	 * @brief
	 * @param void
	 * @return void
	*/
	void draw(void) noexcept override;

	/**
	 * @brief
	 * @param amount:
	 * @return void
	*/
	void update(uint8_t amount) noexcept;

private:
	/**
	 * @brief
	*/
	AsyncQueue<uint8_t> m_queue;

	/**
	 * @brief
	*/
	uint8_t m_previousAmount;
};

} /*< namespace hob */

#endif /*< HOB_GOLD_HPP_ */
