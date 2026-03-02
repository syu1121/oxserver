#include "Server.h"

using namespace std;


Server::Server()
{
}

Server::~Server()
{
}

bool Server::Init()
{
	// WinSock2.2初期化
	WSADATA	wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "Error :WSAStartup" << endl;
		return false;
	}
	cout << "Success :WSAStartup" << endl;

	// TCPリスンソケットの作成
	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		int errorCode = WSAGetLastError();
		cout << "Error :socket" << endl;
		return false;
	}
	cout << "Success :socket" << endl;


	// 固定アドレスの割り当て
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listenSock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		int errorCode = WSAGetLastError();
		cout << "Error :bind" << endl;
		return false;
	}
	cout << "Success :bind" << endl;

	// リスン状態に設定
	if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR)
	{
		int errorCode = WSAGetLastError();
		cout << "Error :listen" << endl;
		return false;
	}
	cout << "Success :listen" << endl;


	return true;
}

void Server::WaitClient()
{
	// 3クライアント用のソケットを用意
	

	// 3クライアント用のソケットアドレス構造体を用意...クライアントのアドレスも使いたくなるかもしれないから
	SOCKADDR_IN clientSocketAddresses[2];
	int addressLength = sizeof(SOCKADDR_IN);

	// 3クライアントからの接続要求を待つ
	int clientCount = 0;
	while (clientCount < 3)
	{
		// いったんSOCKET型の変数に入れて…
		SOCKET tmpSock = accept(listenSock, (SOCKADDR*)&clientSocketAddresses[clientCount], &addressLength);
		if (tmpSock == INVALID_SOCKET)
		{
			// 接続要求受付エラー
		}
		else
		{
			// 接続要求受付たら、3クライアント用のソケット配列にセットする
			socks[clientCount] = tmpSock;
			clientCount++;
		}
	}
	
}

void Server::Run()
{
	char buff[256];
	while (true)
	{
		int playerIndex = game.GetCurrentPlayer() - 1;
		int ret = recv(socks[playerIndex], buff, sizeof(buff) - 1, 0);

		if (ret <= 0)
		{

		}
		
	}




}

void Server::Cleanup()
{
	for (int i = 0; i < 2; i++)
	{
		shutdown(socks[i], SD_BOTH);

		// ソケット破棄
		closesocket(socks[i]);
	}

	// ソケット破棄
	closesocket(listenSock);


	// WinSockの終了処理
	if (WSACleanup() != 0)
	{
		cout << "Error :WSACleanup" << endl;
	}
	cout << "Success :WSACleanup" << endl;
}
