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
	int socket_desc, Client1, Client2;
	struct sockaddr_in serverAdd;
	struct sockaddr_storage serverStorage;
	char buffer[1024];
	socklen_t addr_size;

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(8888);
	serverAdd.sin_addr.s_addr = inet_addr("192.168.56.102");
	memset(serverAdd.sin_zero, '\0', sizeof serverAdd.sin_zero);
	bind(socket_desc, (struct sockaddr *) &serverAdd, sizeof(serverAdd));

	if (listen(socket_desc,5)==0)
 	    {
		puts("\n---------- WELCOME TO THE CHATROOM -----------");
		puts("             Server is Ready to Listen.....\n");
	    }
	else
		puts("Error");

	addr_size = sizeof serverStorage;
	Client1 = accept(socket_desc, (struct sockaddr *) &serverStorage, &addr_size);
	Client2 = accept(socket_desc, (struct sockaddr *) &serverStorage, &addr_size);

	int exit = 0;

	while (exit == 0)
	{
		recv(Client1, buffer, 1024, 0);
		printf("%s\n  ---Sending to Client2---\n", buffer);
		send(Client2,buffer,1024,0);

		if (compare_strings(buffer, "exit")==0)
		   {
			exit = 1;
		   }
		else
		   {
			memset(&buffer[0], 0, sizeof(buffer));
			recv(Client2, buffer, 1024, 0);
			printf("%s\n ---Sending to Client1---\n", buffer);
			send(Client1,buffer,1024,0);

			if (compare_strings(buffer, "exit")==0)
			   {
				exit = 1;
			   }
		    }
	}

	return 0;
}
