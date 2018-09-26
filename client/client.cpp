#include "HClient.h"
#pragma warning(disable : 4996)
using namespace std;

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);
    int SIZE = 120;
    struct sockaddr_in connection;
    int sss = sizeof(sockaddr_in);
    connection.sin_family = AF_INET;
    connection.sin_port = htons(80);
    connection.sin_addr.s_addr = inet_addr("127.0.0.1");
    char buf[120], str[120];
    do {
        SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
        //connect(s, (struct sockaddr*)&connection, sizeof(connection));

        cout << "Enter the string, please" << endl;
        cin.getline(buf, SIZE - 1, '\n');

        sendto(s, buf, sizeof(buf), 0, (struct sockaddr*) &connection, sss);

        int rev = recvfrom(s, str, sizeof(str), 0, (struct sockaddr*) &connection, &sss);
        cout << str << endl;
        for (int i = 0; i < SIZE; i++)
            buf[i] = str[i] = '\0';
        closesocket(s);
        cout << "Click Esc to exit" << endl;
        if (getch() == 27) break;
    } while (getch() != 27);
    WSACleanup();

    return 0;
}

