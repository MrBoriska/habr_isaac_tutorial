#include "MyPingPong.hpp"

#include "engine/core/logger.hpp"

namespace isaac {

void MyPingPong::start() {

  if (get_wait_ping()) {
    LOG_INFO("Запуск в режиме Pong");
    // Запускать tick() по событию приема нового сообщения (rx_pong)
    tickOnMessage(rx_pong());
  } else {
    LOG_INFO("Запуск в режиме Ping");
    // Запускать tick() с периодом, определенным в унаследованном параметре tick_period
    tickPeriodically();
  }
}

void MyPingPong::tick() {
  
  if (!get_wait_ping()) {
    // Получение значения параметра message
    std::string msg = get_message();
    // Инициализация нового сообщения
    PingProto::Builder ping_proto = tx_ping().initProto();
    // Заполнение его данными
    ping_proto.setMessage(msg);
    // Отправка
    tx_ping().publish();
  } else {
    // Получение Proto обьекта входящего сообщения из канала pong
    PingProto::Reader pong_proto = rx_pong().getProto();
    // чтение из Proto обьекта
    const std::string pong_msg = pong_proto.getMessage();
    // расчет времени между отправкой и приемом сообщения
    int64_t latency_ns = this->getTickTimestamp()-rx_pong().pubtime();
    
    // Sight
    show("latency", latency_ns);

    // PoseTree
    //double x=1,y=2,angle=3.14;
    //const Pose2d ping_T_pong{SO2d::FromAngle(angle), Vector2d{x, y}};
    //set_ping_T_pong(ping_T_pong, getTickTime());

    double x=1,y=2,z=3,angle=3.14;
    Vector3d z_axis{0.0, 0.0, 1.0};
    const Pose3d ping_T_pong{SO3d::FromAxisAngle(z_axis, angle),
                             Vector3d{x, y, z}};
    set_ping_T_pong(ping_T_pong, getTickTime());
    
    LOG_INFO("%s by %d ns", pong_msg.c_str(), latency_ns);
  }
}

void MyPingPong::stop() {
  LOG_WARNING("Завершение работы компонента");
}

}  // namespace isaac