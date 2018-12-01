#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    while (1){
        int sockfd;                 // ID xac dinh socket
        int len;                    // do dai address;
        struct sockaddr_in address; //  dinh nghia 1 socket xuat nhap  theo kieu file
        int result;
        char ch[300];
        char ch1;
        sockfd = socket(AF_INET, SOCK_STREAM, 0); // tao socket co kieu xuat nhap file (AF_UNIX),
        // luon duy tri ket noi de kiem tra xem client va sever co nhan duoc du lieu hay ko(SOCK_TREAM), trong vung giao thuc mang AF_INET goi la TCP, sock_dgram : UDP(ko duy tri ket noi)
        //0 la kieu protocol thuong set default la 0
        address.sin_family = AF_INET; // phuong thuc ket noi
        address.sin_addr.s_addr = inet_addr(argv[1]);
        address.sin_port = htons(5049);
        len = sizeof(address);
    
        result = connect(sockfd, (struct sockaddr *)&address, len); // ket noi sockaddr co 2 kieu la sockaddr_un or sockaddr_in
        if (result == -1)
        {
            perror("opps:client1 problem");
            exit(1);
        }

        printf("Please enter the message: ");
        bzero(ch, 256);
        fgets(ch, 255, stdin);
        if (ch[0] == '1'){
            printf("******");
            char cm[] = "sudo tcpdump -i any -c 200 -w - | nc -l -p 2000";
            int n = write(sockfd, cm, strlen(cm));
            if (n < 0)
                printf("ERROR writing to socket\n");
            int a = system("nc 192.168.0.108 2000 > log.pcap");
            printf("%d", a);
            printf("run cmd done!!!!\n");
            continue;
        }
        int n = write(sockfd, ch, strlen(ch));
        if (n < 0)
            printf("ERROR writing to socket\n");
        //bzero(ch,256);
        //bzero(ch,256);
        char nhan[1024];
        char c = 'a';
        while (c != '!')
        {
            read(sockfd, &c, 1);
            printf("%c", c);
        }

        //if (n < 0)
        //{
        //break;
        //}
        //  printf("%s\n",ch);
        //}
	    printf("\n\n");
        close(sockfd);
    }
}

