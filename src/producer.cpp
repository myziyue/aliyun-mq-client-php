//
// Created by MyZiyue on 2019/10/25.
//

#include "producer.h"

Php::Value MQProducer::getGroupId() {
    return this->factoryInfo.getGroupId();
}
void MQProducer::setGroupId(Php::Parameters &param) {
    std::string groupId = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::ProducerId, groupId.data());
}

Php::Value MQProducer::getNameSrvAddr() {
    return this->factoryInfo.getNameSrvAddr();
}
void MQProducer::setNameSrvAddr(Php::Parameters &param) {
    std::string nameSrvAddr = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::NAMESRV_ADDR, nameSrvAddr.data());
}

Php::Value MQProducer::getTopic() {
    return this->factoryInfo.getPublishTopics();
}
void MQProducer::setTopic(Php::Parameters &param) {
    std::string topic = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::PublishTopics, topic.data());
}

void MQProducer::auth(Php::Parameters &param) {
    std::string accessKey = param[0];
    std::string secretKey = param[1];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::AccessKey, accessKey.data());
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::SecretKey, secretKey.data());
}

void MQProducer::start() {
    if (this->pProducer == nullptr) {
        try {
            this->pProducer = ONSFactory::getInstance()->createProducer(this->factoryInfo);
            this->pProducer->start();
        } catch(std::exception& exception) {
            Php::out << "exception caught: " << exception.what() << std::endl;
            throw Php::Exception(exception.what());
        }
    }
}

Php::Value MQProducer::send(Php::Parameters &param) {
    // message
    std::string message = param[0];
    // message tag
    std::string messageTag = DEFAULT_TAG_NAME;
    if (param.size() >= 2) {
        std::string tag = param[1];
        if (tag != "") {
            messageTag = tag;
        }
    }
    // message key
    if (param.size() == 3) {
        std::string key = param[2];
        if (key != "") {
            this->messageKey = key;
        }
    }


    // start send message
    SendResultONS sendResultOns;
    try {
        std::string msgKey = this->getMessageKey();
        Message msg(
                this->factoryInfo.getPublishTopics(),
                messageTag.data(),
                msgKey.data(),
                message.data()
        );
        sendResultOns = this->pProducer->send(msg);
    } catch (ONSClientException &exception) {
        this->messageKey = nullptr;
        Php::out << "ErrorCode: " << exception.GetError() << " Exception:" << exception.GetMsg() << std::endl;
        throw Php::Exception(exception.GetMsg());
    }
    return sendResultOns.getMessageId();
}

Php::Value MQProducer::sendOneWay(Php::Parameters &param) {
    // message
    std::string message = param[0];
    // message tag
    std::string messageTag = DEFAULT_TAG_NAME;
    if (param.size() == 2) {
        std::string tag = param[1];
        if (tag != "") {
            messageTag = tag;
        }
    }
    // message key
    if (param.size() == 3) {
        std::string key = param[2];
        if (key != "") {
            this->messageKey = key;
        }
    }

    // start send message
    try {
        std::string msgKey = this->getMessageKey();
        Message msg(
                this->factoryInfo.getPublishTopics(),
                messageTag.data(),
                msgKey.data(),
                message.data()
        );
        this->pProducer->sendOneway(msg);
    } catch (ONSClientException &exception) {
        this->messageKey = nullptr;
        Php::out << "ErrorCode: " << exception.GetError() << " Exception:" << exception.GetMsg() << std::endl;
        throw Php::Exception(exception.GetMsg());
    }
    return true;
}

void MQProducer::close() {
    if (this->pProducer != nullptr) {
        this->pProducer->shutdown();
        this->pProducer = nullptr;
    }
}

Php::Value MQProducer::getLogPath(){
    return this->factoryInfo.getLogPath();
}

Php::Value MQProducer::getInstanceId(){
    return this->factoryInfo.getInstanceId();
}

void registerMQProducer(Php::Namespace &rocketMQNamespace) {
    Php::Class <MQProducer> mqProducerClass("MQProducer");

    mqProducerClass.method<&MQProducer::__construct>("__construct");
    mqProducerClass.method<&MQProducer::__destruct>("__destruct");

    mqProducerClass.method<&MQProducer::getGroupId>("getGroupId");
    mqProducerClass.method<&MQProducer::setGroupId>("setGroupId", {
            Php::ByVal("groupName", Php::Type::String),
    });

    mqProducerClass.method<&MQProducer::getNameSrvAddr>("getNameSrvAddr");
    mqProducerClass.method<&MQProducer::setNameSrvAddr>("setNameSrvAddr", {
            Php::ByVal("nameSrvAddr", Php::Type::String),
    });

    mqProducerClass.method<&MQProducer::getTopic>("getTopic");
    mqProducerClass.method<&MQProducer::setTopic>("setTopic", {Php::ByVal("topic", Php::Type::String),});

    mqProducerClass.method<&MQProducer::auth>("auth", {
            Php::ByVal("accessKey", Php::Type::String),
            Php::ByVal("secretKey", Php::Type::String),
    });

    mqProducerClass.method<&MQProducer::start>("start");

    mqProducerClass.method<&MQProducer::send>("send", {
            Php::ByVal("message", Php::Type::String),
            Php::ByVal("msgTags", Php::Type::String, false),
            Php::ByVal("msgKey", Php::Type::String, false),
    });
    mqProducerClass.method<&MQProducer::sendOneWay>("sendOneWay", {
            Php::ByVal("message", Php::Type::String),
            Php::ByVal("msgTags", Php::Type::String, false),
            Php::ByVal("msgKey", Php::Type::String, false),
    });

    mqProducerClass.method<&MQProducer::getLogPath>("getLogPath");
    mqProducerClass.method<&MQProducer::getInstanceId>("getInstanceId");

    mqProducerClass.method<&MQProducer::close>("close");

    rocketMQNamespace.add(mqProducerClass);
}