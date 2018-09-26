#include "HServer.h"
#pragma warning(disable : 4996)
using namespace std;

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);

    struct sockaddr_in connection;
    int sss = sizeof(sockaddr_in);
    connection.sin_family = AF_INET;
    connection.sin_port = htons(80);
    connection.sin_addr.s_addr = INADDR_ANY;

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
    int err = bind(s, (struct sockaddr*)&connection, sizeof(connection));

    err = listen(s, 20);
    char str[120], str2[120];

    int clientlen;
    while (true) {
        sockaddr_in client;
        clientlen = sizeof(client);
        //SOCKET s1 = accept(s, (struct sockaddr*)&client, &clientlen);

        recvfrom(s, str, sizeof(str), 0, (struct sockaddr*) &client, &clientlen);

        cout << "Accepted: " << str << endl;

        int j = 0, n = strlen(str);
        for (int i = 0; i < n; i++)
            if (str[i] != ' ')
                str2[j++] = str[i];
            else
                if (i != 0 && (str[i - 1] != ' ' && str[i] == ' '))
                    str2[j++] = str[i];
        str2[j] = '\0';

        sendto(s, str2, sizeof(str2), 0, (struct sockaddr*) &client, clientlen);
        //closesocket(s); 
    }
    WSACleanup();
    return 0;
}