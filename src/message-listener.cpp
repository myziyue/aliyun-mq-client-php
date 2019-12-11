//
// Created by MyZiyue on 2019/10/31.
//
#include "message-listener.h"


void registerMQMessageListener(Php::Namespace &rocketMQNamespace) {
    Php::Class<MQMessageListener> mqMessageListenerClass("MQMessageListener");
    rocketMQNamespace.add(mqMessageListenerClass);
}

