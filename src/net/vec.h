#pragma once
#include "SFML/Network.hpp"
#include "SFML/System/Vector2.hpp"

// Pack: sf::Vector2f into Packet
inline sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& v) {
    return packet << v.x << v.y;
}

// Unpack: Packet into sf::Vector2f
inline sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v) {
    return packet >> v.x >> v.y;
}

inline sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2i& v) {
    return packet << v.x << v.y;
}

// Unpack: Packet into sf::Vector2i
inline sf::Packet& operator >>(sf::Packet& packet, sf::Vector2i& v) {
    return packet >> v.x >> v.y;
}
