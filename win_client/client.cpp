#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "winsock2.h"
#include<cstdlib>
#include <cmath>
#include<windows.h>
#include<string>
#include<cstring>
#define PI 3.1415926

#pragma comment(lib,"ws2_32.lib")//引用库文件

using namespace std;

//10进制转16进制
string trans(int n)
{
	int x;
	string s;
	char c;
	while (n != 0)
	{
		x = n % 16;
		//cout << x << endl;
		if (x < 10)
		{
			c = x + '0';
		}
		else
		{
			c = x + 'A' - 10;
		}

		s = c + s;

		n = n / 16;
	}

	//	cout << s;

	if (s == "") 
	{
		return "";
	}
	else 
	{
		return s;
	}

}

int main()
{
	//加载套接字
	WSADATA wsaData;
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("初始化Winsock失败");
		return 0;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(4001);//端口号
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.1.10");//IP地址

	//创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == sockClient) 
	{
		printf("Socket() error:%d", WSAGetLastError());
		return 0;
	}

	//向服务器发出连接请求
	if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET) 
	{
		printf("连接失败:%d", WSAGetLastError());
		return 0;
	}
	printf("连接成功\n");

	//发送数据
	
	/*char buffs[] = { 0X08,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC };
	char buffs[] = { 0X08,0x00,0x00,0x00,0x01,0x7F,0xFF,0x82,0xd0,0x00,0x33,0x37,0xFF };*/
	
	char buffs1[] = { 0X08,0X00,0x00,0x00,0x01,0XFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFc };
	send(sockClient, buffs1, sizeof(buffs1), 0);
	
	//如果要将string转换为char* ，可以使用string提供的函数c_str() ，或是函数data()，data除了返回字符串内容外，不附加结束符'\0'，而c_str()返回一个以‘\0’结尾的字符数组。
	for (double t = 0; t < 10; t+=0.1)
	{
		double v = 10 * sin(t * (PI / 5));
		double v1 = (pow(2,12) - 1)*(v + 45) / 90;
		string v2 = trans(v1);
		uint8_t p1 = v2.data()[0];
		uint8_t p2 = v2.data()[1];
		uint8_t p3 = v2.data()[2];
		/*cout << p1 << endl;
		cout << p2 << endl;
		cout << p3 << endl;*/
		cout << v << "  " << v1 << "  " << v2 << endl;

		if (p1 > 57)
		{
			p1 -= 55;
		}
		else
		{
			p1 -= 48;
		}
		if (p2 > 57)
		{
			p2 -= 55;
		}
		else
		{
			p2 -= 48;
		}
		if (p3 > 57)
		{
			p3 -= 55;
		}
		else
		{
			p3 -= 48;
		}

		//printf("%d \n", p1);
		//uint8_t p = 0x0F;
		p1 <<= 4;
		p3 <<= 4;



		//cout <<(uint8_t)p1 << " " << (uint8_t)p2 << "  " << (uint8_t)p3 << endl;
		/*printf("%d \n", p1);
		printf("%d \n", p2);
		printf("%d \n", p3);*/
		char buffs[] = { 0X08,0x00,0x00,0x00,0x01,0x7F,0xFF,p1+ p2,p3,0x00,0x33,0x37,0xFF };
		send(sockClient, buffs, sizeof(buffs), 0);
		
		
		
		Sleep(0.1 * 1000);   
	} 

	//vref=(2^12-1)(v+45)/90  1.5字节
	
	char buffs2[] = { 0X08,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFd };
	send(sockClient, buffs2, sizeof(buffs2), 0);



	//不断输入，然后发送
	/*while (true)
	{
		

		
		
		cin >> buffs;
		send(sockClient, buffs, sizeof(buffs), 0);

	}*/

	//关闭套接字
	closesocket(sockClient);
	WSACleanup();//释放初始化Ws2_32.dll所分配的资源。
	system("pause");
	return 0;
}



