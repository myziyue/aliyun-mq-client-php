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

// messageKey
Php::Value MQProducer::getMessageKey() {
    return this->messageKey;
}

void MQProducer::setMessageKey(Php::Parameters &param) {
    std::string messageKey = param[0];
    this->messageKey = messageKey;
}

// messageTag
Php::Value MQProducer::getMessageTag() {
    return this->messageTag;
}

void MQProducer::setMessageTag(Php::Parameters &param) {
    std::string messageTag = param[0];
    this->messageTag = messageTag;
}

// deliverTime
void MQProducer::setDeliverTime(Php::Parameters &param) {
    long deliverTime = param[0];
    if (deliverTime > 0) {
        this->deliverTime = getTimeStamp() + deliverTime * 1000;
    } else {
        this->deliverTime = 0;
    }
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
            this->factoryInfo.setFactoryProperty("LogPath", Php::ini_get("aliyunmq.log_path"));

            this->pProducer = ONSFactory::getInstance()->createProducer(this->factoryInfo);
            this->pProducer->start();
        } catch (std::exception &exception) {
            Php::out << "exception caught: " << exception.what() << std::endl;
            throw Php::Exception(exception.what());
        }
    }
}

Php::Value MQProducer::send(Php::Parameters &param) {
    // message
    std::string message = param[0];

    // start send message
    SendResultONS sendResultOns;

    try {
        Message msg(
                this->factoryInfo.getPublishTopics(),
                DEFAULT_TAG_NAME,
                message.data()
        );
        if (this->getMessageKey()) {
            msg.setKey(this->getMessageKey());
        }
        if (this->getMessageTag()) {
            msg.setTag(this->getMessageTag());
        }
        if (this->deliverTime) {
            msg.setStartDeliverTime((float)this->deliverTime);
        }
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
    // start send message
    try {
        Message msg(
                this->factoryInfo.getPublishTopics(),
                DEFAULT_TAG_NAME,
                message.data()
        );
        if (this->getMessageKey()) {
            msg.setKey(this->getMessageKey());
        }
        if (this->getMessageTag()) {
            msg.setTag(this->getMessageTag());
        }
        if (this->deliverTime) {
            msg.setStartDeliverTime((float)this->deliverTime);
        }
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

    mqProducerClass.method<&MQProducer::getMessageKey>("getMessageKey");
    mqProducerClass.method<&MQProducer::setMessageKey>("setMessageKey", {Php::ByVal("messageKey", Php::Type::String),});


    mqProducerClass.method<&MQProducer::getMessageTag>("getMessageTag");
    mqProducerClass.method<&MQProducer::setMessageTag>("setMessageTag", {Php::ByVal("messageTag", Php::Type::String),});

    mqProducerClass.method<&MQProducer::setDeliverTime>("setDeliverTime", {Php::ByVal("deliverTime", Php::Type::Float),});

    mqProducerClass.method<&MQProducer::auth>("auth", {
            Php::ByVal("accessKey", Php::Type::String),
            Php::ByVal("secretKey", Php::Type::String),
    });

    mqProducerClass.method<&MQProducer::start>("start");

    mqProducerClass.method<&MQProducer::send>("send", {
            Php::ByVal("message", Php::Type::String),
    });
    mqProducerClass.method<&MQProducer::sendOneWay>("sendOneWay", {
            Php::ByVal("message", Php::Type::String),
    });

    mqProducerClass.method<&MQProducer::close>("close");

    rocketMQNamespace.add(mqProducerClass);
}