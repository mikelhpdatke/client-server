
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_address, '0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(5049);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len); // gan va rang buoc cong , port
    listen(server_sockfd, 1000);                                         //cho phep ket noi toi da 1000 ;
    while (1)
    {
        char ch[256];
        printf("Server waitting\n");
        // cho va chap nhan  ket noi;
        client_sockfd = accept(server_sockfd, (struct sockaddr *)NULL, NULL);
        char ch1;

        //FILE *f ;
        //f=fopen("khach.txt","wt");
        char s[256];
        //bzero(s,256);

        //bzero(ch,256);
        memset(ch, 0, sizeof(ch));
        int n = read(client_sockfd, ch, sizeof(ch) - 1);
        ch[n] = 0;
        //strcat(ch," > a.out");
        if (n < 0)
            write(client_sockfd, "ERROR reading from socket\n", 26);
        printf("Here is the message: %s\n", ch);

        FILE *f = popen(ch, "r");
        char sendBuff[1024];
        /*
        c=fgetc(f);
        if (c==EOF) break;
        n=write(client_sockfd,&c,1);
        }
        write(client_sockfd,"complete",8);
        pclose(f);

        }
        close(client_sockfd);
        close(server_sockfd);

        return 0;*/
        if (f == NULL)
        {
            strcpy(sendBuff, "Can not execute this command!\n");
            write(client_sockfd, sendBuff, strlen(sendBuff));
        }
        else
        {
            while (fgets(sendBuff, sizeof sendBuff, f) != NULL)
            {
                write(client_sockfd, sendBuff, strlen(sendBuff));
            }
        }

        strcpy(sendBuff, "Complete_tranfer!\n");
        write(client_sockfd, sendBuff, strlen(sendBuff));
    }
    //ch="q";
    //write(client_sockfd,ch,sizeof(ch));
}
