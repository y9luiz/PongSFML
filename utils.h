#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include "defs.h"
std::vector<std::string> splitString( std::string  text,char delimiter)
{
	std::vector<std::string> words{};
	size_t pos;
	std::cout << text << "\n";
	int start = 0;
	int end;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		end = pos;
		words.push_back(text.substr(start, end));
		start = end;
		text = text.substr(start+1, text.length());
		start = 0;
	}
	words.push_back(text);
	return words;
}

std::string sfVectorToStdString(const sf::Vector2f & v)
{
	std::string x = std::to_string(int(v.x));
	std::string y = std::to_string(int(v.y));
	return x + separator + y;
}
sf::Vector2f stdStringTosfVector(const std::string & s)
{
	auto fields = splitString(s, separator);

	assert(fields.size() == 2);
	return sf::Vector2f(atoi(fields[0].data()), atoi(fields[1].data()));
}