//
// Created by MyZiyue on 2019/10/31.
//
#include "message-listener.h"


void registerMQOrderMessageListener(Php::Namespace &rocketMQNamespace) {
    Php::Class<MQOrderMessageListener> mqOrderMessageListenerClass("MQOrderMessageListener");
    rocketMQNamespace.add(mqOrderMessageListenerClass);
}

