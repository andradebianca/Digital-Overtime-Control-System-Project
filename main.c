#include <stdio.h>
#include <stdlib.h>

int main()
{
	
    int resposta, respostagestor;
    
    
    do {
    printf("<===== REGISTRO DE HORAS EXTRAS ====>\n");
    printf("(1) Solicitar hora extra\n(2) Relatorio\n(3) Sair\n-> ");
    scanf("%d", &resposta);
    
	    if (resposta != 1 && resposta != 2 && resposta != 3)
	    {
	        printf("Respota invalida, tente novamente.\n");
	        system("sleep 1");
	        system("cls");
	    }
	    
	} while (resposta != 1 && resposta != 2 && resposta != 3 );
    
    switch (resposta)
    {
        case 1:
        
            do {
            	system("cls");
                printf("=== GESTOR === \n");
                printf("Liberar hora extra diaria?\n(1) Sim    (2) Nao\n-> ");
                scanf("%d", &respostagestor);
        
                if (respostagestor == 1)
                {
                    printf("Horas extras liberadas!\n");
                }   
                
                else if (respostagestor == 2)
                {
                    printf("Horas extras negadas!\n");
                }
                
                else
                {
                    printf("Opcao invalida! Tente novamente.\n");
                    system("sleep 1");
                }
        
                system("cls");
            } while (respostagestor != 1 && respostagestor != 2);
        break;
        
        case 2:
        break;
        
        case 3:
            printf("Programa finalizado.");
            exit(EXIT_SUCCESS);
        break;
    }

    return 0;
}