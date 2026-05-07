#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class Game;

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

        pactor<int>& operator=(const std::vector<std::unique_ptr<Game>>& vec);

        ~pactor(){}
        pactor(){}

    private:
};

// Full specialization for int
template <>
class pactor<int> : public std::vector<int>{
    public:
        friend sf::Packet& operator<<(sf::Packet& packet, pactor& p){
            int size = p.size();
            packet << size;
            for(auto it = p.begin(); it != p.end(); it++)
                packet << *it;
            return packet;
        }

        friend sf::Packet& operator>>(sf::Packet& packet, pactor& p){
            int size;
            if(!(packet >> size)) return packet;
            p.resize(size);
            for(auto it = p.begin(); it != p.end(); it++)
                packet >> *it;
            return packet;
        }

        ~pactor(){}
        pactor(){}
};