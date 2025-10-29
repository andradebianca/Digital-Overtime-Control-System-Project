#include <stdio.h>
#include <stdlib.h>
#define MAX_HORAS_EXTRAS 176

// Declaração de Função

void verificar_horas_extras(float horas_feitas, float *horas_faltantes, int *atingiu_limite) 
{
	if (horas_feitas < 0) horas_feitas = 0;
	*atingiu_limite = (horas_feitas >= MAX_HORAS_EXTRAS) ? 1 : 0;
    *horas_faltantes = (*atingiu_limite) ? 0 : (MAX_HORAS_EXTRAS - horas_feitas);
}



int main()
{
    float horas_feitas, horas_faltantes;
    int limite_atingido, resposta, respostagestor, entradafuncionario, saidafuncionario;
    
    do {
    printf("<===== REGISTRO DE HORAS EXTRAS ====>\n");
    printf("(1) Solicitar hora extra\n(2) Relatorio\n(3) Controle de Horas\n(4) Sair\n-> ");
    scanf("%d", &resposta);
    if (resposta != 1 && resposta != 2 && resposta != 3 && resposta != 4)
    {
        printf("Opcao invalida! Tente novamente.\n");
        system("sleep 1");
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
                    printf("Horario de inicio:");
                    scanf("%d", &entradafuncionario);
                    printf("Horario de Saida:");
                    scanf("%d", &saidafuncionario);
                    
                    
                }   
                
                else if (respostagestor == 2)
                {
                    printf("Horas extras negadas!\n");
                    system("sleep 1");
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
            printf("Quantas horas extras você ja fez este mes? ");
            scanf("%f", &horas_feitas);
        
            verificar_horas_extras(horas_feitas, &horas_faltantes, &limite_atingido);
        
            if (limite_atingido) 
            {
                printf("Limite de horas extras atingido! (%d h)\n", MAX_HORAS_EXTRAS);
            } 
            
            else 
            {
                printf("Ainda faltam %.1f horas para atingir o limite de %d h\n", horas_faltantes, MAX_HORAS_EXTRAS);
            }
        break; 
        
        case 4:
            printf("Programa finalizado.");
            exit(EXIT_SUCCESS);
        break;
    }
    

    

    return 0;
}