<?php
include_once "config.php";

try{
    $mqConsumer = new \MyZiyue\MQOrderConsumer();
    $mqConsumer->setConsumerId($groupId);
    $mqConsumer->setNameSrvAddr($nameSrvAddr);
    $mqConsumer->setTopic($topics);
    $mqConsumer->auth($accessKey, $secretKey);
    $mqConsumer->registerCallback(function($message){
        var_dump($message);
        echo "====>" . $message['topic'] . "$" . $message['msgID'] . "\n";
        return true;
    });
    $mqConsumer->subscribe(5);
    $mqConsumer->shutdown();
} catch(\Exception $ex) {
    var_dump($ex);
//    echo $ex->getMessage();
}
