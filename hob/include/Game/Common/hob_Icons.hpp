#ifndef HOB_ICONS_HPP_
#define HOB_ICONS_HPP_

#include "hob_TextureInitializer.hpp"

namespace hob
{

class Icons final : public TextureInitializer<14L, 5L>
{
public:

	Icons(void) noexcept;

	~Icons(void) = default;

	void hide(void) noexcept;

	void setAllianceKeep(void) noexcept;
};

} /*< namespace hob */

#endif /*< HOB_ICONS_HPP_ */
