// �������� 01
// ù��° ������ �����Ͽ� wsa ������ �ʵ��� ó�� �� ���� ȭ�鿡 ����Ͻÿ�.
// ���� 1.1 ������ ����ϵ��� ������ ������ ��� �� ������ ��� �ٲ�°�?
#include <WinSock2.h>
#include <iostream>

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

	// ���� 1.1 ���� ���
	if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
		return 1;
	MessageBox(NULL, L"���� �ʱ�ȭ ����", L"�˸�", MB_OK);

	// wsa Ư�� ���� 4�� ���
	std::cout << wsa.wVersion << std::endl
		<< wsa.wHighVersion << std::endl
		<< wsa.szDescription << std::endl
		<< wsa.szSystemStatus << std::endl;

	// ���� ����
	WSACleanup();

	return 0;
}