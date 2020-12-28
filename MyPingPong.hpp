#pragma once
#include "engine/alice/alice_codelet.hpp" // ядро isaac sdk
#include "messages/ping.capnp.h" // нужен для PingProto

namespace isaac {
class MyPingPong: public isaac::alice::Codelet {
public:
    // Запускается при старте компонента
    void start() override;
    // В зависимости от реализации start(): запускается многократно, либо с заданным периодом, либо в блокирующем режиме, либо по событию приема нового сообщения.
    void tick() override;
    // Запускается по завершению работы компонента
    void stop() override;

    // Коммуникация с другими компонентами
    ISAAC_PROTO_TX(PingProto, ping);
    ISAAC_PROTO_RX(PingProto, pong);

    //ISAAC_POSE2(ping, pong);
    ISAAC_POSE3(ping, pong)
    
    // Параметры запуска компонента
    // (тип , название, значение по умолчанию)
  	ISAAC_PARAM(bool, wait_ping, true);
    ISAAC_PARAM(std::string, message, "Текст сообщения");
};
}
ISAAC_ALICE_REGISTER_CODELET(isaac::MyPingPong);