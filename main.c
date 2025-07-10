#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "./include/menus.h"
#include "./include/types.h"
#include "./include/cadastros.h"
#include "./include/relatorios.h"
#include "./include/arquivos.h"
#include "./include/consultas.h"
#include "./include/utils.h"

#define INICIO  1
#define FIM     2
#define SAIR    0

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Numero de parametros errado\n");
        printf("Uso: ./sistema-rh (nome_arquivo.bin) inicio ou fim \n");
       
        return 1;
    }

    char *nome_arq_bin = argv[1];
    int insercao = 0;

    if (strcmp(argv[2], "inicio") == 0) {
        insercao = INICIO;
    } else if (strcmp(argv[2], "fim") == 0) {
        insercao = FIM;
    } else {
        printf("insercao errada.\n");
        printf("Use 'inicio' para inserir no comeco da lista ou 'fim' para inserir no final.\n");
        return 1;
    }
    
  

    uint8_t opcao, sub_menu;
    no_t *aux = NULL;
    float salario_minimo, salario_maximo;
    string nome_arq, nome_pessoa, funcao;
    char resposta;
    data_t data;

    lista_t lista_rh;

    // Criar a lista
    inicializa_lista_rh(&lista_rh);

    // Carrega dados arquivo
    ler_registros_rh_arquivo_binario(nome_arq_bin, &lista_rh);

    ordenar_em_ordem_alfabetica(&lista_rh);


    do {
        opcao = menu_principal();

        switch (opcao) {

            case 1: 
                    do {
                        sub_menu = menu_cadastros();
                        switch (sub_menu) {
                            
                            case 1: break;
                            
                            case 2: aux = novo_registro_rh();
                                    if(insercao == INICIO) {
                                         insere_registro_inicio_rh(aux, &lista_rh);
                                    } else {
                                        insere_registro_fim_rh(aux, &lista_rh);
                                    }
                                    break;

                            case 3: 
                                    ordenar_em_ordem_alfabetica(&lista_rh);    
                                    break;

                            case 4: limpar_tela();
                                    printf("Qual o nome do funcionario? ");
                                    fgets(nome_pessoa, T_STR, stdin);
                                    retirar_enter(nome_pessoa);
                                    to_upper(nome_pessoa);

                                    aux = consulta_pessoa_por_nome(nome_pessoa, lista_rh.cabeca);

                                    if (aux) {
                                        mostrar_dados_registro_rh(aux);
                                        printf("\nConfirma a inativacao do funcionario (S/N)? ");
                                        scanf("%c", &resposta);
                                        if (resposta == 'S' || resposta == 's') {
                                            printf("Informe a data do desligamento: ");
                                            scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
                                            inativar_funcionario(aux, data);
                                        }
                                    }
                                    else {
                                        printf("%s nao esta cadastrado!\n", nome_pessoa);
                                        msg_press_enter();
                                    }
                                    break;


                            case 5: limpar_tela();
                                    
                                    printf("Qual funcionario vc quer excluir? ");
                                    fgets(nome_pessoa, T_STR, stdin);
                                    
                                    retirar_enter(nome_pessoa);
                                    to_upper(nome_pessoa);

                                    aux = consulta_pessoa_por_nome(nome_pessoa, lista_rh.cabeca);

                                    if (aux) {
                                        mostrar_dados_registro_rh(aux);
                                        printf("\nConfirma para excluir digite a letra /s/ e para nao excluir digite a letra /n/? ");
                                        scanf("%c", &resposta);
                                        getchar();
                                        if (resposta == 's') {
                                            excluir_registro_rh(aux, &lista_rh);
                                            printf("\nexcluido\n");
                                            msg_press_enter();
                                        }
                                    }
                                    else {
                                        printf("%s nao esta cadastrado em nosso sistema\n", nome_pessoa);
                                        msg_press_enter();
                                    }
                                    break;
                        }

                    } while (sub_menu != SAIR);

                    break;

            case 2: do {
                        sub_menu = menu_relatorios();
                        switch (sub_menu) {
                                    
                            case 1: break;

                            case 2: listar_todos_registros_rh(lista_rh.cabeca);
                                    break;
                            
                            case 3:                                 

                                    printf("\n=== RELATORIO DE FAIXA SALARIAL ===\n");
                                    printf("Digite o salario minimo: ");
                                    scanf("%f", &salario_minimo);

                                    printf("Digite o salario maximo: ");
                                    scanf("%f", &salario_maximo);
                                    getchar();
                                    if(salario_minimo > salario_maximo)
                                    {
                                        printf("Erro, salario minimo maior que o maximo!\n");
                                        msg_press_enter();
                                        break;
                                    }
                                    
                                    relatorio_faixa_salarial(lista_rh.cabeca, salario_minimo, salario_maximo);
                                    msg_press_enter();
                                    break;
                                
                            case 4: mostrar_funcionarios_ativos(lista_rh.cabeca);
                                    break;

                            case 5: limpar_tela();
                                    printf("Qual a funcao? ");
                                    fgets(funcao, T_STR, stdin);
                                    retirar_enter(funcao);
                                    to_upper(funcao);
                                    listar_funcionarios_por_funcao(funcao, lista_rh.cabeca);
                                    break;        
                            
                        }

                    } while (sub_menu != SAIR);
                    break;

            case 3: do {
                        sub_menu = menu_consultas();
                        switch (sub_menu) {
                            
                            case 1: limpar_tela();
                                    printf("Qual o nome do funcionario? ");
                                    fgets(nome_pessoa, T_STR, stdin);
                                    retirar_enter(nome_pessoa);
                                    to_upper(nome_pessoa);

                                    aux = consulta_pessoa_por_nome(nome_pessoa, lista_rh.cabeca);

                                    if (aux) {
                                        mostrar_dados_registro_rh(aux);
                                        msg_press_enter();
                                    }
                                    else {
                                        printf("%s nao esta cadastrado!\n", nome_pessoa);
                                        msg_press_enter();
                                    }

                            }                         

                        
                    } while (sub_menu != SAIR);
            
                    break;

            case 4: do {
                        sub_menu = manipulacao_arquivos();

                        switch (sub_menu) {

                            case 1: limpar_tela();
                                    msg_cabecalho("Exportar dados para arquivo do tipo texto\n");
                                    printf("Qual o nome do arquivo de saida? ");
                                    fgets(nome_arq, T_STR, stdin);
                                    retirar_enter(nome_arq);

                                    exportar_dados_para_arquivo_texto(nome_arq, lista_rh.cabeca);

                                    break;

                            case 2: limpar_tela();
                                    msg_cabecalho("Exportar dados para arquivo do tipo texto\n");
                                    printf("Qual o nome do arquivo de saida (extensao .csv)? ");
                                    fgets(nome_arq, T_STR, stdin);
                                    retirar_enter(nome_arq);
                                    exportar_dados_para_arquivo_csv(nome_arq, lista_rh.cabeca);
                                    break;
                        }

                    } while (sub_menu != SAIR);
        }


    } while (opcao != SAIR);

    if (!is_lista_rh_vazia(lista_rh.cabeca)) {
        salvar_registros_rh_arquivo_binario(nome_arq_bin, lista_rh.cabeca);
    }

    return 0;
}
