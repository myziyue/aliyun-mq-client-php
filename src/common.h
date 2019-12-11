//
// Created by MyZiyue on 2019/10/26.
//

#ifndef ROCKETMQ_ONCE_CLIENT_PHP_COMMON_H
#define ROCKETMQ_ONCE_CLIENT_PHP_COMMON_H

#include <string>
#include <iostream>
#include <phpcpp.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <mutex>

#include "ONSFactory.h"
#include "ONSClientException.h"

#include "producer.h"
//#include "mq-exception.h"

#define NAMESPACE_NAME "MyZiyue"
#define DEFAULT_TAG_NAME "MyZiyueTag"
#define DEFAULT_WAIT_TIME 60; // 单位：秒

using namespace ons;

#endif //ROCKETMQ_ONCE_CLIENT_PHP_COMMON_H
