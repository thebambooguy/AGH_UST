//Imię i nazwisko: Patryk Szeląg
//Nr Indeksu: 283335
//Nazwa projektu: InteractiveSimpleFTP
//Funckja: Client
//Opis: Napisany program służy do przesyłania plików między serwerem a klientem. Serwer jest serwerem
//wspołbieżnym, co oznacza, że w tym samym czasie jest w stanie realizować kilka polączeń z róznymi klientami.
//Program działa w trybie interaktywnym - klient wysyła komendy do serwera, który interpretując je w
//odpowiedni sposób jest w stanie wysłac wiadomość zwrotną do klienta o posiadanych plikach czy też wiadomość,
//ze nie rozumie on co napisał do niego klient. Dzięki temu wystarczy nam tylko okienko klienta, ponieważ
//jestesmy w stanie "dogadać się" z naszym serwerem.
//Komendy, które program jest w stanie zrealizować to:
//1."ls" - client wysyła zapytanie do serwera jakie pliki może od niego dostać
//2."get" - client chce pobrać plik, który posiada serwer, rozpoczyna się etap przesylania odpowiedniego pliku
//3."exit" - client chce zakonczyć połączenie
//4."put" - client wysyła swój plik na serwer -aczkolwiek pojawia się problem po jego użyciu, mianowicie
//funkcja read przestaje być funkcją blokującą po stronie serwera, przez co następne komendy są niepoprawnie
//intepretowane. Program działa, plik zostanie przesłany niestety późniejsze korzystanie z programu jest utrudnione.
//Nie korzystając z komendy put, program działa bez zarzutów.

//Kazda inna wiadomosc do serwera skutkuje nieporozumieniem i taką tez odpowiedzią ze strony serwera.
//Typy plików, na których sprawdzałem dzialanie programu: .pdf, .exe, .rar, .jpg, .PNG, .c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>

#define PORT 4444


	int clientSocket = 0;
	struct sockaddr_in serverAddr;
	int bytesReceived = 0;
	char fname[100];
	char file_buffer[4095], text_buffer[1024];
	

void FileReceive( int temp_sock )
	{

		/* Create file where data will be stored */
		FILE *fp;
		printf("Enter filename: ");
		scanf("%s", &fname[0]);

		write(temp_sock, fname, sizeof(fname));

		read(temp_sock, text_buffer, sizeof(text_buffer));

		if( strcmp( text_buffer, "NOK") != 0 ) {

			fp = fopen(fname, "ab");
			if(fp == NULL ) {
				printf("Error opening file");
				exit(0);
			}

			struct timeval timeout;
			timeout.tv_sec = 2;
			timeout.tv_usec = 0;

			if (setsockopt (temp_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
				error("setsockopt failed\n");

			while((bytesReceived = read(temp_sock, file_buffer, 256)) > 0) {
					fwrite(file_buffer, sizeof(char),bytesReceived,fp);
			}

			if(bytesReceived < 0)
				 printf("Your file proably has been received successfully \n");

			fclose(fp);
			bzero(&file_buffer, sizeof(file_buffer));


		}
		else{
			printf("Server do not have such a file \n");
			bzero(&text_buffer, sizeof(text_buffer));
		}

	}


void FileSend( int temp_sock )
	{

		FILE *ff;
		printf("Enter filename: ");
		scanf("%s", &fname[0]);

		ff = fopen(fname,"rb");
		write(temp_sock, fname, sizeof(fname));
		sleep(2);

		while(1) {


			unsigned char buff[1024]={0};
			int nread = fread(buff,1,1024,ff);

			if(nread > 0){
				write(temp_sock, buff, nread);
			}

			if (nread < 1024){
				if (feof(ff)){
					printf("End of file\n");
					printf("Your file has been transfered correctly \n");
				}
				if (ferror(ff))
					printf("Error reading\n");
				break;
			}
		}

		fclose(ff);
	}


int main(int argc, char *argv[])
	{

		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if(clientSocket < 0) {
			fprintf(stderr,"socket error : %s\n", strerror(errno));
			return 1;
		}

		printf("[+]Client Socket is created.\n");

		bzero(&serverAddr, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(PORT);
		char ip[50];
		if(argc < 2) {
			printf("Enter IP address of server: ");
			gets(ip);
		}
		else
			strcpy(ip,argv[1]);

		serverAddr.sin_addr.s_addr = inet_addr(ip);

		if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
			fprintf(stderr,"connect error : %s \n", strerror(errno));
			return 1;
		}

		printf("[+]Connected to Server.\n");

		//receiveFile( clientSocket );

		while(1) {

			printf("Client:");
			scanf("%s", &text_buffer[0]);
			write(clientSocket, text_buffer, strlen(text_buffer));

			if(strcmp(text_buffer, "exit") == 0){
				close(clientSocket);
				printf("[-]Disconunected from server.\n");
				return 0;
			}

			else if(strcmp(text_buffer, "get") == 0) {
				FileReceive( clientSocket );
				bzero(&text_buffer, sizeof(text_buffer));

			}

			else if(strcmp(text_buffer, "put") == 0) {
				FileSend( clientSocket );
				bzero(&text_buffer, sizeof(text_buffer));
			}

			else if(read(clientSocket, text_buffer, sizeof(text_buffer)) < 0){
				printf("[-]Error in receiving data.\n");
				}

			else{
				printf("Server:\n%s \n", text_buffer);
				bzero(&text_buffer, sizeof(text_buffer));
				}
		}

	}
