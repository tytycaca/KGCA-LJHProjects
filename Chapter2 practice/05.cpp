// 연습문제 05
// 사용자 정의 함수도 일반 소켓 함수와 같은 방법으로 소켓 오류를 처리하도록 만들 수 있다.
// 다음 내용을 참고하여 f() 함수를 정의하시오. (힌트: WSASetLastError())
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

int f(int x)
{
	if (x > 0)
	{
		WSASetLastError(0);
		return 0;
	}
	else if (x < 0)
	{
		WSASetLastError(WSAEMSGSIZE);
		return SOCKET_ERROR;
	}
	else
		return 0;
}

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	MessageBox(NULL, L"윈속 초기화 성공", L"알림", MB_OK);

	// 소켓 생성
	SOCKET TCPSocket = socket(AF_INET6, SOCK_STREAM, 0);
	if (TCPSocket == INVALID_SOCKET) err_quit((char*)"socket()");
	MessageBox(NULL, L"TCP 소켓 생성 성공", L"알림", MB_OK);

	// 소켓 닫기
	closesocket(TCPSocket);

	// 윈속 종료
	WSACleanup();

	return 0;
}