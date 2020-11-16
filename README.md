# aliyunmq-client-php
----------
[[中文文档]](README_ZH.md) | [English]


A Php Client for Aliyun RocketMQ. 

  Note: because Aliyun's CPP SDK does not support the Coroutine, this extension is temporarily unavailable under the Coroutine framework.

# dependence

- [aliyun-mq-linux-cpp-sdk](https://ons-client-sdk.oss-cn-hangzhou.aliyuncs.com/linux_all_in_one/V2.0.0/aliyun-mq-linux-cpp-sdk.tar.gz?spm=a2c4g.11186623.2.16.717bd2cc5zhMdW&file=aliyun-mq-linux-cpp-sdk.tar.gz)
- [PHP-CPP](http://www.php-cpp.com/)
- [PHP7.1+](https://www.php.net/)

```
 In php7.1 environment, php-cpp 2.1.4 is recommended.
```

# INSTALL

1. Install aliyun-mq-linux-cpp-sdk

```
# wget "https://ons-client-sdk.oss-cn-hangzhou.aliyuncs.com/linux_all_in_one/V2.0.0/aliyun-mq-linux-cpp-sdk.tar.gz?spm=a2c4g.11186623.2.16.717bd2cc5zhMdW&file=aliyun-mq-linux-cpp-sdk.tar.gz" -O aliyun-mq-linux-cpp-sdk.tar.gz
# tar zxvf aliyun-mq-linux-cpp-sdk.tar.gz
# cd aliyun-mq-linux-cpp-sdk/RHEL_7.x/x86_64/
# tar zxvf aliyun-mq-linux-cpp-sdk.tar.gz
# cp -rf aliyun-mq-linux-cpp-sdk/include/* /usr/include/
# cp -rf aliyun-mq-linux-cpp-sdk/lib/* /lib64/
```

2. Install PHP-CPP

```
# git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
# cd PHP-CPP
# make && make install
```

3. Install aliyunmq-client-php
```
# sh build.sh
```
4. update php.ini file, add line extension=aliyunmq.so;
```
# echo "extension=aliyunmq.so" >> $PHP_INSTALL_PATH/etc/php.ini
```

# Usage

to see autocompelete file.

# Example

to see example file.

# todo
- [x] 普通消息发送
- [x] 顺序消息发送
- [x] 定时消息发送
- [ ] 事物消息发送
- [x] 消息接收
