//
// Created by MyZiyue on 2019/10/31.
//
#include "order-consumer.h"

// ConsumerId
Php::Value MQOrderConsumer::getConsumerId() {
    return this->factoryInfo.getConsumerId();
}
void MQOrderConsumer::setConsumerId(Php::Parameters &param) {
    std::string consumerId = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::ConsumerId, consumerId.data());
}

// topic
Php::Value MQOrderConsumer::getTopic() {
    return this->factoryInfo.getPublishTopics();
}
void MQOrderConsumer::setTopic(Php::Parameters &param) {
    std::string topic = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::PublishTopics, topic.data());
}

// NameSrvAddr
void MQOrderConsumer::setNameSrvAddr(Php::Parameters &param) {
    std::string nameSrvAddr = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::NAMESRV_ADDR, nameSrvAddr.data());
}
Php::Value MQOrderConsumer::getNameSrvAddr() {
    return this->factoryInfo.getNameSrvAddr();
}

// set aliyun ONS-MQ accessKey and SecretKey
void MQOrderConsumer::auth(Php::Parameters &param) {
    std::string accessKey = param[0];
    std::string secretKey = param[1];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::AccessKey, accessKey.data());
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::SecretKey, secretKey.data());
}

void MQOrderConsumer::registerCallback(Php::Parameters &param) {
    if (!param[0].isCallable())
        throw Php::Exception("Not a callable type.");
    this->callbackFunc = param[0];
}

void MQOrderConsumer::subscribe(Php::Parameters &param) {
    int waitTime = DEFAULT_WAIT_TIME;
    if (param.size() == 1) {
        int waitTimeParam = param[0];
        if(waitTimeParam > 0){
            waitTime = (int)waitTimeParam;
        }
    }
    std::string tags = "*";
    if (param.size() == 2) {
        std::string tag = param[1];
        if(tag != ""){
            tags = tag;
        }
    }
    if(this->cConsumer == nullptr) {
        try {
            this->factoryInfo.setFactoryProperty("LogPath", Php::ini_get("aliyunmq.log_path"));

            this->cConsumer = ONSFactory::getInstance()->createOrderConsumer(this->factoryInfo);
            std::string topic(this->factoryInfo.getPublishTopics());
            std::string tag(tags.data());

            MQOrderMessageListener *mqOrderMessageListener = new MQOrderMessageListener();
            mqOrderMessageListener->registerCallback(this->callbackFunc);
            this->cConsumer->subscribe(topic.c_str(), tag.c_str(), mqOrderMessageListener);
            this->cConsumer->start();

            std::this_thread::sleep_for(std::chrono::milliseconds(waitTime * 1000));
        } catch(ONSClientException &exception){
            Php::out << "ErrorCode: " << exception.GetError() << " Exception:" << exception.GetMsg() << std::endl;
            throw Php::Exception(exception.GetMsg());
        }
    }
}

void MQOrderConsumer::shutdown() {
    if(this->cConsumer != nullptr) {
        this->cConsumer->shutdown();
        this->cConsumer = nullptr;
    }
}

void registerMQOrderConsumer(Php::Namespace &rocketMQNamespace) {
    Php::Class <MQOrderConsumer> mqOrderConsumerClass("MQOrderConsumer");

    mqOrderConsumerClass.method<&MQOrderConsumer::__construct>("__construct");
    mqOrderConsumerClass.method<&MQOrderConsumer::__destruct>("__destruct");

    mqOrderConsumerClass.method<&MQOrderConsumer::getConsumerId>("getConsumerId");
    mqOrderConsumerClass.method<&MQOrderConsumer::setConsumerId>("setConsumerId", {
        Php::ByVal("consumerId", Php::Type::String),
    });

    mqOrderConsumerClass.method<&MQOrderConsumer::getTopic>("getTopic");
    mqOrderConsumerClass.method<&MQOrderConsumer::setTopic>("setTopic", {
        Php::ByVal("topic", Php::Type::String),
    });

    mqOrderConsumerClass.method<&MQOrderConsumer::getNameSrvAddr>("getNameSrvAddr");
    mqOrderConsumerClass.method<&MQOrderConsumer::setNameSrvAddr>("setNameSrvAddr", {
        Php::ByVal("nameSrvAddr", Php::Type::String),
    });

    mqOrderConsumerClass.method<&MQOrderConsumer::auth>("auth", {
        Php::ByVal("accessKey", Php::Type::String),
        Php::ByVal("secretKey", Php::Type::String),
    });

    mqOrderConsumerClass.method<&MQOrderConsumer::registerCallback>("registerCallback", {
        Php::ByVal("callbackFunc", Php::Type::Callable),
    });

    mqOrderConsumerClass.method<&MQOrderConsumer::subscribe>("subscribe", {
        Php::ByVal("waitTime", Php::Type::Numeric, false),
        Php::ByVal("tags", Php::Type::String, false),
    });

    mqOrderConsumerClass.method<&MQOrderConsumer::shutdown>("shutdown");

    rocketMQNamespace.add(mqOrderConsumerClass);
}