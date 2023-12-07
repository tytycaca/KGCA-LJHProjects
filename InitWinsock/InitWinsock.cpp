#include <WinSock2.h>

void err_quit(char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCWSTR)lpMsgBuf, (LPWSTR)msg, MB_ICONERROR);

	LocalFree(lpMsgBuf);

	exit(1);
}

int main(int argc, char* argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	MessageBox(NULL, L"���� �ʱ�ȭ ����", L"�˸�", MB_OK);

	// ���� ����
	SOCKET TCPSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (TCPSocket == INVALID_SOCKET) err_quit((char*)"socket()");
	MessageBox(NULL, L"TCP ���� ���� ����", L"�˸�", MB_OK);

	// ���� �ݱ�
	closesocket(TCPSocket);

	// ���� ����
	WSACleanup();

	return 0;
}