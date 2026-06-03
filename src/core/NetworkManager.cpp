#include <NetworkManager.h>
#include <memory>
#include <string>

const int DISCOVERY_PORT = 54000;
const int HOSTING_PORT = 55000;


NetworkManager::NetworkManager() {

}

void NetworkManager::startServer() {
  mode = NetMode::SERVER;

  listener.listen(HOSTING_PORT);
  listener.setBlocking(false);

  udp.bind(DISCOVERY_PORT);
  udp.setBlocking(false);

  selector.add(listener);

}

void NetworkManager::startClient() {
  mode = NetMode::CLIENT;

  udp.bind(DISCOVERY_PORT);
  udp.setBlocking(false);

}

void NetworkManager::discoveryPing() {
  std::string msg = "MINESWEEPER CLIENT";
  udp.send(msg.c_str(), msg.size(), sf::IpAddress::Broadcast, DISCOVERY_PORT);
}



void NetworkManager::update(NetworkInfo& networkInfo) {
  if (mode == NetMode::CLIENT) updateClient(networkInfo);
  else if (mode == NetMode::SERVER) updateServer(networkInfo);
}

void NetworkManager::updateServer(NetworkInfo& networkInfo) {
  if (broadcastClock.getElapsedTime().asSeconds() >1.f) {
    discoveryPing();
    broadcastClock.restart();
  }

  auto client = std::make_unique<sf::TcpSocket>();
  if (listener.accept(*client) == sf::Socket::Status::Done) {
    client->setBlocking(false);
    selector.add(*client);
    client->send(&networkInfo, sizeof(NetworkInfo));
    clients.push_back(std::move(client));
  }
  for (auto& client : clients) {
    size_t received;
    NetworkInfo info;
    if (client->receive(&info, sizeof(NetworkInfo), received) == sf::Socket::Status::Done) {
    // client sent a click, info.x and info.y are the cell they clicked
    }
  }
}

void NetworkManager::updateClient(NetworkInfo& networkInfo) {
  if (!socket.getRemoteAddress().has_value()) {
    char buff[32];
    size_t received;

    unsigned short ignored;

    udp.receive(buff, sizeof(buff), received, serverIp, ignored);

    if (serverIp.has_value()) {
      socket.connect(serverIp.value(), HOSTING_PORT);
    } 
  } else {
    size_t received;

    socket.receive(&networkInfo, sizeof(NetworkInfo), received);
  }
}
