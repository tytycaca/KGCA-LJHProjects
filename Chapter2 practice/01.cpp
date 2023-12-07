// 연습문제 01
// 첫번째 예제를 수정하여 wsa 변수의 필드중 처음 네 개를 화면에 출력하시오.
// 윈속 1.1 버전을 사용하도록 예제를 수정할 경우 이 값들이 어떻게 바뀌는가?
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
	// 윈속 초기화
	WSADATA wsa;

	// 윈속 1.1 버전 사용
	if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
		return 1;
	MessageBox(NULL, L"윈속 초기화 성공", L"알림", MB_OK);

	// wsa 특정 변수 4개 출력
	std::cout << wsa.wVersion << std::endl
		<< wsa.wHighVersion << std::endl
		<< wsa.szDescription << std::endl
		<< wsa.szSystemStatus << std::endl;

	// 윈속 종료
	WSACleanup();

	return 0;
}