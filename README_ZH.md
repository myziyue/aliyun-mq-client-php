# aliyunmq-client-php
----------
[English](README.md)
----------

阿里云ONS MQ的PHP扩展客户端。

# 依赖

- [aliyun-mq-linux-cpp-sdk V2.0.0](https://ons-client-sdk.oss-cn-hangzhou.aliyuncs.com/linux_all_in_one/V2.0.0/aliyun-mq-linux-cpp-sdk.tar.gz?spm=a2c4g.11186623.2.16.717bd2cc5zhMdW&file=aliyun-mq-linux-cpp-sdk.tar.gz)
- [PHP-CPP](http://www.php-cpp.com/)
- [PHP7.2+](https://www.php.net/)

# 安装

1. 安装 aliyun-mq-linux-cpp-sdk

```
# cp -rf aliyun-mq-linux-cpp-sdk-centos7/include/* /usr/include/
# cp -rf aliyun-mq-linux-cpp-sdk-centos7/lib/* /lib64/
```

2. 安装 PHP-CPP

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
