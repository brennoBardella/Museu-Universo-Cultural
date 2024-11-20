#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

void limpar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (c == EOF) {
        clearerr(stdin);
        while (getchar() != '\n');
    }
}
void gerarCodigoTicket(char *codigo, int tamanho) {
    const char caracteresPermitidos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int tamanhoCaracteres = strlen(caracteresPermitidos);

    for (int i = 0; i < tamanho; i++) {
        int indice = rand() % tamanhoCaracteres;
        codigo[i] = caracteresPermitidos[indice];
    }
    codigo[tamanho] = '\0';
}
void salvarQuantidadesIngressos(int quantidade_olimpiadas, int quantidade_copa, int quantidade_arte, int quantidade_santos) {
    FILE *arquivo = fopen("quantidades_ingressos.csv", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "Olimpiadas:,Copa do Mundo:,Arte Moderna:,Santos Dumont:\n");
        fprintf(arquivo, "%d, %d, %d, %d", quantidade_olimpiadas, quantidade_copa, quantidade_arte, quantidade_santos);
        fclose(arquivo);
    }
}
void carregarQuantidadesIngressos(int *quantidade_olimpiadas, int *quantidade_copa, int *quantidade_arte, int *quantidade_santos) {
    FILE *arquivo = fopen("quantidades_ingressos.csv", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "Olimpiadas:,Copa do Mundo:,Arte Moderna:,Santos Dumont:\n%d, %d, %d, %d", quantidade_olimpiadas, quantidade_copa, quantidade_arte, quantidade_santos);
        fclose(arquivo);
    }
}
void salvarTicket(char *codigo, int quantidadeVendida, char *cpf) {
    FILE *arquivo = fopen("tickets.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    if (tamanho == 0) {
        fprintf(arquivo, "Ticket:,Quantidade:,CPF:\n");
    }
    fprintf(arquivo, "%s,%d,%s\n", codigo, quantidadeVendida, cpf);

    fclose(arquivo);
}
int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(NULL));
    int opcao;
    int ingressos_100_arte_moderna = 100;
    int ingressos_150_santos_dumont = 100;
    int ingressos_olimpiadas_paris_2024 = 100;
    int ingressos_copa_mundo_2026 = 100;
    float valor_ingresso_inteira = 10.0;
    float valor_ingresso_meia = 5.0;
    float valor_total;
    int metodo_pagamento;
    carregarQuantidadesIngressos(&ingressos_olimpiadas_paris_2024, &ingressos_copa_mundo_2026, &ingressos_100_arte_moderna, &ingressos_150_santos_dumont);

    while (1) {
        limpar();
        printf("\tMuseu Universo Cultural\n");
        printf("1- 100 anos da semana da arte moderna\n");
        printf("2- 150 anos de Santos Dumont\n");
        printf("3- Jogos Olímpicos de Paris 2024\n");
        printf("4- Copa do Mundo 2026\n");
        printf("5- Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        int quantidade_inteira;
        int quantidade_meia;
        int quantidade_isencao;
        salvarQuantidadesIngressos(ingressos_olimpiadas_paris_2024, ingressos_copa_mundo_2026, ingressos_100_arte_moderna, ingressos_150_santos_dumont);

        if (opcao < 1 || opcao > 5) {
            continue;
        }

        switch (opcao) {
            case 1:
                limpar();
                printf("--100 anos da semana da arte moderna--\n\n");
                printf(" A arte contemporânea, que se estende por aproximadamente um século de evolução\n"
                       "artística do final do século XIX até meados do século XX, se destaca pela multiplicidade\n"
                       "de estilos, movimentos e experimentações. Englobando correntes como impressionismo,\n"
                       "pós-impressionismo, cubismo, futurismo, expressionismo, dadaísmo, surrealismo, abstracionismo,\n"
                       "entre outras, a arte moderna foi marcada por renomados artistas como Picasso,\n"
                       "Van Gogh, Duchamp e Dalí. Esses artistas desafiaram tradições, exploraram novas formas\n"
                       "de expressão e contribuíram para moldar a arte contemporânea. Esse período reflete as\n"
                       "mudanças sociais, políticas e tecnológicas da época, destacando-se como uma era de\n"
                       "inovação e diversidade nas artes.\n\n");
                printf("Ingressos disponíveis: %d\n", ingressos_100_arte_moderna);
                if (ingressos_100_arte_moderna == 0) {
                    printf("Ingressos esgotados!\n");
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                    }
                }
                printf("Escolha o tipo de ingresso:\n");
                printf("1- Inteira (R$%.2f)\n", valor_ingresso_inteira);
                printf("2- Meia (R$%.2f)\n", valor_ingresso_meia);
                printf("3- Isenção (Apenas para pessoas acima de 60 anos e crianças abaixo de 6 anos)\n");
                printf("4- Voltar ao menu inicial\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                limparBufferEntrada();

                if (opcao < 1 || opcao > 4) {
                    continue;
                }

                if (opcao == 4) {
                    break;
                }

                if (opcao == 1) {
                    limpar();
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_inteira);
                    limparBufferEntrada();
                    if (quantidade_inteira <= 0 || quantidade_inteira > ingressos_100_arte_moderna) {
                    limpar();
                    printf("Quantidade de ingressos de entrada inteira inválida ou esgotada.\n");
                    printf("Ingressos disponíveis: %d\n", ingressos_100_arte_moderna);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF válido\n");
                    printf("Escolha o método de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cartão de Crédito\n");
                    printf("3- Cartão de Débito\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_inteira * valor_ingresso_inteira;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket é: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_inteira, cpf);
                        system("pause");

                        ingressos_100_arte_moderna -= quantidade_inteira;
                        }
                    }
                } else if (opcao == 2) {
                    limpar();
                    printf("ATENÇÃO: Apresentação de documento obrigatória.\n");
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_meia);
                    limparBufferEntrada();
                    if (quantidade_meia <= 0 || quantidade_meia > ingressos_100_arte_moderna) {
                    limpar();
                    printf("Quantidade de ingressos de meia entrada inválida ou esgotada.\n");
                    printf("Ingressos disponíveis: %d\n", ingressos_100_arte_moderna);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF válido\n");
                    printf("Escolha o método de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cartão de Crédito\n");
                    printf("3- Cartão de Débito\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_meia * valor_ingresso_meia;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket é: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_meia, cpf);
                        system("pause");
                        ingressos_100_arte_moderna -= quantidade_meia;
                            }
                        }
                } else if (opcao == 3) {
                    limpar();
                    printf("ATENÇÃO: Apresentação de documento obrigatória.\n");
                    printf("Informe a idade: ");
                    int idade;
                    scanf("%d", &idade);
                    limparBufferEntrada();

                    if (idade >= 60 || idade <= 6) {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                        limpar();
                        printf("CPF válido\n");
                        printf("Quantidade de ingressos de isenção desejada: ");
                        scanf("%d", &quantidade_isencao);
                        limparBufferEntrada();

                        if (quantidade_isencao <= 0 || quantidade_isencao > ingressos_100_arte_moderna) {
                            limpar();
                            printf("Quantidade de ingressos de isenção inválida.\n");
                            printf("Ingressos disponíveis: %d\n", ingressos_100_arte_moderna);
                        } else {
                            limpar();
                            printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                            int confirmacao;
                            scanf("%d", &confirmacao);
                            limparBufferEntrada();
                            if (confirmacao == 1) {
                            char codigoTicket[7];
                            gerarCodigoTicket(codigoTicket, 6);
                            limpar();
                            printf("Seu ticket é: %s\n", codigoTicket);
                            salvarTicket(codigoTicket, quantidade_isencao, cpf);
                            system("pause");
                            ingressos_100_arte_moderna -= quantidade_isencao;
                            }
                        }
                    } else {
                        limpar();
                        printf("Isenção válida apenas para pessoas com 60 anos ou mais e crianças com menos de 6 anos.\n");
                    }
                }
                break;

            case 2:
                limpar();
                printf("--150 anos de Santos Dumont--\n\n");
                printf(" No âmbito da aviação, Santos Dumont, nascido em 20 de julho de 1873 e falecido\n"
                       "em 23 de julho de 1932, é reconhecido como um pioneiro brasileiro essencial na história\n"
                       "mundial da aviação. Ao longo de seus 59 anos de vida, ele alcançou feitos notáveis,\n"
                       "incluindo o voo do 14-Bis em 1906, uma aeronave de sua própria concepção que percorreu\n"
                       "publicamente uma distância de 60 metros, sendo exclusivamente reconhecido como o\n"
                       "primeiro voo controlado, autossustentado e motorizado do mundo. Em 1907, ele projetou o\n"
                       "Demoiselle, uma aeronave leve e acessível que contribuiu para a popularização da aviação.\n"
                       "Santos Dumont recebeu o Prêmio Deutsch de la Meurthe em 1901, 1904 e 1905 por suas\n"
                       "conquistas aeronáuticas, evidenciando sua influência na aviação. Além de suas realizações\n"
                       "técnicas, ele também era um defensor da aviação civil e do voo como meio de transporte\n"
                       "acessível. No entanto, os seus últimos anos foram marcados por problemas de saúde,\n"
                       "incluindo esclerose múltipla, levando-o a enfrentar tristeza e depressão. Em 1932, optou por\n"
                       "encerrar sua própria vida. Santos Dumont é lembrado como um visionário que contribuiu\n"
                       "significativamente para o desenvolvimento da aviação, representando uma fonte de orgulho\n"
                       "para o Brasil e o mundo.\n\n");
                printf("Ingressos disponíveis: %d\n", ingressos_150_santos_dumont);
                if (ingressos_150_santos_dumont == 0) {
                    printf("Ingressos esgotados!\n");
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                    }
                }
                printf("Escolha o tipo de ingresso:\n");
                printf("1- Inteira (R$%.2f)\n", valor_ingresso_inteira);
                printf("2- Meia (R$%.2f)\n", valor_ingresso_meia);
                printf("3- Isenção (Apenas para pessoas acima de 60 anos e crianças abaixo de 6 anos)\n");
                printf("4- Voltar ao menu inicial\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                limparBufferEntrada();

                if (opcao < 1 || opcao > 4) {
                    continue;
                }

                if (opcao == 4) {
                    break;
                }

                if (opcao == 1) {
                    limpar();
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_inteira);
                    limparBufferEntrada();
                    if (quantidade_inteira <= 0 || quantidade_inteira > ingressos_150_santos_dumont) {
                    limpar();
                    printf("Quantidade de ingressos de entrada inteira inválida ou esgotada.\n");
                    printf("Ingressos disponíveis: %d\n", ingressos_150_santos_dumont);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF válido\n");
                    printf("Escolha o método de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cartão de Crédito\n");
                    printf("3- Cartão de Débito\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_inteira * valor_ingresso_inteira;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket é: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_inteira, cpf);
                        system("pause");
                        ingressos_150_santos_dumont -= quantidade_inteira;
                        }
                    }
                } else if (opcao == 2) {
                    limpar();
                    printf("ATENÇÃO: Apresentação de documento obrigatória.\n");
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_meia);
                    limparBufferEntrada();
                    if (quantidade_meia <= 0 || quantidade_meia > ingressos_150_santos_dumont) {
                    limpar();
                    printf("Quantidade de ingressos de meia entrada inválida ou esgotada.\n");
                    printf("Ingressos disponíveis: %d\n", ingressos_150_santos_dumont);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF válido\n");
                    printf("Escolha o método de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cartão de Crédito\n");
                    printf("3- Cartão de Débito\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_meia * valor_ingresso_meia;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket é: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_meia, cpf);
                        system("pause");
                        ingressos_150_santos_dumont -= quantidade_meia;
                            }
                        }
                } else if (opcao == 3) {
                    limpar();
                    printf("ATENÇÃO: Apresentação de documento obrigatória.\n");
                    printf("Informe a idade: ");
                    int idade;
                    scanf("%d", &idade);
                    limparBufferEntrada();

                    if (idade >= 60 || idade <= 6) {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                        limpar();
                        printf("CPF válido\n");
                        printf("Quantidade de ingressos de isenção desejada: ");
                        scanf("%d", &quantidade_isencao);
                        limparBufferEntrada();

                        if (quantidade_isencao <= 0 || quantidade_isencao > ingressos_150_santos_dumont) {
                            limpar();
                            printf("Quantidade de ingressos de isenção inválida.\n");
                            printf("Ingressos disponíveis: %d\n", ingressos_150_santos_dumont);
                        } else {
                            limpar();
                            printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                            int confirmacao;
                            scanf("%d", &confirmacao);
                            limparBufferEntrada();
                            if (confirmacao == 1) {
                            char codigoTicket[7];
                            gerarCodigoTicket(codigoTicket, 6);
                            limpar();
                            printf("Seu ticket é: %s\n", codigoTicket);
                            salvarTicket(codigoTicket, quantidade_isencao, cpf);
                            system("pause");
                            ingressos_150_santos_dumont -= quantidade_isencao;
                            }
                        }
                    } else {
                        limpar();
                        printf("Isenção válida apenas para pessoas com 60 anos ou mais e crianças com menos de 6 anos.\n");
                    }
                }
                break;

            case 3:
                limpar();
                printf("--Jogos Olímpicos de Paris 2024--\n\n");
                printf(" Os Jogos Olímpicos de Paris 2024 estão agendados para ocorrer na cidade de\n"
                       "Paris, França, e em localidades circunvizinhas, prometendo uma experiência esportiva\n"
                       "abrangente e única. Com programação estabelecida para o período de 26 de julho a 11 de\n"
                       "agosto de 2024, esse evento esportivo abrangerá uma ampla gama de modalidades, desde\n"
                       "esportes tradicionais como atletismo, natação e ginástica até modalidades recentemente\n"
                       "incorporadas, como surfe, escalada esportiva e skate, com o intuito de atrair uma audiência\n"
                       "mais diversificada.\n"
                       "Paris planeja utilizar uma combinação de locais já icônicos, como o Stade de France,\n"
                       "instalações renovadas e novas construções para sediar as competições esportivas. Além\n"
                       "do enfoque esportivo, os Jogos de Paris 2024 têm a ambição de destacar a rica cultura e\n"
                       "história da França, promovendo valores como igualdade de gênero e sustentabilidade.\n"
                       "Posteriormente aos Jogos Olímpicos, Paris manterá o espírito esportivo ao ser palco dos\n"
                       "Jogos Paralímpicos de 2024, reforçando o compromisso com a inclusão e celebrando o\n"
                       "esporte adaptado.\n"
                       "É essencial notar que detalhes específicos, como locais exatos, cerimônias e participantes,\n"
                       "podem sofrer ajustes à medida que a data do evento se aproxima. Dessa forma, recomenda-se\n"
                       "acompanhar as notícias e os canais oficiais para obter informações atualizadas sobre os\n"
                       "Jogos Olímpicos de Paris 2024.\n\n");
                printf("Ingressos disponíveis: %d\n", ingressos_olimpiadas_paris_2024);
                if (ingressos_olimpiadas_paris_2024 == 0) {
                    printf("Ingressos esgotados!\n");
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                    }
                }
                printf("Escolha o tipo de ingresso:\n");
                printf("1- Inteira (R$%.2f)\n", valor_ingresso_inteira);
                printf("2- Meia (R$%.2f)\n", valor_ingresso_meia);
                printf("3- Isenção (Apenas para pessoas acima de 60 anos e crianças abaixo de 6 anos)\n");
                printf("4- Voltar ao menu inicial\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                limparBufferEntrada();

                if (opcao < 1 || opcao > 4) {
                    continue;
                }

                if (opcao == 4) {
                    break;
                }

                if (opcao == 1) {
                    limpar();
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_inteira);
                    limparBufferEntrada();
                    if (quantidade_inteira <= 0 || quantidade_inteira > ingressos_olimpiadas_paris_2024) {
                    limpar();
                    printf("Quantidade de ingressos de entrada inteira inválida ou esgotada.\n");
                    printf("Ingressos disponíveis: %d\n", ingressos_olimpiadas_paris_2024);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF válido\n");
                    printf("Escolha o método de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cartão de Crédito\n");
                    printf("3- Cartão de Débito\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_inteira * valor_ingresso_inteira;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket é: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_inteira, cpf);
                        system("pause");
                        ingressos_olimpiadas_paris_2024 -= quantidade_inteira;
                        }
                    }
                } else if (opcao == 2) {
                    limpar();
                    printf("ATENÇÃO: Apresentação de documento obrigatória.\n");
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_meia);
                    limparBufferEntrada();
                    if (quantidade_meia <= 0 || quantidade_meia > ingressos_olimpiadas_paris_2024) {
                    limpar();
                    printf("Quantidade de ingressos meia entrada inválida ou esgotada.\n");
                    printf("Ingressos disponíveis: %d\n", ingressos_olimpiadas_paris_2024);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF válido\n");
                    printf("Escolha o método de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cartão de Crédito\n");
                    printf("3- Cartão de Débito\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_meia * valor_ingresso_meia;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket é: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_meia, cpf);
                        system("pause");
                        ingressos_olimpiadas_paris_2024 -= quantidade_meia;
                            }
                        }
                } else if (opcao == 3) {
                   limpar();
                    printf("ATENÇÃO: Apresentação de documento obrigatória.\n");
                    printf("Informe a idade: ");
                    int idade;
                    scanf("%d", &idade);
                    limparBufferEntrada();

                    if (idade >= 60 || idade <= 6) {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                        limpar();
                        printf("CPF válido\n");
                        printf("Quantidade de ingressos de isenção desejada: ");
                        scanf("%d", &quantidade_isencao);
                        limparBufferEntrada();

                        if (quantidade_isencao <= 0 || quantidade_isencao > ingressos_olimpiadas_paris_2024) {
                            limpar();
                            printf("Quantidade de ingressos de isenção inválida.\n");
                            printf("Ingressos disponíveis: %d\n", ingressos_olimpiadas_paris_2024);
                        } else {
                            limpar();
                            printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                            int confirmacao;
                            scanf("%d", &confirmacao);
                            limparBufferEntrada();
                            if (confirmacao == 1) {
                            char codigoTicket[7];
                            gerarCodigoTicket(codigoTicket, 6);
                            limpar();
                            printf("Seu ticket é: %s\n", codigoTicket);
                            salvarTicket(codigoTicket, quantidade_isencao, cpf);
                            system("pause");
                            ingressos_olimpiadas_paris_2024 -= quantidade_isencao;
                            }
                        }
                    } else {
                        limpar();
                        printf("Isenção válida apenas para pessoas com 60 anos ou mais e crianças com menos de 6 anos.\n");
                    }
                }
                break;


            case 4:
                limpar();
                printf("--Copa do Mundo 2026--\n\n");
                printf(" A Copa do Mundo de 2026 está agendada para ocorrer nos Estados Unidos, Canadá\n"
                       "e México, marcando a primeira vez que o torneio será disputado em três nações distintas.\n"
                       "Este evento esportivo prevê ser grandioso, abrangendo uma variedade significativa de\n"
                       "cidades-sede. No entanto, é aconselhável consultar fontes atualizadas para obter informações\n"
                       "detalhadas sobre o evento, incluindo dados sobre estádios, equipes participantes e\n"
                       "outras novidades relacionadas à Copa do Mundo de 2026.\n\n");
                printf("Ingressos disponíveis: %d\n", ingressos_copa_mundo_2026);
                if (ingressos_copa_mundo_2026 == 0) {
                    printf("Ingressos esgotados!\n");
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                    }
                }
                printf("Escolha o tipo de ingresso:\n");
                printf("1- Inteira (R$%.2f)\n", valor_ingresso_inteira);
                printf("2- Meia (R$%.2f)\n", valor_ingresso_meia);
                printf("3- Isenção (Apenas para pessoas acima de 60 anos e crianças abaixo de 6 anos)\n");
                printf("4- Voltar ao menu inicial\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                limparBufferEntrada();

                if (opcao < 1 || opcao > 4) {
                    continue;
                }

                if (opcao == 4) {
                    break;
                }

                if (opcao == 1) {
                    limpar();
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_inteira);
                    limparBufferEntrada();
                    if (quantidade_inteira <= 0 || quantidade_inteira > ingressos_copa_mundo_2026) {
                    limpar();
                    printf("Quantidade de ingressos de entrada inteira inválida ou esgotada.\n");
                    printf("Ingressos disponíveis: %d\n", ingressos_copa_mundo_2026);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF válido\n");
                    printf("Escolha o método de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cartão de Crédito\n");
                    printf("3- Cartão de Débito\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_inteira * valor_ingresso_inteira;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket é: %s\n", codigoTicket);

                        system("pause");
                        ingressos_copa_mundo_2026 -= quantidade_inteira;
                        }
                    }
                } else if (opcao == 2) {
                    limpar();
                    printf("ATENÇÃO: Apresentação de documento obrigatória.\n");
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_meia);
                    limparBufferEntrada();
                    if (quantidade_meia <= 0 || quantidade_meia > ingressos_copa_mundo_2026) {
                    limpar();
                    printf("Quantidade de ingressos meia entrada inválida ou esgotada.\n");
                    printf("Ingressos disponíveis: %d\n", ingressos_copa_mundo_2026);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF válido\n");
                    printf("Escolha o método de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cartão de Crédito\n");
                    printf("3- Cartão de Débito\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_meia * valor_ingresso_meia;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket é: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_meia, cpf);
                        system("pause");
                        ingressos_copa_mundo_2026 -= quantidade_meia;
                            }
                        }
                } else if (opcao == 3) {
                   limpar();
                    printf("ATENÇÃO: Apresentação de documento obrigatória.\n");
                    printf("Informe a idade: ");
                    int idade;
                    scanf("%d", &idade);
                    limparBufferEntrada();

                    if (idade >= 60 || idade <= 6) {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas números): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
                            system("pause");
                            continue;
                        }
                        limpar();
                        printf("CPF válido\n");
                        printf("Quantidade de ingressos de isenção desejada: ");
                        scanf("%d", &quantidade_isencao);
                        limparBufferEntrada();

                        if (quantidade_isencao <= 0 || quantidade_isencao > ingressos_copa_mundo_2026) {
                            limpar();
                            printf("Quantidade de ingressos de isenção inválida.\n");
                            printf("Ingressos disponíveis: %d\n", ingressos_copa_mundo_2026);
                        } else {
                            limpar();
                            printf("Deseja confirmar o pagamento (1-Sim, 2-Não)? ");
                            int confirmacao;
                            scanf("%d", &confirmacao);
                            limparBufferEntrada();
                            if (confirmacao == 1) {
                            char codigoTicket[7];
                            gerarCodigoTicket(codigoTicket, 6);
                            limpar();
                            printf("Seu ticket é: %s\n", codigoTicket);
                            salvarTicket(codigoTicket, quantidade_isencao, cpf);
                            system("pause");
                            ingressos_copa_mundo_2026 -= quantidade_isencao;
                            }
                        }
                    } else {
                        limpar();
                        printf("Isenção válida apenas para pessoas com 60 anos ou mais e crianças com menos de 6 anos.\n");
                        system("pause");
                    }
                }
                break;
            case 5:
                printf("Saindo do sistema...\n");
                exit(0);

            default:
                break;
        }
        printf("\nPressione Enter para continuar...");
        limparBufferEntrada();
    }
    return 0;
}
