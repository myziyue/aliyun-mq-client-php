//
// Created by MyZiyue on 2019/10/25.
//
#include "common.h"

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {

    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module()
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("aliyunmq", "1.2.0");

        // add your own functions, classes, namespaces to the extension
        // all class in RocketMQ namespace.
        Php::Namespace rocketMQNamespace(NAMESPACE_NAME);

        // class Producer
//        registerMQException(rocketMQNamespace);
        registerMQMessageListener(rocketMQNamespace);
        registerMQProducer(rocketMQNamespace);
        registerMQConsumer(rocketMQNamespace);
        registerMQOrderProducer(rocketMQNamespace);
        registerMQOrderConsumer(rocketMQNamespace);

        extension.add(std::move(rocketMQNamespace));
        extension.add(Php::Ini("aliyunmq.log_path", "/tmp/"));

        // return the extension
        return extension;
    }
}

