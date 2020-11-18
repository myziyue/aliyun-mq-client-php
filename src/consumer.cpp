//
// Created by MyZiyue on 2019/10/31.
//
#include "consumer.h"

// ConsumerId
Php::Value MQConsumer::getConsumerId() {
    return this->factoryInfo.getConsumerId();
}
void MQConsumer::setConsumerId(Php::Parameters &param) {
    std::string consumerId = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::ConsumerId, consumerId.data());
}

// topic
Php::Value MQConsumer::getTopic() {
    return this->factoryInfo.getPublishTopics();
}
void MQConsumer::setTopic(Php::Parameters &param) {
    std::string topic = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::PublishTopics, topic.data());
}

// NameSrvAddr
void MQConsumer::setNameSrvAddr(Php::Parameters &param) {
    std::string nameSrvAddr = param[0];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::NAMESRV_ADDR, nameSrvAddr.data());
}
Php::Value MQConsumer::getNameSrvAddr() {
    return this->factoryInfo.getNameSrvAddr();
}

// set aliyun ONS-MQ accessKey and SecretKey
void MQConsumer::auth(Php::Parameters &param) {
    std::string accessKey = param[0];
    std::string secretKey = param[1];
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::AccessKey, accessKey.data());
    this->factoryInfo.setFactoryProperty(ONSFactoryProperty::SecretKey, secretKey.data());
}

void MQConsumer::registerCallback(Php::Parameters &param) {
    if (!param[0].isCallable())
        throw Php::Exception("Not a callable type.");
    this->callbackFunc = param[0];
}

void MQConsumer::subscribe(Php::Parameters &param) {
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
            this->factoryInfo.setFactoryProperty(ONSFactoryProperty::LogPath, Php::ini_get("aliyunmq.log_path"));

            this->cConsumer = ONSFactory::getInstance()->createPushConsumer(this->factoryInfo);
            std::string topic(this->factoryInfo.getPublishTopics());
            std::string tag(tags.data());

            MQMessageListener *mqMessageListener = new MQMessageListener();
            mqMessageListener->registerCallback(this->callbackFunc);
            this->cConsumer->subscribe(topic.c_str(), tag.c_str(), mqMessageListener);
            this->cConsumer->start();

            std::this_thread::sleep_for(std::chrono::milliseconds(waitTime * 1000));
        } catch(ONSClientException exception){
            Php::error << "ErrorCode: " << exception.GetError() << "; Exception:" << exception.GetMsg() << std::flush;
        }
    }
}

void MQConsumer::shutdown() {
    if(this->cConsumer != nullptr) {
        this->cConsumer->shutdown();
        this->cConsumer = nullptr;
    }
}

void registerMQConsumer(Php::Namespace &rocketMQNamespace) {
    Php::Class <MQConsumer> mqConsumerClass("MQConsumer");

    mqConsumerClass.constant("DEFAULT_TAG_NAME", DEFAULT_TAG_NAME);

    mqConsumerClass.method<&MQConsumer::__construct>("__construct");
    mqConsumerClass.method<&MQConsumer::__destruct>("__destruct");

    mqConsumerClass.method<&MQConsumer::getConsumerId>("getConsumerId");
    mqConsumerClass.method<&MQConsumer::setConsumerId>("setConsumerId", {
        Php::ByVal("consumerId", Php::Type::String),
    });

    mqConsumerClass.method<&MQConsumer::getTopic>("getTopic");
    mqConsumerClass.method<&MQConsumer::setTopic>("setTopic", {
        Php::ByVal("topic", Php::Type::String),
    });

    mqConsumerClass.method<&MQConsumer::getNameSrvAddr>("getNameSrvAddr");
    mqConsumerClass.method<&MQConsumer::setNameSrvAddr>("setNameSrvAddr", {
        Php::ByVal("nameSrvAddr", Php::Type::String),
    });

    mqConsumerClass.method<&MQConsumer::auth>("auth", {
        Php::ByVal("accessKey", Php::Type::String),
        Php::ByVal("secretKey", Php::Type::String),
    });

    mqConsumerClass.method<&MQConsumer::registerCallback>("registerCallback", {
        Php::ByVal("callbackFunc", Php::Type::Callable),
    });

    mqConsumerClass.method<&MQConsumer::subscribe>("subscribe", {
        Php::ByVal("waitTime", Php::Type::Numeric, false),
        Php::ByVal("tags", Php::Type::String, false),
    });

    mqConsumerClass.method<&MQConsumer::shutdown>("shutdown");

    rocketMQNamespace.add(mqConsumerClass);
}
