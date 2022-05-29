#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int compare_strings(char x[], char y[])
{
	int z = 0;
	while (x[z] == y[z])
	{
		if (x[z] == '\0' || y[z] == '\0')
		break;
		z++;
	}
	if (x[z] == '\0' && y[z] == '\0')

	return 0;

	else

	return -1;
}

int main() {

	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAdd;
	socklen_t addr_size;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(8888);
	serverAdd.sin_addr.s_addr = inet_addr("192.168.56.102");
	memset(serverAdd.sin_zero, '\0', sizeof serverAdd.sin_zero);
	addr_size = sizeof serverAdd;

	//Connect to Server
	if (connect(clientSocket, (struct sockaddr *) &serverAdd, addr_size) <0 ) 
          {
		puts("CONNECTION FAILS");
	  }
	else{
		puts("-----WELCOME TO THE CHATROOM-----\n");
	}

	//Input message from Client1
	printf("Client 1 : ");
	scanf(" %[^\n]s", buffer);
	send(clientSocket,buffer,sizeof buffer - 1,0);

	//message will be send & receive till client type "exit"
	int exit = 0;
	while (exit == 0)
	{
		if (compare_strings(buffer, "exit")==-1)
		{
			memset(&buffer[0], 0, sizeof(buffer));

			int receive = recv(clientSocket, buffer, sizeof buffer - 1, 0);

			if (receive != 1)
			{
				if (compare_strings(buffer, "exit")==-1)
				{
					printf("Client 2 : ");
					printf("%s\n", buffer);

					memset(&buffer[0], 0, sizeof(buffer));
				}
				else exit = 1;
			}
			else
			{
				printf("Client 1 : ");
				scanf(" %[^\n]s", buffer);

				send(clientSocket, buffer, sizeof buffer - 1,0);
			}
		}
		//Exit loop when client 1 type "exit"
		else exit = 1;
	}
	return 0;
}
