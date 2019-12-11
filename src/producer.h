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
    std::string messageKey = "";

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

    // logger
    Php::Value getLogPath();

    Php::Value getInstanceId();

    void __destruct() {
        if (this->pProducer != nullptr) {
            this->pProducer->shutdown();
            delete (this->pProducer);
        }
    }
private:
    Php::Value getMessageKey() {
        if (this->messageKey == "") {
            this->messageKey = std::to_string(rand());
        }
        return this->messageKey;
    }
};

void registerMQProducer(Php::Namespace &rocketMQNamespace);

#endif //ROCKETMQ_ONCE_CLIENT_PHP_PRODUCER_H
