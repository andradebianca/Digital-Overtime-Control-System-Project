#include <stdio.h>
#include <stdlib.h>

// Declaração de Função
int acumularhorasfuncao(int a, int b)
{
	int horasextrascalculo;
	horasextrascalculo = abs(a - b);
	return horasextrascalculo;
}

int main()
{
    int resposta, respostagestor, entradafuncionario, saidafuncionario, acumulohorasextras;
    
    do {
	    printf("<===== REGISTRO DE HORAS EXTRAS ====>\n");
	    printf("(1) Solicitar hora extra\n(2) Relatorio\n(3) Controle de Horas\n(4) Sair\n-> ");
	    scanf("%d", &resposta);
	    if (resposta != 1 && resposta != 2 && resposta != 3 && resposta != 4)
	    {
	        printf("Opcao invalida! Tente novamente.\n");
	        system("pause");
	        system("cls");
	    }
    } while (resposta != 1 && resposta != 2 && resposta != 3 && resposta != 4);
    
    
    switch (resposta)
    {
        case 1:
        	system("cls");
            do {
                printf("=== GESTOR === \n");
                printf("Liberar hora extra diaria?\n(1) Sim    (2) Nao\n-> ");
                scanf("%d", &respostagestor);
        
                if (respostagestor == 1)
                {	
                	system("cls");
                	printf("Horario de Entrada: ");
                	scanf("%d", &entradafuncionario);
                	printf("Horario de Saida:");
                	scanf("%d", &saidafuncionario);
                	
                	acumulohorasextras = acumularhorasfuncao(entradafuncionario, saidafuncionario);
                	
                	printf("Horas extras %d", acumulohorasextras );
                    system("pause");
                }   
                
                else if (respostagestor == 2)
                {
                    printf("Horas extras negadas!\n");
                    system("pause");
                }
                
                else
                {
                    printf("Opcao invalida! Tente novamente.\n");
                    system("pause");
                }
        
                system("cls");
            } while (respostagestor != 1 && respostagestor != 2);


        break;
        
        
        
        
        case 2:
        break;
        
        case 3:

        break; 
        
        case 4:
            printf("Programa finalizado.");
            exit(EXIT_SUCCESS);
        break;
    }
    

    

    return 0;
}