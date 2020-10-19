#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/reboot.h>
#include<sys/syscall.h>
#include<string.h>
#include<stdint.h>
uint8_t partitionOK(char test[]){
    for(int i=0;i<strlen(test);i++){
        if(test[i]<'0' || test[i]>'9'){
            return 0;
        }
    }
    return 1;
}
void printhelp(){
    printf("Help menu\n");
    printf("--help or -h to display help\n");
    printf("--patition <pid> or -p <pid> to boot to partition, example mmcblk0p1 will be -p 1 or --partition 1\n");
}
int  main(int argc, char ** args){
	//sync();
    // -p 1 --partition 1 --help -h
    char partition[10]="";
    if(argc<=1){
        printf("Needs an argument to work, try argument --help\n");
    }
    else{
        for(int i=1;i<argc;i++){
            if(strcmp(args[i],"--help")==0){
                printhelp();
            }
            else if(strcmp(args[i],"-h")==0){
                printhelp();
            }
            else if(strcmp(args[i],"-p")==0){
                if(strlen(args[i+1])<9){
                    if(argc>i+1){
                        strcpy(partition,args[i+1]);
                        i++;
                    }
                    else{
                        printf("-p requires an argument\n");
                    }
                }
                else{
                    printf("-p parameter too large.\n");
                }
            }
            else if(strcmp(args[i],"--partition")==0){
                if(strlen(args[i+1])<9){
                    if(argc>i+1){
                        strcpy(partition,args[i+1]);
                        i++;
                    }
                    else{
                        printf("--partition requires an argument\n");
                    }
                }
                else{
                    printf("--partition parameter too large.\n");
                }
            }
//             printf("Argument is %s\n", args[1] );
        }
    }
    if(strcmp(partition,"")!=0){
        printf("Partition detected as %s\n",partition);
        //printf("Partition test status: %d\n",partitionOK(partition));
        if(partitionOK(partition)){
            printf("Syncing disk...\n");
            sync();
            printf("Rebooting...\n");
            syscall(SYS_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_RESTART2, "8");
        }
        else{
            printf("Invalid partition number!\n");
        }
    }
	//syscall(SYS_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_RESTART2, "8");
}
