#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

template <typename T>
class pactor : public std::vector<T>{
    public:
        friend sf::packet& operator<<(sf::packet& packet, pactor& p){
            int size = p.size();
            packet << size;
            for(typename pactor<T>::iterator it = pactor.begin(); it != pactor.end(); it++){
                packet << *it;
            }
            return packet;
        }

        friend sf::packet& operator>>(sf::packet& packet, pactor& p){
            int size;
            if(!(packet >> size)) return packet;
            p.resize(size);
            for(typename pactor<T>::iterator it = pactor.begin(); it != pactor.end(); it++)
                packet >> *it;
            return packet;
        }

    private:
};