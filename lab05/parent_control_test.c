#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define SITE1 ((unsigned char *)"google.com")
#define SITE2 ((unsigned char *)"youtube.com")
#define SITE3 ((unsigned char *)"gmail.com")

#define __NR_parent_control_change 473
#define __NR_parent_control_check 474

void verify_check_ret(unsigned char *url, bool expected)
{
    bool bret = syscall(__NR_parent_control_check, url);

    if (!bret)
    {
        printf("Poggers! O acesso ao site %s está permitido!\n", url);
    }
    else
    {
        printf("Noggers... o acesso ao site %s não está permitido :(\n", url);
    }

    if (bret == expected)
    {
        printf(">>> Retorno condiz com o esperado.\n");
    }
    else
    {
        printf(">>> Retorno não condiz com o esperado.\n");
    }
    printf("\n");
}

void teste_lista_vazia()
{
    // Teste inicial: todos os sites devem estar bloqueados, pq nenhum deles foi adicionado à lista de sites permitidos.
    verify_check_ret(SITE1, false);
    verify_check_ret(SITE2, false);
    verify_check_ret(SITE3, false);
}

void teste_remover_sites_nao_existentes()
{
    // Teste após tentar remover sites sem eles de fato existirem na lista.
    syscall(__NR_parent_control_change, 1, SITE1);
    syscall(__NR_parent_control_change, 1, SITE2);
    syscall(__NR_parent_control_change, 1, SITE3);

    //verify_check_ret(SITE1, false);
    //verify_check_ret(SITE2, false);
    //verify_check_ret(SITE3, false);

    printf(">>> Tentativas de remoção foram feitas e nada quebrou!\n");
}

void teste_adicionar_sites()
{
    // Teste após adicionar os sites à lista de sites permitidos: todos os sites devem estar liberados.
    syscall(__NR_parent_control_change, 0, SITE1);
    syscall(__NR_parent_control_change, 0, SITE2);
    syscall(__NR_parent_control_change, 0, SITE3);

    verify_check_ret(SITE1, true);
    verify_check_ret(SITE2, true);
    verify_check_ret(SITE3, true);
}

void teste_adicionar_sites_existentes()
{
    // Teste após tentar adicionar sites que já existem na lista de sites permitidos: todos os sites devem continuar liberados.
    syscall(__NR_parent_control_change, 0, SITE1);
    syscall(__NR_parent_control_change, 0, SITE2);
    syscall(__NR_parent_control_change, 0, SITE3);

    //verify_check_ret(SITE1, true);
    //verify_check_ret(SITE2, true);
    //verify_check_ret(SITE3, true);

    printf(">>> Tentativas de adicionar duplicatas foram feitas e nada quebrou!\n");
}

void teste_remover_sites_existentes()
{
    // Teste após remover os sites da lista de sites permitidos: todos os sites devem estar bloqueados.
    syscall(__NR_parent_control_change, 1, SITE1);
    syscall(__NR_parent_control_change, 1, SITE2);
    syscall(__NR_parent_control_change, 1, SITE3);

    verify_check_ret(SITE1, false);
    verify_check_ret(SITE2, false);
    verify_check_ret(SITE3, false);
}

int main()
{
    printf("\n\n---- Teste LISTA VAZIA.\n");
    teste_lista_vazia();

    printf("\n\n---- Teste REMOVER SITES NÃO EXISTENTES.\n");
    teste_remover_sites_nao_existentes();
    
    printf("\n\n---- Teste ADICIONAR SITES.\n");
    teste_adicionar_sites();

    printf("\n\n---- Teste ADICIONAR SITES JÁ EXISTENTES.\n");
    teste_adicionar_sites_existentes();

    printf("\n\n---- Teste REMOVER SITES EXISTENTES.\n");
    teste_remover_sites_existentes();
    
    return 0;
}