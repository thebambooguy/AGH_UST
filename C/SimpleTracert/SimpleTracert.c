//Imię i nazwisko: Patryk Szeląg
//Nr Indeksu: 283335
//Nazwa projektu: SimpleTracert
//Opis: Napisany program prezentuje uproszczone działanie programu jakim jest tracert. Został on zrealizowany na gniaździe
//surowym, tak by mógl wysłać pakiet z komunikatem "Echo Request", a potem mógł pakiet z komunikatem "Echo Reply". Najważniejszą
//rzeczą jest zwiekszające się pole TTL na każdym "przystanku", dzięki czemu zbudowany własnoręcznie pakiet odkyrwa kolejne routery
//na swojej drodze Jeżeli taki komunikat osiągie swoje przeznaczenie, to zawsze zostanie odesłana odpowiedź "Echo Reply".
//zięki takiemu rozwiązaniowi nie trzeba polegać na założeniu związanymi z wysokimi numerami portów dla datagramów UDP oraz można
//ominąć niektóre firewalle. Przed uruchomieniem programu należy zmienić źrodłowy adres IP, oraz należy pamiętać o uruchamianiu
//programu z opcją "sudo", gdyz aby utworzyć gniazdo surowe i wykorzystać do tego flagę IP_HDRINCL należy skorzystać z praw root'a.
//Adres docelowy należy dopisać jako argument uruchamianego programu.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <errno.h>

#define SA (struct sockaddr*)


//sposób liczenia internetowej sumy kontrolnej zdefiniowany jest w dokumencie
//RFC 1071. Poniżej jedna z mozliwych implementacji.

unsigned short csum (unsigned short *buf, int nwords)
{
  	unsigned long sum;
  	for (sum = 0; nwords > 0; nwords--)
    	sum += *buf++;
  		sum = (sum >> 16) + (sum & 0xffff);
  		sum += (sum >> 16);
  		return ~sum;
}


int main(int argc, char *argv[]){


	int sockfd;
	int hop = 0; // skoki TTL, będzie się zwiększał co każdy "przystanek"

	sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP); //utworzenie gniazda surowego, który umożliwi wysłanie i odbiór komunikatu ICMP
	if( sockfd < 0)
	{
		fprintf(stderr,"socket error : %s\n", strerror(errno));
		return 1;
	}

	const int on = 1; //setsockopt potrzebuje tam wskaźnika potem i 1 żeby włączyć

	if( setsockopt ( sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
		printf("Cannot set HDRINCL! \n");


	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	inet_pton( AF_INET, argv[1], &(addr.sin_addr));

	char datagram[4096]; //mój pakiet(bufor) który będę wysyłał na doecelowy adres; będzie zawierał ip header i icmp header
	struct ip *ip_header = (struct ip *) datagram;
	struct icmphdr *icmp_header = (struct icmphdr *) (datagram + 20); //buduję część ICMP, przesuwam się za nagłówek IP w moim buforze

	while(1)
	{

			//Budowa nagłówka IP - total ip header length - 20 bytes

			ip_header->ip_v = 4;  	    //ip version, we use IPv4
			ip_header->ip_hl = 5; 		//IHL - Internet Header Length has 4 bits, which is the number of 32-bit words. The minimal value indicates a length of 5*32 bits = 20 bytes
			ip_header->ip_tos = 0;	    //type of service, 0x00 is normal
			ip_header->ip_len = 20 + 8; //20 bytes of IP header + 8 bytes of ICMP header, entire packet size in bytes
			ip_header->ip_id = 10000;
			ip_header->ip_off = 0;
			ip_header->ip_ttl = hop; 									//TTL - Time to Live is the amount of hops
			ip_header->ip_p = IPPROTO_ICMP; 							//the protocol we used in data portion of te IP datgram
			inet_pton( AF_INET, "10.0.2.15", &(ip_header->ip_src)); 	//source IP
			inet_pton( AF_INET, argv[1], &(ip_header->ip_dst));			//destination IP
			ip_header->ip_sum = csum ((unsigned short *) datagram, 9); //checksum


			//Budowa nagłówka ICMP - total ICMP heade length: 8 bytes

			icmp_header->type = ICMP_ECHO; 	//Type 8 - jest to tzw. ECHO REQUEST
			icmp_header->code = 0;
			icmp_header->un.echo.id = 0;
			icmp_header->un.echo.sequence = hop + 1;
			icmp_header->checksum = csum ((unsigned short*) (datagram+20),4);


			sendto(sockfd, datagram, sizeof(struct ip) + sizeof(struct icmphdr), 0, SA & addr, sizeof addr ); //wysyłam zbudowany przez siebie pakiet

			char rdatagram[4096] = {0}; //bufor odbiorczy dla komunikatu ECHO_RESPONSE
			struct sockaddr_in raddr;

			socklen_t len = sizeof ( struct sockaddr_in);
			recvfrom( sockfd, rdatagram, sizeof(rdatagram), 0, SA & raddr, &len ); //odbieram pakiet od routera

			struct icmphdr *ricmp_header = (struct icmphdr *) (rdatagram + 20);

			// Jeśli typ wiadomości jest inny tylko niż ECHO RESPONSE, to go printuje, natomiast jeśli dostałem odpowiedź na "swojego pinga" to kończę program.
			if( ricmp_header->type != 0) {
				printf("hop limit: %d Address: %s \n", hop, inet_ntoa(raddr.sin_addr));
			}
			else{
					printf("Reached destination: %s with hop limit: %d \n", inet_ntoa(raddr.sin_addr), hop);
					exit(0);
				}

			hop++; //zwiększam pole TTL po dojściu do kolejnego routera


	}

	//return 0;
}
