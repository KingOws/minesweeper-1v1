#pragma once
#include <vector>
#include "SFML/Network.hpp"

template <typename T>
class pactor : public std::vector<T>{
    public:
        friend sf::Packet& operator<<(sf::Packet& packet, pactor& p){
            uint32_t size = p.size();
            packet << size;
            for(typename pactor<T>::iterator it = p.begin(); it != p.end(); it++){
                packet << *it;
            }
            return packet;
        }

        friend sf::Packet& operator>>(sf::Packet& packet, pactor& p){
            uint32_t size;
            if(!(packet >> size)) return packet;
            p.resize(size);
            for(typename pactor<T>::iterator it = p.begin(); it != p.end(); it++)
                packet >> *it;
            return packet;
        }

        friend std::ostream& operator<<(std::ostream& os, pactor& p){
            for(typename pactor<T>::iterator it = p.begin(); it != p.end(); it++){
                os << *it;
            }
            return os;
        }

    private:
};


template<>
class pactor<uint32_t> : public std::vector<uint32_t>{
    public:
        friend sf::Packet& operator<<(sf::Packet& packet, pactor& p){
            packet << static_cast<uint32_t>(p.size());
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

        friend std::ostream& operator<<(std::ostream& os, pactor& p){
            os << "Size is: ";
            os << p.size();
            os << std::endl;
            for(auto it = p.begin(); it != p.end(); it++)
                os << *it << " ";
            os << std::endl;
            return os;
        }
};
