#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* nmapFunction(void* buf){
    int i=0;
    while(1){
        i++;
        printf("NMAP %d \n",i);
        system((char*)buf);
        sleep(60);
        printf("[1]: Active Host Scanning \n");
        printf("[2]: Regular Port Scanning \n");
        printf("[3]: IDS Starting \n");
        printf("[0 & Default]: EXIT \n");
        printf("Choose Number :");
    }
}

int main(int argc,char * argv[])
{
    if(argc != 3)
        return 0;
    FILE *p;
    p=fopen("/opt/splunk/commandfile.txt","r");
    int num=0;
    char ipscan_buf[80];
    char nmap_buf[80];
    char snort_buf[100];
    unsigned char iparr[16];
    for(int i=0;i<3;i++)
    {
        switch(i){
        case 0:
            fgets(ipscan_buf,80,p);
            strtok(ipscan_buf,"\n");
            break;
        case 1:
            fgets(nmap_buf,80,p);
            strtok(nmap_buf,"\n");
            break;
        case 2:
            fgets(snort_buf,100,p);
            strtok(snort_buf,"\n");
        default:
            continue;
        }
    }
    pthread_t nmapThread;
    while(1){

        printf("\n-------------------- Splunk & Network Vulnerabilities ----------------------\n");
        printf("[1]: Active Host Scanning \n");
        printf("[2]: Regular Port Scanning \n");
        printf("[3]: IDS Starting \n");
        printf("[0 & Default]: EXIT \n");
        printf("Choose Number :");
        scanf("%d",&num);

        switch(num){
        case 1:
            printf("starting ip scan .. \n");
            strncat(ipscan_buf,argv[1],16);
            strncat(ipscan_buf,"  ",1);
            strncat(ipscan_buf,argv[2],16);
            //printf("%s\n",ipscan_buf);
            sleep(1);
            system(ipscan_buf);
            break;
        case 2:
            printf("Insert IP :");
            scanf("%s",iparr);
            strncat(nmap_buf,(char *)iparr,16);
            //printf("%s\n",nmap_buf);
            printf("Port Scan Starting \n");
            if( pthread_create(&nmapThread,NULL,nmapFunction,(void*)nmap_buf)){
                printf("Thread Error \n");
                return 0;
            }
            else {
                printf("Thread Start \n");
            }
            break;
        case 3:
                    printf("Starting snort ..\n");
                    //printf("%s\n",snort_buf);
                    sleep(3);
                    system(snort_buf);
            break;
        default:
            printf("----------------------- Thank you --------------------------\n");
            return 0;
        }
        sleep(1);
    }
}
