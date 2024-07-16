#define _WINSOCK_DEPRECATED_NO_WARNINGS //error C4996 : 'inet_addr' : Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

#include <iostream>
#include <winsock.h>

const short port = 10000;

int main()
{
    // 1) ���� �ʱ�ȭ (���� ���� ����)
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("192.168.0.90");
    sa.sin_port = htons(port); // host to network string

    int ret = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
    if (ret == 0)
    {
        printf("���� ���� ip=%s, Port:%d �߽��ϴ�.\n",
            inet_ntoa(sa.sin_addr),
            ntohs(sa.sin_port));
    }
    else
    {
        printf("���� ���� ip=%s, Port:%d �Ұ�, ������.\n",
            inet_ntoa(sa.sin_addr),
            ntohs(sa.sin_port));
    }

    char buf[256] = { 0, };
    int iLen = strlen(buf);
    int iSendByte;

    while (1)
    {
        ZeroMemory(buf, sizeof(char) * 256);
        fgets(buf, 256, stdin);
        if (buf[0] == '\n') break;
        iLen = strlen(buf);
        iSendByte = send(sock, buf, iLen, 0);
        printf("%d����Ʈ�� �����߽��ϴ�\n", iSendByte);
    }

    closesocket(sock);

    // ���� ����    
    WSACleanup();
    std::cout << "Hello World!\n";
}