<?php

namespace Yunhu;

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


    public function auth(string $accessKey, string $secretKey) : void
    {
    }

    public function start() : void
    {
    }

    public function close(): void
    {
    }

    public function send(string $message, string $msgTags, string $msgKey): string
    {
    }

    public function sendOneway(string $message, string $msgTags, string $msgKey): string
    {
    }

    public function sendAsync(string $message, string $msgTags, string $msgKey): string
    {
    }

    public function getLogPath(): string
    {
    }

    public function getInstanceId(): string
    {
    }
}