//
// Created by MyZiyue on 2019/10/31.
//

#ifndef ROCKETMQ_ONCE_CLIENT_PHP_MESSAGE_LISTENER_H
#define ROCKETMQ_ONCE_CLIENT_PHP_MESSAGE_LISTENER_H

#include "common.h"

using namespace ons;

class MQMessageListener : public MessageListener, public Php::Base {
private:
    Php::Value callback;
public:
    Action consume(Message& message, ConsumeContext& context) {
        //此处为具体的消息处理过程，确认消息被处理成功请返回 CommitMessage，
        //如果有消费异常，或者期望重新消费，可以返回 ReconsumeLater，消息将会在一段时间后重新投递
        std::mutex console_mtx;
        std::lock_guard<std::mutex> lk(console_mtx);

        std::map<std::string, std::string> mqMessage;
        mqMessage["topic"] = message.getTopic();
        mqMessage["tag"] = message.getTag();
        mqMessage["key"] = message.getKey();
        mqMessage["msgID"] = message.getMsgID();
        mqMessage["body"] = message.getBody();
        mqMessage["msgBody"] = message.getMsgBody();
        mqMessage["reconsumeTimes"] = message.getReconsumeTimes();
        mqMessage["storeTimestamp"] = message.getStoreTimestamp();
        mqMessage["queueOffset"] = message.getQueueOffset();
        mqMessage["startDeliverTime"] = message.getStartDeliverTime();
        std::string userProperties = Php::call("json_encode", message.getUserProperties());
        mqMessage["userProperties"] = userProperties;
        std::string systemProperties = Php::call("json_encode", message.getSystemProperties());
        mqMessage["systemProperties"] = systemProperties;

        bool result = this->callback(mqMessage);
        return result ? CommitMessage : ReconsumeLater;
    }
    void registerCallback(Php::Value &param) {
        if (!param.isCallable())
            throw Php::Exception("Not a callable type.");
        this->callback = param;
    }
};

void registerMQMessageListener(Php::Namespace &rocketMQNamespace);

#endif //ROCKETMQ_ONCE_CLIENT_PHP_MESSAGE_LISTENER_H




