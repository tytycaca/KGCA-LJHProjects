#define _WINSOCK_DEPRECATED_NO_WARNINGS //error C4996 : 'inet_addr' : Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

#include <iostream>
#include <winsock2.h>
const short port = 10000;
// (1)socket
int main()
{
    // 1) ���� �ʱ�ȭ
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sa;
    sa.sin_family = AF_INET;

    sa.sin_addr.s_addr = inet_addr("192.168.0.90");
    sa.sin_port = htons(port);

    int ret = bind(sock, (SOCKADDR*)&sa, sizeof(sa));
    ret = listen(sock, SOMAXCONN);
    SOCKADDR_IN clientaddr;
    SOCKET clientsock;
    printf("���� ���� �۵� ����!!\n");
    while (1) {
        int addlen = sizeof(clientaddr);
        clientsock = accept(sock, (SOCKADDR*)&clientaddr, &addlen);
        printf("Ŭ���̾�Ʈ ���� ip=%s, Port:%d\n",
            inet_ntoa(clientaddr.sin_addr),
            ntohs(clientaddr.sin_port));
        while (1)
        {
            char buf[256] = { 0, };
            int iRecvByte = recv(clientsock, buf, 256, 0);
            if (iRecvByte == 0) break; // ��������
            if (clientsock == SOCKET_ERROR) break;// ������ ����
            printf("[����]%s\n", buf);
        }
        closesocket(clientsock);
        printf("Ŭ���̾�Ʈ �������� ip=%s, Port:%d\n",
            inet_ntoa(clientaddr.sin_addr),
            ntohs(clientaddr.sin_port));
    }
    closesocket(sock);
    // )  ���� ����    
    WSACleanup();
    std::cout << "Hello World!\n";
}
