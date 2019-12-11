<?php
namespace Yunhu;


class MQConsumer
{
    const DEFAULT_TAG_NAME = "DefaultTag";
    public function __construct()
    {
    }

    public function __destruct()
    {
    }

    public function getConsumerId(): string
    {
    }

    public function setConsumerId(string $consumerId): void
    {
    }

    public function getTopic(): string
    {
    }

    public function setTopic(string $topic): void
    {
    }

    public function getNameSrvAddr(): string
    {
    }

    public function setNameSrvAddr(string $nameSrvAddr) : void
    {
    }


    public function auth(string $accessKey, string $secretKey) : void
    {
    }

    public function registerCallback(callable $callbackFunc) : void
    {
    }

    public function subscribe(int $waitTime = 60, string $tags = MQConsumer::DEFAULT_TAG_NAME) : void
    {
    }

    public function shutdown() : void
    {
    }
}