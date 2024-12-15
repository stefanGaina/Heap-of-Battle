#ifndef HOB_ENGINE_APPLICATION_HPP_
#define HOB_ENGINE_APPLICATION_HPP_

#include <string>
#include <memory>

namespace hob::engine
{

class application_impl;

class application final
{
public:
	application(std::string_view configuration_file) noexcept(false);

	~application(void) noexcept;

	void run(void) noexcept(false);

private:
	std::unique_ptr<application_impl> implementation;
};

} /*< namespace hob::engine */

#endif /*< HOB_ENGINE_APPLICATION_HPP_ */
