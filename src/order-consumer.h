//
// Created by MyZiyue on 2019/10/31.
//

#ifndef ROCKETMQ_ONCE_CLIENT_PHP_ORDER_CONSUMER_H
#define ROCKETMQ_ONCE_CLIENT_PHP_ORDER_CONSUMER_H

#include "common.h"
#include "MessageListener.h"
#include "order-message-listener.h"

using namespace ons;

#define MESSAGE_LISTENER_CLASS_NAME NAMESPACE_NAME"\\MQMessageListener"

class MQOrderConsumer : public Php::Base {
private:
    ons::ONSFactoryProperty factoryInfo;
    ons::OrderConsumer *cConsumer = nullptr;
    Php::Value callbackFunc;
public:
    MQOrderConsumer() {}
    virtual ~MQOrderConsumer() {}
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

void registerMQOrderConsumer(Php::Namespace &rocketMQNamespace);

#endif //ROCKETMQ_ONCE_CLIENT_PHP_ORDER_CONSUMER_H
