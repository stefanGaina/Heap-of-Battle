#ifndef HOB_APITESTER_DETAILS_ARGUMENT_HPP_
#define HOB_APITESTER_DETAILS_ARGUMENT_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <format>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace hob::apitester::details
{

/**
 * @brief 
 */
class argument
{
public:
	/**
	 * @brief Construct a new argument object
	 */
	argument(void) noexcept;

	/**
	 * @brief Construct a new argument object
	 * 
	 * @param text 
	 */
	argument(const std::string& text) noexcept(false);

	argument(std::string&& text) noexcept;

	/**
	 * @brief 
	 * @param other 
	 * @return argument& 
	 */
	argument& operator=(const argument& other) noexcept(false);

	[[nodiscard]] bool operator==(const argument& other) const noexcept;

	[[nodiscard]] bool operator==(const std::string& string) const noexcept;

	[[nodiscard]] bool operator==(const char* string) const noexcept;

	/** ***********************************************************************************************
	 * @brief Cast from text to boolean byte.
	 * @param void
	 * @returns The argument as bool.
	 * @throws std::invalid_argument: If the string does not evaluate to "true" or "false".
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator bool(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 1 byte signed integer byte.
	 * @param void
	 * @returns The argument as std::int8_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the int8_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator std::int8_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 1 byte unsigned integer byte.
	 * @param void
	 * @returns The argument as uint8_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the uint8_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator std::uint8_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 2 byte signed integer byte.
	 * @param void
	 * @returns The argument as std::int16_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the int16_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator std::int16_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 2 byte unsigned integer byte.
	 * @param void
	 * @returns The argument as std::uint16_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the uint16_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator std::uint16_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 4 byte signed integer byte.
	 * @param void
	 * @returns The argument as std::int32_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the int32_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator std::int32_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 4 byte unsigned integer byte.
	 * @param void
	 * @returns The argument as std::uint32_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the uint32_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator std::uint32_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 8 byte signed integer byte.
	 * @param void
	 * @returns The argument as std::int64_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the int64_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator std::int64_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 8 byte unsigned integer byte.
	 * @param void
	 * @returns The argument as std::uint64_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the uint64_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator std::uint64_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 4 byte floating point number.
	 * @param void
	 * @returns The argument as float.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the float range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator float(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 8 byte floating point number.
	 * @param void
	 * @returns The argument as double.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the double range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator double(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast to address of the buffer.
	 * @param void
	 * @returns The argument as const char* (should not be nullptr).
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] operator const char*(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Cast to get the argument in the string form.
	 * @param void
	 * @returns The argument as std::string (should not be empty).
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] operator const std::string&(void) const noexcept;

	[[nodiscard]] operator std::string_view(void) const noexcept;

	[[nodiscard]] operator FILE*(void) const noexcept(false);

	friend bool operator==(const std::string& string, const argument& argument) noexcept;
	friend bool operator==(const char* string, const argument& argument) noexcept;

	friend std::ostream& operator<<(std::ostream& ostream, const argument& argument) noexcept(false);

protected:
	/** ***********************************************************************************************
	 * @brief The text form of the argument before it is being casted to desired data types.
	 *************************************************************************************************/
	std::string text;

private:
	[[nodiscard]] std::int64_t get_signed_integer(std::int64_t minimum, std::int64_t maximum) const noexcept(false);

	[[nodiscard]] std::uint64_t get_unsigned_integer(std::uint64_t maximum) const noexcept(false);

	[[nodiscard]] float get_float(void) const noexcept(false);

	/**
	 * @brief Get the Double object
	 * @returns
	 * @throws
	 */
	[[nodiscard]] double get_double(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Checks if the text has been converted fully or it has ignored characters at the end.
	 * @param position: Index of the last character in the text that was converted.
	 * @returns void
	 * @throws std::invalid_argument: If the text has trailing characters after string conversion.
	 *************************************************************************************************/
	void throw_if_trailing_characters(std::size_t position) const noexcept(false);
};

} /*< namespace hob::apitester::details */

namespace std
{

/** ***************************************************************************************************
 * @brief This class allows hob::apitester::details::argument to be formatted so it can be a parameter to
 * std::print and similar functions.
 *****************************************************************************************************/
template<>
class formatter<hob::apitester::details::argument> : public formatter<string>
{
public:
	/** ***********************************************************************************************
	 * @brief Formats an argument object to be able to be printed using std::print() and similar
	 * functions.
	 * @param argument: The argument object to be formatted.
	 * @param context: Provides access to formatting state consisting of the formatting arguments and
	 * the output iterator.
	 * @returns Unkown data type.
	 * @throws std::bad_alloc: If formatting the string fails.
	 *************************************************************************************************/
	auto format(hob::apitester::details::argument argument, format_context& context) const noexcept(false)
	{
		return formatter<string>::format(std::format("{}", static_cast<const string&>(argument)), context);
	}
};

} /*< namespace std */

#endif /*< HOB_APITESTER_DETAILS_ARGUMENT_HPP_ */
