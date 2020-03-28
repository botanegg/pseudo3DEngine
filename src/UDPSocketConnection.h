#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <utility>
#include "World.h"
#include "Camera.h"

class UDPSocketConnection {
private:
    World& W_world;
    Camera& C_camera;
    sf::UdpSocket socket;

    std::map<short unsigned, size_t> clientPortToCameraOid;

    std::map<short unsigned, Camera> m_cameras;
    std::string s_ipAdress;
    short unsigned i_myPort;

    std::vector<Point2D> v_spawns = {{1.5, 1.5}, {1.5, 9}};
public:
    UDPSocketConnection(World& world, Camera& camera) : W_world(world), C_camera(camera) {}

    void bind(std::string ip, short unsigned port) {
        s_ipAdress = std::move(ip);
        socket.bind(port);
        socket.setBlocking(false);
        i_myPort = port;
        //C_camera.setName(std::to_string(port));
    }

    void update() {
        double x = 0;
        double y = 0;
        int health = 100;
        size_t killedId = std::numeric_limits<size_t>::max();

        sf::Packet packet;
        sf::IpAddress sender;
        short unsigned int senderPort = 0;
        short unsigned int port = 0;

        bool ack1 = false;
        bool ack2 = false;


        while((socket.receive(packet, sender, port) == sf::Socket::Status::Done) && (port >= 54000) && (port <= 54010)) {
            sf::Uint64 killedIdTransport; //using fixed size type for networking
            packet >> x >> y >> killedIdTransport >> ack2 >> health;
            killedId = killedIdTransport;
            senderPort = port;
        }
        while((socket.receive(packet, sender, port) == sf::Socket::Status::Done)) {};

        if(ack2)
            C_camera.cleanLastKillId();

        if(killedId == C_camera.getId()) {
            C_camera.setPosition(v_spawns[i_myPort % v_spawns.size()]);
            C_camera.fullHealth();
            ack1 = true;
        }

        if (auto it = clientPortToCameraOid.find(senderPort); it != clientPortToCameraOid.end()) {
            // client was bound before
            m_cameras.at(senderPort).setPosition({ x, y });
            C_camera.setHealth(health);
            m_cameras.at(senderPort).reduceHealth(-0.1);
        } else if ((senderPort >= 54000) && (senderPort <= 54010)) {
            Camera camera(W_world, { 2.5, 0 });
            m_cameras.insert({ senderPort, camera });
            size_t assignedId = W_world.addObject2D(m_cameras.at(senderPort));
            m_cameras.at(senderPort).setId(assignedId);
        }

        for(int i = 54000; i < 54010; i++) {
            sf::Packet packetSend;
            int h = m_cameras.count(i) != 0 ? m_cameras.at(i).health() : 100;
            sf::Uint64 killedIdTransport = C_camera.getLastKillId(); //using fixed size for networking
            packetSend << C_camera.x() << C_camera.y() << killedIdTransport << ack1 << h;
            if (i != i_myPort)
                socket.send(packetSend, s_ipAdress, i);
        }
    }
};
