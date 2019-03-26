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

	int sockfd;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;
	char file_buffer[4095], text_buffer[1024];
	char fname[100];
	int bytesReceived = 0;
	pid_t childpid;


void sig_chld(int signo)
	{
		pid_t pid;
		int stat;

		while( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
			printf("Child %d terminated \n", pid);
		return;

	}

void FileSend( int temp_sock )
	{

		read(temp_sock, fname,sizeof(fname));
		FILE *fp = fopen(fname,"rb");
        if(fp==NULL) {
                printf("Wrong name of file \n");
           	    snprintf(text_buffer, sizeof(text_buffer),"NOK");
	    	    write(temp_sock, text_buffer, sizeof(text_buffer));
		        bzero(&text_buffer, sizeof(text_buffer));
            	
        }

	    else{
		    snprintf(text_buffer, sizeof(text_buffer),"OK");
		    write(temp_sock, text_buffer, sizeof(text_buffer));
		    bzero(&text_buffer, sizeof(text_buffer));
		    sleep(2);



        	while(1) {

            		unsigned char buff[1024]={0};
            		int nread = fread(buff,1,1024,fp);
                 

           		    if(nread > 0){
               			 write(temp_sock, buff, nread);
            		}

            		if (nread < 1024){
            		        if (feof(fp)){
            		        	printf("End of file\n");
            		        	printf("Your file has been transfered correctly \n");
            		        }
                	        if (ferror(fp))
                   		        printf("Error reading\n");
                   		        break;
           		    }
        	}
		}

		fclose(fp);
	}

void FileReceive( int temp_sock )
	{
		FILE *ff;
		char fname[100];
		read(temp_sock, fname,sizeof(fname));


		ff = fopen(fname, "ab");
		if(ff == NULL ) {
			printf("Error opening file");
			exit(0);
		}

		struct timeval timeout;
		timeout.tv_sec = 2;
		timeout.tv_usec = 0;

		if (setsockopt (temp_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
			error("setsockopt failed\n");

		while((bytesReceived = read(temp_sock, file_buffer, 256)) > 0) {
			fwrite(file_buffer, sizeof(char),bytesReceived,ff);
		}

		if(bytesReceived < 0)
			printf("Your file proably has been received successfully \n");

		fclose(ff);
		bzero(&file_buffer, sizeof(file_buffer));

	}


int main(int argc, char *argv[])
	{

		if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			fprintf(stderr, "Socket error: %s \n", strerror(errno));
			return 1;
		}

		printf("[+]Server Socket is created.\n");

		bzero(&serverAddr, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(PORT);
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		if( bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
			fprintf(stderr,"Bind error: %s\n", strerror(errno));
			return 1;
		}

		printf("[+]Bind to port %d\n", 4444);

		if( listen(sockfd, 10) < 0 ){
			fprintf(stderr,"Listen error: %s\n", strerror(errno));
			return 1;
		}
		else {
			printf("Waiting for clients...\n");
		}


		signal(SIGCHLD, sig_chld);


		while(1){

			newSocket = accept(sockfd, (struct sockaddr*) &newAddr, &addr_size);
			if( newSocket < 0){
				//fprintf(stderr, "Accept error: %s\n", strerror(errno));
				continue;
			}

			printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port)); //dlaczego jak ja rzuce pod close(sockfd) to wypierdziela program

			if((childpid = fork()) == 0){
			close(sockfd);

				while(1) {

					read(newSocket, text_buffer, sizeof(text_buffer)) ; //nie blokuje sie na readzie po "put"
					printf("%s \n", text_buffer);



						if (strcmp(text_buffer, "exit") == 0) {
							printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
							break;
						}

						else if (strcmp(text_buffer, "ls") == 0) {

							FILE *fp;
							char path[256];
							char buff[256];

							/* Open the command for reading. */
							fp = popen("ls", "r");
							if (fp == NULL) {
								printf("Failed to run command\n");
								exit(1);
							}

							/* Read the output a line at a time - output it. */
							while (fgets(path, sizeof(path), fp) != NULL) {
								strcat(buff, path);
							}

							send(newSocket, buff, strlen(buff), 0);
							bzero(&buff, sizeof(buff));


							pclose(fp);
							bzero(&text_buffer, sizeof(text_buffer));

						}

						else if (strcmp(text_buffer, "get") == 0) {
							FileSend(newSocket);
							bzero(&text_buffer, sizeof(text_buffer));
						}

						else if (strcmp(text_buffer, "put") == 0) {
							FileReceive(newSocket);
							bzero(&text_buffer, sizeof(text_buffer));
						}

						else {
							snprintf(text_buffer, sizeof(text_buffer), "Server does not understand");
							write(newSocket, text_buffer, sizeof(text_buffer));
							bzero(&text_buffer, sizeof(text_buffer));
						}

					}
			}
			close(newSocket);
		}
	}
