//
// Created by MyZiyue on 2019/10/25.
//

#ifndef ROCKETMQ_ONCE_CLIENT_PHP_PRODUCER_H
#define ROCKETMQ_ONCE_CLIENT_PHP_PRODUCER_H

#include "common.h"

class MQProducer : public Php::Base {
private:
    ons::ONSFactoryProperty factoryInfo;
    ons::Producer *pProducer = nullptr;
    ons::OrderProducer *pOrderProducer = nullptr;
    std::string messageKey = "";
    std::string messageTag = "";
    std::string shardingKey = "";
    long deliverTime = 0; // ms

    std::time_t getTimeStamp() {
        std::chrono::time_point <std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now());
        auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
        std::time_t timestamp = tmp.count();
        //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
        return timestamp;
    }
public:
    MQProducer() {}

    virtual ~MQProducer() {}

    void __construct() {}

    // group id
    Php::Value getGroupId();
    void setGroupId(Php::Parameters &param);

    // NameSrvAddr
    Php::Value getNameSrvAddr();
    void setNameSrvAddr(Php::Parameters &param);

    // topic
    Php::Value getTopic();
    void setTopic(Php::Parameters &param);

    // messageKey
    Php::Value getMessageKey();
    void setMessageKey(Php::Parameters &param);

    // messageTag
    Php::Value getMessageTag();
    void setMessageTag(Php::Parameters &param);

    // shardingKey
    Php::Value getShardingKey();
    void setShardingKey(Php::Parameters &param);

    // deliverTime
    void setDeliverTime(Php::Parameters &param);

    // set aliyun ONS-MQ accessKey and SecretKey
    void auth(Php::Parameters &param);

    // start client
    void start();

    // send message
    Php::Value send(Php::Parameters &param);
    Php::Value sendOneWay(Php::Parameters &param);
//    void sendAsync(Php::Parameters &param);

    // close
    void close();

    Php::Value getInstanceId();

    void __destruct() {
        if (this->pProducer != nullptr) {
            this->pProducer->shutdown();
            delete (this->pProducer);
        }
    }
};

void registerMQProducer(Php::Namespace &rocketMQNamespace);

#endif //ROCKETMQ_ONCE_CLIENT_PHP_PRODUCER_H
