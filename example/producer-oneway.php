<?php

include_once "config.php";

$mqProducer = new \MyZiyue\MQProducer();
$mqProducer->setGroupId($groupId);
$mqProducer->setNameSrvAddr($nameSrvAddr);
$mqProducer->setTopic($topics);
$mqProducer->auth($accessKey, $secretKey);
$mqProducer->start();
try {
    $mqProducer->sendOneway("This is a demo");
} catch (Exception $ex) {
    echo $ex->getMessage();
}

echo $mqProducer->getTopic();
echo $mqProducer->getInstanceId();

$mqProducer->close();
