#!/app/server/php/bin/php
<?php
/**
 *
 */
include_once "config.php";

try {
    $mqProducer = new \MyZiyue\MQOrderProducer();
    $mqProducer->setGroupId($groupId);
    $mqProducer->setNameSrvAddr($nameSrvAddr);
    $mqProducer->setTopic($topics);
    $mqProducer->auth($accessKey, $secretKey);

    $mqProducer->setShardingKey("test-abc");
    $mqProducer->setMessageKey("testkey");
    $mqProducer->setMessageTag("testtag");
    
    $mqProducer->start();
    // 顺序分布
    var_dump($mqProducer->send("This is a demo"));
} catch (Exception $ex) {
    echo $ex->getMessage();
}
//echo $mqProducer->getTopic();
//echo $mqProducer->getInstanceId();
$mqProducer->close();

