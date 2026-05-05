#pragma once
#include <vector>
#include "SFML/Network.hpp"

template <typename T>
class pactor : public std::vector<T>{
    public:
        friend sf::Packet& operator<<(sf::Packet& packet, pactor& p){
            int size = p.size();
            packet << size;
            for(typename pactor<T>::iterator it = p.begin(); it != p.end(); it++){
                packet << *it;
            }
            return packet;
        }

        friend sf::Packet& operator>>(sf::Packet& packet, pactor& p){
            int size;
            if(!(packet >> size)) return packet;
            p.resize(size);
            for(typename pactor<T>::iterator it = p.begin(); it != p.end(); it++)
                packet >> *it;
            return packet;
        }

    private:
};