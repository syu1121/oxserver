#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <DxLib.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // WinSock2.2 初期化
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "Error : WSAStartup" << endl;
        return 1;
    }
    cout << "Success : WSAStartup" << endl;

    // TCPリスンソケットの作成
    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET)
    {
        cout << "Error : socket" << endl;
        return 1;
    }
    cout << "Success : socket" << endl;

    // ノンブロッキング設定
    unsigned long cmdarg = 0x01;
    ioctlsocket(listenSock, FIONBIO, &cmdarg);

    // 固定アドレスの割り当て
    SOCKADDR_IN bindSocketAddress;
    memset(&bindSocketAddress, 0, sizeof(bindSocketAddress));
    bindSocketAddress.sin_family = AF_INET;
    bindSocketAddress.sin_port = htons(8888);
    bindSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenSock, (SOCKADDR*)&bindSocketAddress, sizeof(bindSocketAddress)) == SOCKET_ERROR)
    {
        cout << "Error : bind" << endl;
        return 1;
    }
    cout << "Success : bind" << endl;

    // リスン状態に設定
    if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Error : listen" << endl;
        return 1;
    }
    cout << "Success : listen" << endl;

    // クライアントソケット管理
    vector<SOCKET> socks;
    SOCKADDR_IN clientAddr;
    int addressLength = sizeof(SOCKADDR_IN);

    // DxLib周りの初期化・ウィンドウ作成処理
    SetWindowText("サーバ！");
    SetGraphMode(800, 600, 32);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetBackgroundColor(0, 0, 0);
    SetDrawScreen(DX_SCREEN_BACK);
    SetAlwaysRunFlag(1);





    // メインループ
    while (1)
    {
        // 接続受け入れ
        int tmpSock = accept(listenSock, (SOCKADDR*)&clientAddr, &addressLength);
        if (tmpSock > 0)
        {
            ioctlsocket(listenSock, FIONBIO, &cmdarg);
            socks.push_back(tmpSock);
        }

        // 受信処理
        for (int i = 0; i < socks.size(); i++)
        {
            char buff[256];
            int ret = recv(socks[i], (char*)&buff, sizeof(buff), 0);
            if (ret > 0)
            {
               
               
            }
            else
            {
                if (WSAGetLastError() == WSAECONNRESET)
                {
                    cout << "shutdown" << endl;
                    shutdown(socks[i], SD_BOTH);
                    closesocket(socks[i]);
                    socks[i] = -1;
                }
            }
        }


        


        // 切断されたソケットの削除
        socks.erase(
            remove_if(socks.begin(), socks.end(), [](SOCKET sock)
                { return sock == -1; }),
            socks.end());

        ScreenFlip();
        WaitTimer(16);
        if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
        {
            break;
        }
    }
    DxLib_End();
}
