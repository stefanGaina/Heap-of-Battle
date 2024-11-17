#ifndef HOB_ENGINE_APPLICATION_HPP_
#define HOB_ENGINE_APPLICATION_HPP_

#include <string>

namespace hob::engine
{

class application
{
public:
	application(std::string_view configuration_file) noexcept(false);

	void run(void) noexcept(false);
};

} /*< namespace hob::engine */

#endif /*< HOB_ENGINE_APPLICATION_HPP_ */
