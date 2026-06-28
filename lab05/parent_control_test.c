#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define SITE1 ((unsigned char *) "google.com")
#define SITE2 ((unsigned char *) "youtube.com")
#define SITE3 ((unsigned char *) "gmail.com")

#define __NR_parent_control_change 473
#define __NR_parent_control_check 474

void verify_check_ret(unsigned char *url, bool expected){
    bool bret = syscall(__NR_parent_control_check, url);

    if(bret){
        printf("Poggers! O acesso ao site %s está permitido!\n", url);
    } else {
        printf("Noggers... o acesso ao site %s não está permitido :(\n", url);
    }

    if(bret == expected){
        printf("Retorno condiz com o esperado.\n");
    } else {
        printf("Retorno não condiz com o esperado.\n");
    }
    printf("\n");
}

int main(){
    verify_check_ret(SITE1, false);
    verify_check_ret(SITE2, false);
    verify_check_ret(SITE3, false);

    syscall(__NR_parent_control_change, 0, SITE1);
    syscall(__NR_parent_control_change, 0, SITE2);
    syscall(__NR_parent_control_change, 0, SITE3);

    verify_check_ret(SITE1, true);
    verify_check_ret(SITE2, true);
    verify_check_ret(SITE3, true);

    syscall(__NR_parent_control_change, 1, SITE1);
    syscall(__NR_parent_control_change, 1, SITE2);
    syscall(__NR_parent_control_change, 1, SITE3);

    verify_check_ret(SITE1, false);
    verify_check_ret(SITE2, false);
    verify_check_ret(SITE3, false);

    return 0;
}