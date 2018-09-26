#include "HServer.h"
using namespace std;

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);

    struct sockaddr_in connection;
    connection.sin_family = AF_INET;
    connection.sin_port = htons(1280);
    connection.sin_addr.s_addr = INADDR_ANY;

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
    int err = bind(s, (struct sockaddr*)&connection, sizeof(connection));

    err = listen(s, 20);
    char str[120], str2[120];

    int clientlen;
    while (true) {
        sockaddr_in client;
        clientlen = sizeof(client);
        recvfrom(s, str, sizeof(str), 0, (struct sockaddr*) &client, &clientlen);
        cout << "Accepted: " << str << endl;
		int j = 0, n = strlen(str), count = 0, max_count = 0, word_begin[100], current_word;
		for (int i = 0; i <= n; i++) {
			if (i != n && (str[i] != ' '))
				count++;
			else {
				if (count > max_count) {
					word_begin[0] = i - count;
					current_word = 1;
					max_count = count;
				}
				else if (count == max_count) {
					word_begin[current_word] = i - count;
					current_word++;
				}
				count = 0;
			}
		}
		for (int a = 0; a < current_word; a++, j++) {
			for (int i = word_begin[a]; i < (max_count + word_begin[a]) ; i++, j++) {
				str2[j] = str[i];
			}
			str2[j] = ' ';
		}
        str2[j] = '\0';
        sendto(s, str2, sizeof(str2), 0, (struct sockaddr*) &client, clientlen);
    }
	closesocket(s);
    WSACleanup();
    return 0;
}