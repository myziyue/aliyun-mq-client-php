<?php

namespace MyZiyue;

class MQProducer
{
    public function __construct()
    {
    }

    public function __destruct()
    {
    }

    public function getGroupId(): string
    {
    }

    public function setGroupId(string $groupName) : void
    {
    }

    public function getNameSrvAddr(): string
    {
    }

    public function setNameSrvAddr(string $nameSrvAddr) : void
    {
    }

    public function getTopic(): string
    {
    }

    public function setTopic(string $topic) : void
    {
    }
    // messageKey
    public function getMessageKey():string
    {}
    public function setMessageKey(string $messageKey):void
    {}

    // messageTag
    public function getMessageTag():string
    {}
    public function setMessageTag(string $messageTag):void
    {}

    // deliverTime
    public function getDeliverTime():float
    {}
    public function setDeliverTime(float $deliverTime):void
    {}

    public function auth(string $accessKey, string $secretKey) : void
    {
    }

    public function start() : void
    {
    }

    public function close(): void
    {
    }

    public function send(string $message): string
    {
    }

    public function sendOneway(string $message): string
    {
    }
}