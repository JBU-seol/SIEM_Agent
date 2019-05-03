#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char * argv[])
{
    while(1){
        int num;
        char ipscan_buf[100]="/usr/bin/ipscan -s -o /opt/splunk/var/data/data.xml -f:range ";
        strncat(ipscan_buf,argv[1],16);
        strncat(ipscan_buf,"  ",1);
        strncat(ipscan_buf,argv[2],16);
        char nmap_buf[100]="nmap -sS -p- -T5 -v --open -oX /opt/splunk/var/data/data.xml ";
        unsigned char iparr[16];
        printf("\nWeakness Check through Splunk\n");
        printf("[1]:IP Scan\n");
        printf("[2]:Port Scan\n");
        printf("[Default]:EXIT\n");
        printf("Choose Number :");
        scanf("%d",&num);

        switch(num){
        case 1:
            printf("starting ip scan .. \n");
            printf("%s\n",ipscan_buf);
            sleep(1);
            system(ipscan_buf);
            break;
        case 2:
            printf("Insert IP :");
            scanf("%s",iparr);
            strncat(nmap_buf,(char *)iparr,16);
            printf("%s\n",nmap_buf);
            printf("Starting port scan .. \n");
            sleep(1);
            system(nmap_buf);
            break;
        default:
            printf("End .. !!\n");
            return 0;
        }
    }
}
