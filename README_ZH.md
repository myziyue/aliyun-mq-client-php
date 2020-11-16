# aliyunmq-client-php
----------
[中文文档] | [[English]](README.md)


阿里云ONS MQ的PHP扩展客户端。注意：由于阿里云CPP版本SDK不支持协程，所以此扩展在协程框架下暂不可用。

# 依赖

- [aliyun-mq-linux-cpp-sdk V2.1.0](https://ons-client-sdk.oss-cn-hangzhou.aliyuncs.com/linux_all_in_one/2.1.0/rhel7u2/aliyun-mq-linux-cpp-sdk.tar.gz?spm=a2c4g.11186623.2.18.22323a04UlcEJo&file=aliyun-mq-linux-cpp-sdk.tar.gz)
- [PHP-CPP](http://www.php-cpp.com/)
- [PHP7.1+](https://www.php.net/)

```
 在PHP7.1环境下，建议使用PHP-CPP 2.1.4版本
```

# 安装

1. 安装 aliyun-mq-linux-cpp-sdk

```
# wget "https://ons-client-sdk.oss-cn-hangzhou.aliyuncs.com/linux_all_in_one/2.1.0/rhel7u2/aliyun-mq-linux-cpp-sdk.tar.gz?spm=a2c4g.11186623.2.18.22323a04UlcEJo&file=aliyun-mq-linux-cpp-sdk.tar.gz" -O aliyun-mq-linux-cpp-sdk.tar.gz
# tar zxvf aliyun-mq-linux-cpp-sdk.tar.gz
# cd aliyun-mq-linux-cpp-sdk/
# cp -rf include/* /usr/include/
# cp -rf lib/* /lib64/
```

2. 安装 PHP-CPP

```
# git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
# cd PHP-CPP
# make && make install
```

3. 安装 aliyunmq-client-php

```
# sh build.sh
```

4. 配置PHP扩展

```
# echo "extension=aliyunmq.so" >> $PHP_INSTALL_PATH/etc/php.ini
```

# 使用

查看autocomplete文件夹

# 示例

查看example文件夹

# todo
- [x] 普通消息发送
- [x] 顺序消息发送
- [x] 定时消息发送
- [ ] 事物消息发送
- [x] 消息接收
