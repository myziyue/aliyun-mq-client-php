#!/app/server/php/bin/php
<?php
/**
 *
 */
include_once "config.php";

try {
    $mqProducer = new \MyZiyue\MQProducer();
    $mqProducer->setGroupId($groupId);
    $mqProducer->setNameSrvAddr($nameSrvAddr);
    $mqProducer->setTopic($topics);
    $mqProducer->setMessageTag("test_tag");
    $mqProducer->setMessageKey("S__MSG_php");
    $mqProducer->auth($accessKey, $secretKey);
    $mqProducer->start();
    $msgId = $mqProducer->send("This is a demo");
    var_dump($msgId);
} catch (Exception $ex) {
    echo $ex->getMessage();
}
//echo $mqProducer->getTopic();
//echo $mqProducer->getInstanceId();
$mqProducer->close();

