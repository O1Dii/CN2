#include "HClient.h"
using namespace std;

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);
    int SIZE = 120;
    struct sockaddr_in connection;
    connection.sin_family = AF_INET;
    connection.sin_port = htons(1280);
	inet_pton(AF_INET, "127.0.0.1", &connection.sin_addr);
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	int sss = sizeof(sockaddr_in);
    char buf[120], str[120], check;
    do {
		cout << "Enter the string, please" << endl;
        cin.getline(buf, SIZE - 1, '\n');
        sendto(s, buf, sizeof(buf), 0, (struct sockaddr*) &connection, sss);
        int rev = recvfrom(s, str, sizeof(str), 0, (struct sockaddr*) &connection, &sss);
        cout << str << endl;
        for (int i = 0; i < SIZE; i++)
            buf[i] = str[i] = '\0';
        cout << "Enter 1 to continue" << endl;
		cin >> check;
		cin.ignore(cin.rdbuf()->in_avail());
    } while (check == '1');
	closesocket(s);
    WSACleanup();
    return 0;
}

