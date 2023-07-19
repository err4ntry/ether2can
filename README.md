## Background

使用以太网转can模块GCAN212和电机通信，分别在windows和linux系统下用tcp通信，发送信号控制电机速度呈正弦函数变化。可以用在四足机器人上，用以太网和关节电机通信。

## Usage

![image](https://github.com/err4ntry/ether2can/assets/102002513/dcdbe7c8-6816-4691-b5af-85988fb06297)


GCAN212模块使用12V直流供电，电机使用24V直流供电。

GCAN212默认IP：192.168.1.10，通信前需要保证PC机和GCAN212在同一个网段内，例如TCP/IPv4设置IP地址：192.168.1.43，子网掩码：255.255.255.0。

GCAN212默认端口号4001，代码中需要保持一致，如addrSrv.sin_port = htons(4001)。

发送的一条 CAN 帧包含 13 个字节，帧信息占1字节，帧ID占4字节，帧数据占8字节。在默认模式下和我们的电机通信前5个字节是0X08,0X00,0X00,0X00,0X01。

帧数据可参考通讯协议：

<img src="C:\Users\CZ\AppData\Roaming\Typora\typora-user-images\image-20220411155249261.png" alt="image-20220411155249261" style="zoom:80%;" />

上传的测试代码中正弦函数峰值速度为10rad/s，周期为10s，每0.1s发送一次信号。
