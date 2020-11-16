//
// Created by MyZiyue on 2019/10/31.
//

#ifndef ROCKETMQ_ONCE_CLIENT_PHP_CONSUMER_H
#define ROCKETMQ_ONCE_CLIENT_PHP_CONSUMER_H

#include "common.h"
#include "rocketmq/MessageListener.h"
#include "message-listener.h"

using namespace ons;

#define MESSAGE_LISTENER_CLASS_NAME NAMESPACE_NAME"\\MQMessageListener"

class MQConsumer : public Php::Base {
private:
    ons::ONSFactoryProperty factoryInfo;
    ons::PushConsumer *cConsumer = nullptr;
    Php::Value callbackFunc;
public:
    MQConsumer() {}
    virtual ~MQConsumer() {}
    void __construct() {};

    // ConsumerId
    Php::Value getConsumerId();
    void setConsumerId(Php::Parameters &param);

    // topic
    Php::Value getTopic();
    void setTopic(Php::Parameters &param);

    // set aliyun ONS-MQ accessKey and SecretKey
    void auth(Php::Parameters &param);

    // NameSrvAddr
    Php::Value getNameSrvAddr();
    void setNameSrvAddr(Php::Parameters &param);

    // Callback
    void registerCallback(Php::Parameters &param);

    void subscribe(Php::Parameters &param);

    void shutdown();

    void __destruct() {
        if (this->cConsumer != nullptr) {
            this->cConsumer->shutdown();
            delete (this->cConsumer);
        }
    };
};

void registerMQConsumer(Php::Namespace &rocketMQNamespace);

#endif //ROCKETMQ_ONCE_CLIENT_PHP_CONSUMER_H
