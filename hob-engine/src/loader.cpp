/******************************************************************************************************
 * Copyright (C) 2024 Gaina Stefan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file loader.cpp
 * @author Gaina Stefan
 * @date 18.12.2024
 * @brief This file implements the class defined in loader.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <logger.hpp>

#include "loader.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace hob::engine
{

sf::Texture
loader::load_texture(const std::string& file_path, const std::int32_t x, const std::int32_t y, const std::int32_t width, const std::int32_t height) noexcept(false)
{
	sf::Texture texture = {};

	hob_log_default_trace("Texture is being loaded. (path: \"{}\") (x: \'{}\') (y: \'{}\') (width: \'{}\') (height: \'{}\')", file_path, x, y, width, height);
	return true == texture.loadFromFile(file_path, { x, y, width, height })
			   ? texture
			   : throw std::runtime_error{ std::format("Failed to load texture! (file path: \"{}\")", file_path) };
}

sf::Font loader::load_font(const std::string& file_path) noexcept(false)
{
	sf::Font font = {};

	hob_log_default_trace("Font is being loaded. (path: \"{}\")", file_path);
	return true == font.loadFromFile(file_path) ? font : throw std::runtime_error{ std::format("Failed to load font! (file path: \"{}\")", file_path) };
}

std::shared_ptr<sf::Sprite> loader::load_sprite(
	const std::vector<sf::Texture>& textures,
	const std::size_t				texture_index,
	const float						x,
	const float						y,
	const float						width,
	const float						height) noexcept(false)
{
	const std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
	const sf::Texture&				  texture =
		   texture_index < textures.size()
						   ? textures[texture_index]
						   : throw std::out_of_range{ std::format("Texture index is out of range! (size: \'{}\') (index: \'{}\')", textures.size(), texture_index) };

	hob_log_default_trace("Sprite is being loaded. (index: \'{}\') (x: \'{}\') (y: \'{}\') (width: \'{}\'), (height: \'{}\')", texture_index, x, y, width, height);

	sprite->setTexture(texture);
	sprite->setPosition(x, y);
	sprite->setScale(width / texture.getSize().x, height / texture.getSize().y);

	return sprite;
}

std::shared_ptr<sf::Text> loader::load_text(
	const std::vector<sf::Font>& fonts,
	const std::size_t			 font_index,
	const std::string&			 string,
	const sf::Color&			 color,
	const sf::Vector2f&			 position,
	const std::uint32_t			 character_size) noexcept(false)
{
	const std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>();

	hob_log_default_trace("Text is being loaded. (string: \"{}\")", string);

	text->setFont(font_index < fonts.size()
					  ? fonts[font_index]
					  : throw std::out_of_range{ std::format("Fonts index is out of range! (size: \'{}\') (index: \'{}\')", fonts.size(), font_index) });
	text->setString(string);
	text->setFillColor(color);
	text->setPosition(position);
	text->setCharacterSize(character_size);

	return text;
}

void loader::load_music(sf::Music& music, const std::string& file_path) noexcept(false)
{
	hob_log_default_trace("Music is being loaded. (path: \"{}\")", file_path);

	if (false == music.openFromFile(file_path))
	{
		throw std::runtime_error{ std::format("Failed to load music! (file path: \"{}\")", file_path) };
	}

	music.setLoop(true);
}

sf::SoundBuffer loader::load_sound_buffer(const std::string& file_path) noexcept(false)
{
	sf::SoundBuffer sound_buffer = {};

	hob_log_default_trace("Sound buffer is being loaded. (path: \"{}\")", file_path);
	return true == sound_buffer.loadFromFile(file_path)
			   ? sound_buffer
			   : throw std::runtime_error{ std::format("Failed to load sound buffer! (file path: \"{}\")", file_path) };
}

sf::Sound loader::load_sound(const std::vector<sf::SoundBuffer>& sound_buffers, const std::size_t buffer_index) noexcept(false)
{
	sf::Sound sound = {};

	hob_log_default_trace("Sound is being loaded. (index: \'{}\')", buffer_index);

	sound.setBuffer(
		buffer_index < sound_buffers.size()
			? sound_buffers[buffer_index]
			: throw std::out_of_range{ std::format("Sound buffer index is out of range! (size: \'{}\') (index: \'{}\')", sound_buffers.size(), buffer_index) });
	return sound;
}

} /*< namespace hob::engine */
