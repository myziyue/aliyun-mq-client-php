//
// Created by MyZiyue on 2019/10/25.
//

#include "order-producer.h"

Php::Value MQOrderProducer::getGroupId() {
    return this->factoryInfo.getGroupId();
}

void MQOrderProducer::setGroupId(Php::Parameters &param) {
    std::string groupId = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::ProducerId, groupId.data());
}

Php::Value MQOrderProducer::getNameSrvAddr() {
    return this->factoryInfo.getNameSrvAddr();
}

void MQOrderProducer::setNameSrvAddr(Php::Parameters &param) {
    std::string nameSrvAddr = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::NAMESRV_ADDR, nameSrvAddr.data());
}

Php::Value MQOrderProducer::getTopic() {
    return this->factoryInfo.getPublishTopics();
}

void MQOrderProducer::setTopic(Php::Parameters &param) {
    std::string topic = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::PublishTopics, topic.data());
}

// messageKey
Php::Value MQOrderProducer::getMessageKey() {
    return this->messageKey;
}

void MQOrderProducer::setMessageKey(Php::Parameters &param) {
    std::string messageKey = param[0];
    this->messageKey = messageKey;
}

// messageTag
Php::Value MQOrderProducer::getMessageTag() {
    return this->messageTag;
}

void MQOrderProducer::setMessageTag(Php::Parameters &param) {
    std::string messageTag = param[0];
    this->messageTag = messageTag;
}

// shardingKey
Php::Value MQOrderProducer::getShardingKey() {
    return this->shardingKey;
}

void MQOrderProducer::setShardingKey(Php::Parameters &param) {
    std::string shardingKey = param[0];

//    std::cout << "#" << shardingKey << "#" << std::endl;
    this->shardingKey = shardingKey;
}

// deliverTime
void MQOrderProducer::setDeliverTime(Php::Parameters &param) {
    long deliverTime = param[0];
    if (deliverTime > 0) {
        this->deliverTime = getTimeStamp() + deliverTime * 1000;
    } else {
        this->deliverTime = 0;
    }
}

void MQOrderProducer::auth(Php::Parameters &param) {
    std::string accessKey = param[0];
    std::string secretKey = param[1];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::AccessKey, accessKey.data());
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::SecretKey, secretKey.data());
}

void MQOrderProducer::start() {
    if (this->shardingKey == "") {
        Php::error << "ShardingKey is empty(0).") << std::flush;
    }
    if (this->pOrderProducer == nullptr) {
        try {
            this->factoryInfo.setFactoryProperty(ONSFactoryProperty::LogPath, Php::ini_get("aliyunmq.log_path"));

            this->pOrderProducer = ONSFactory::getInstance()->createOrderProducer(this->factoryInfo);
            this->pOrderProducer->start();
        } catch (Php::Exception &exception) {
            Php::error << "exception caught: " << exception.what() << std::flush;
        }
    }
}

Php::Value MQOrderProducer::send(Php::Parameters &param) {
    // message
    std::string message = param[0];

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
    if (this->shardingKey == "") {
        Php::error << "ShardingKey is empty(1).") << std::flush;
    }

    // start send message
    try {
        SendResultONS sendResultOns = this->pOrderProducer->send(msg, this->shardingKey);
        return sendResultOns.getMessageId();
    } catch (ONSClientException exception) {
        Php::error << "ErrorCode: " << exception.GetError() << "; Exception:" << exception.GetMsg() << std::flush;
    }
    return nullptr;
}

void MQOrderProducer::close() {
    if (this->pOrderProducer != nullptr) {
        this->pOrderProducer->shutdown();
        this->pOrderProducer = nullptr;
    }
}

void registerMQOrderProducer(Php::Namespace &rocketMQNamespace) {
    Php::Class <MQOrderProducer> mqOrderProducerClass("MQOrderProducer");

    mqOrderProducerClass.method<&MQOrderProducer::__construct>("__construct");
    mqOrderProducerClass.method<&MQOrderProducer::__destruct>("__destruct");

    mqOrderProducerClass.method<&MQOrderProducer::getGroupId>("getGroupId");
    mqOrderProducerClass.method<&MQOrderProducer::setGroupId>("setGroupId", {
            Php::ByVal("groupName", Php::Type::String),
    });

    mqOrderProducerClass.method<&MQOrderProducer::getNameSrvAddr>("getNameSrvAddr");
    mqOrderProducerClass.method<&MQOrderProducer::setNameSrvAddr>("setNameSrvAddr", {
            Php::ByVal("nameSrvAddr", Php::Type::String),
    });

    mqOrderProducerClass.method<&MQOrderProducer::getTopic>("getTopic");
    mqOrderProducerClass.method<&MQOrderProducer::setTopic>("setTopic", {Php::ByVal("topic", Php::Type::String),});

    mqOrderProducerClass.method<&MQOrderProducer::getMessageKey>("getMessageKey");
    mqOrderProducerClass.method<&MQOrderProducer::setMessageKey>("setMessageKey", {Php::ByVal("messageKey", Php::Type::String),});


    mqOrderProducerClass.method<&MQOrderProducer::getMessageTag>("getMessageTag");
    mqOrderProducerClass.method<&MQOrderProducer::setMessageTag>("setMessageTag", {Php::ByVal("messageTag", Php::Type::String),});


    mqOrderProducerClass.method<&MQOrderProducer::getShardingKey>("getShardingKey");
    mqOrderProducerClass.method<&MQOrderProducer::setShardingKey>("setShardingKey", {Php::ByVal("shardingKey", Php::Type::String),});

    mqOrderProducerClass.method<&MQOrderProducer::setDeliverTime>("setDeliverTime", {Php::ByVal("deliverTime", Php::Type::Float),});

    mqOrderProducerClass.method<&MQOrderProducer::auth>("auth", {
            Php::ByVal("accessKey", Php::Type::String),
            Php::ByVal("secretKey", Php::Type::String),
    });

    mqOrderProducerClass.method<&MQOrderProducer::start>("start");

    mqOrderProducerClass.method<&MQOrderProducer::send>("send", {
            Php::ByVal("message", Php::Type::String),
    });

    mqOrderProducerClass.method<&MQOrderProducer::close>("close");

    rocketMQNamespace.add(mqOrderProducerClass);
}
