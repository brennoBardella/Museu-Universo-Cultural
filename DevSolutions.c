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
        printf("3- Jogos Ol�mpicos de Paris 2024\n");
        printf("4- Copa do Mundo 2026\n");
        printf("5- Sair\n");
        printf("Escolha uma op��o: ");
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
                printf(" A arte contempor�nea, que se estende por aproximadamente um s�culo de evolu��o\n"
                       "art�stica do final do s�culo XIX at� meados do s�culo XX, se destaca pela multiplicidade\n"
                       "de estilos, movimentos e experimenta��es. Englobando correntes como impressionismo,\n"
                       "p�s-impressionismo, cubismo, futurismo, expressionismo, dada�smo, surrealismo, abstracionismo,\n"
                       "entre outras, a arte moderna foi marcada por renomados artistas como Picasso,\n"
                       "Van Gogh, Duchamp e Dal�. Esses artistas desafiaram tradi��es, exploraram novas formas\n"
                       "de express�o e contribu�ram para moldar a arte contempor�nea. Esse per�odo reflete as\n"
                       "mudan�as sociais, pol�ticas e tecnol�gicas da �poca, destacando-se como uma era de\n"
                       "inova��o e diversidade nas artes.\n\n");
                printf("Ingressos dispon�veis: %d\n", ingressos_100_arte_moderna);
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
                printf("3- Isen��o (Apenas para pessoas acima de 60 anos e crian�as abaixo de 6 anos)\n");
                printf("4- Voltar ao menu inicial\n");
                printf("Escolha uma op��o: ");
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
                    printf("Quantidade de ingressos de entrada inteira inv�lida ou esgotada.\n");
                    printf("Ingressos dispon�veis: %d\n", ingressos_100_arte_moderna);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF v�lido\n");
                    printf("Escolha o m�todo de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cart�o de Cr�dito\n");
                    printf("3- Cart�o de D�bito\n");
                    printf("Escolha uma op��o: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_inteira * valor_ingresso_inteira;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket �: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_inteira, cpf);
                        system("pause");

                        ingressos_100_arte_moderna -= quantidade_inteira;
                        }
                    }
                } else if (opcao == 2) {
                    limpar();
                    printf("ATEN��O: Apresenta��o de documento obrigat�ria.\n");
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_meia);
                    limparBufferEntrada();
                    if (quantidade_meia <= 0 || quantidade_meia > ingressos_100_arte_moderna) {
                    limpar();
                    printf("Quantidade de ingressos de meia entrada inv�lida ou esgotada.\n");
                    printf("Ingressos dispon�veis: %d\n", ingressos_100_arte_moderna);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF v�lido\n");
                    printf("Escolha o m�todo de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cart�o de Cr�dito\n");
                    printf("3- Cart�o de D�bito\n");
                    printf("Escolha uma op��o: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_meia * valor_ingresso_meia;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket �: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_meia, cpf);
                        system("pause");
                        ingressos_100_arte_moderna -= quantidade_meia;
                            }
                        }
                } else if (opcao == 3) {
                    limpar();
                    printf("ATEN��O: Apresenta��o de documento obrigat�ria.\n");
                    printf("Informe a idade: ");
                    int idade;
                    scanf("%d", &idade);
                    limparBufferEntrada();

                    if (idade >= 60 || idade <= 6) {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                        limpar();
                        printf("CPF v�lido\n");
                        printf("Quantidade de ingressos de isen��o desejada: ");
                        scanf("%d", &quantidade_isencao);
                        limparBufferEntrada();

                        if (quantidade_isencao <= 0 || quantidade_isencao > ingressos_100_arte_moderna) {
                            limpar();
                            printf("Quantidade de ingressos de isen��o inv�lida.\n");
                            printf("Ingressos dispon�veis: %d\n", ingressos_100_arte_moderna);
                        } else {
                            limpar();
                            printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                            int confirmacao;
                            scanf("%d", &confirmacao);
                            limparBufferEntrada();
                            if (confirmacao == 1) {
                            char codigoTicket[7];
                            gerarCodigoTicket(codigoTicket, 6);
                            limpar();
                            printf("Seu ticket �: %s\n", codigoTicket);
                            salvarTicket(codigoTicket, quantidade_isencao, cpf);
                            system("pause");
                            ingressos_100_arte_moderna -= quantidade_isencao;
                            }
                        }
                    } else {
                        limpar();
                        printf("Isen��o v�lida apenas para pessoas com 60 anos ou mais e crian�as com menos de 6 anos.\n");
                    }
                }
                break;

            case 2:
                limpar();
                printf("--150 anos de Santos Dumont--\n\n");
                printf(" No �mbito da avia��o, Santos Dumont, nascido em 20 de julho de 1873 e falecido\n"
                       "em 23 de julho de 1932, � reconhecido como um pioneiro brasileiro essencial na hist�ria\n"
                       "mundial da avia��o. Ao longo de seus 59 anos de vida, ele alcan�ou feitos not�veis,\n"
                       "incluindo o voo do 14-Bis em 1906, uma aeronave de sua pr�pria concep��o que percorreu\n"
                       "publicamente uma dist�ncia de 60 metros, sendo exclusivamente reconhecido como o\n"
                       "primeiro voo controlado, autossustentado e motorizado do mundo. Em 1907, ele projetou o\n"
                       "Demoiselle, uma aeronave leve e acess�vel que contribuiu para a populariza��o da avia��o.\n"
                       "Santos Dumont recebeu o Pr�mio Deutsch de la Meurthe em 1901, 1904 e 1905 por suas\n"
                       "conquistas aeron�uticas, evidenciando sua influ�ncia na avia��o. Al�m de suas realiza��es\n"
                       "t�cnicas, ele tamb�m era um defensor da avia��o civil e do voo como meio de transporte\n"
                       "acess�vel. No entanto, os seus �ltimos anos foram marcados por problemas de sa�de,\n"
                       "incluindo esclerose m�ltipla, levando-o a enfrentar tristeza e depress�o. Em 1932, optou por\n"
                       "encerrar sua pr�pria vida. Santos Dumont � lembrado como um vision�rio que contribuiu\n"
                       "significativamente para o desenvolvimento da avia��o, representando uma fonte de orgulho\n"
                       "para o Brasil e o mundo.\n\n");
                printf("Ingressos dispon�veis: %d\n", ingressos_150_santos_dumont);
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
                printf("3- Isen��o (Apenas para pessoas acima de 60 anos e crian�as abaixo de 6 anos)\n");
                printf("4- Voltar ao menu inicial\n");
                printf("Escolha uma op��o: ");
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
                    printf("Quantidade de ingressos de entrada inteira inv�lida ou esgotada.\n");
                    printf("Ingressos dispon�veis: %d\n", ingressos_150_santos_dumont);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF v�lido\n");
                    printf("Escolha o m�todo de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cart�o de Cr�dito\n");
                    printf("3- Cart�o de D�bito\n");
                    printf("Escolha uma op��o: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_inteira * valor_ingresso_inteira;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket �: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_inteira, cpf);
                        system("pause");
                        ingressos_150_santos_dumont -= quantidade_inteira;
                        }
                    }
                } else if (opcao == 2) {
                    limpar();
                    printf("ATEN��O: Apresenta��o de documento obrigat�ria.\n");
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_meia);
                    limparBufferEntrada();
                    if (quantidade_meia <= 0 || quantidade_meia > ingressos_150_santos_dumont) {
                    limpar();
                    printf("Quantidade de ingressos de meia entrada inv�lida ou esgotada.\n");
                    printf("Ingressos dispon�veis: %d\n", ingressos_150_santos_dumont);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF v�lido\n");
                    printf("Escolha o m�todo de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cart�o de Cr�dito\n");
                    printf("3- Cart�o de D�bito\n");
                    printf("Escolha uma op��o: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_meia * valor_ingresso_meia;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket �: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_meia, cpf);
                        system("pause");
                        ingressos_150_santos_dumont -= quantidade_meia;
                            }
                        }
                } else if (opcao == 3) {
                    limpar();
                    printf("ATEN��O: Apresenta��o de documento obrigat�ria.\n");
                    printf("Informe a idade: ");
                    int idade;
                    scanf("%d", &idade);
                    limparBufferEntrada();

                    if (idade >= 60 || idade <= 6) {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                        limpar();
                        printf("CPF v�lido\n");
                        printf("Quantidade de ingressos de isen��o desejada: ");
                        scanf("%d", &quantidade_isencao);
                        limparBufferEntrada();

                        if (quantidade_isencao <= 0 || quantidade_isencao > ingressos_150_santos_dumont) {
                            limpar();
                            printf("Quantidade de ingressos de isen��o inv�lida.\n");
                            printf("Ingressos dispon�veis: %d\n", ingressos_150_santos_dumont);
                        } else {
                            limpar();
                            printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                            int confirmacao;
                            scanf("%d", &confirmacao);
                            limparBufferEntrada();
                            if (confirmacao == 1) {
                            char codigoTicket[7];
                            gerarCodigoTicket(codigoTicket, 6);
                            limpar();
                            printf("Seu ticket �: %s\n", codigoTicket);
                            salvarTicket(codigoTicket, quantidade_isencao, cpf);
                            system("pause");
                            ingressos_150_santos_dumont -= quantidade_isencao;
                            }
                        }
                    } else {
                        limpar();
                        printf("Isen��o v�lida apenas para pessoas com 60 anos ou mais e crian�as com menos de 6 anos.\n");
                    }
                }
                break;

            case 3:
                limpar();
                printf("--Jogos Ol�mpicos de Paris 2024--\n\n");
                printf(" Os Jogos Ol�mpicos de Paris 2024 est�o agendados para ocorrer na cidade de\n"
                       "Paris, Fran�a, e em localidades circunvizinhas, prometendo uma experi�ncia esportiva\n"
                       "abrangente e �nica. Com programa��o estabelecida para o per�odo de 26 de julho a 11 de\n"
                       "agosto de 2024, esse evento esportivo abranger� uma ampla gama de modalidades, desde\n"
                       "esportes tradicionais como atletismo, nata��o e gin�stica at� modalidades recentemente\n"
                       "incorporadas, como surfe, escalada esportiva e skate, com o intuito de atrair uma audi�ncia\n"
                       "mais diversificada.\n"
                       "Paris planeja utilizar uma combina��o de locais j� ic�nicos, como o Stade de France,\n"
                       "instala��es renovadas e novas constru��es para sediar as competi��es esportivas. Al�m\n"
                       "do enfoque esportivo, os Jogos de Paris 2024 t�m a ambi��o de destacar a rica cultura e\n"
                       "hist�ria da Fran�a, promovendo valores como igualdade de g�nero e sustentabilidade.\n"
                       "Posteriormente aos Jogos Ol�mpicos, Paris manter� o esp�rito esportivo ao ser palco dos\n"
                       "Jogos Paral�mpicos de 2024, refor�ando o compromisso com a inclus�o e celebrando o\n"
                       "esporte adaptado.\n"
                       "� essencial notar que detalhes espec�ficos, como locais exatos, cerim�nias e participantes,\n"
                       "podem sofrer ajustes � medida que a data do evento se aproxima. Dessa forma, recomenda-se\n"
                       "acompanhar as not�cias e os canais oficiais para obter informa��es atualizadas sobre os\n"
                       "Jogos Ol�mpicos de Paris 2024.\n\n");
                printf("Ingressos dispon�veis: %d\n", ingressos_olimpiadas_paris_2024);
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
                printf("3- Isen��o (Apenas para pessoas acima de 60 anos e crian�as abaixo de 6 anos)\n");
                printf("4- Voltar ao menu inicial\n");
                printf("Escolha uma op��o: ");
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
                    printf("Quantidade de ingressos de entrada inteira inv�lida ou esgotada.\n");
                    printf("Ingressos dispon�veis: %d\n", ingressos_olimpiadas_paris_2024);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF v�lido\n");
                    printf("Escolha o m�todo de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cart�o de Cr�dito\n");
                    printf("3- Cart�o de D�bito\n");
                    printf("Escolha uma op��o: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_inteira * valor_ingresso_inteira;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket �: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_inteira, cpf);
                        system("pause");
                        ingressos_olimpiadas_paris_2024 -= quantidade_inteira;
                        }
                    }
                } else if (opcao == 2) {
                    limpar();
                    printf("ATEN��O: Apresenta��o de documento obrigat�ria.\n");
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_meia);
                    limparBufferEntrada();
                    if (quantidade_meia <= 0 || quantidade_meia > ingressos_olimpiadas_paris_2024) {
                    limpar();
                    printf("Quantidade de ingressos meia entrada inv�lida ou esgotada.\n");
                    printf("Ingressos dispon�veis: %d\n", ingressos_olimpiadas_paris_2024);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF v�lido\n");
                    printf("Escolha o m�todo de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cart�o de Cr�dito\n");
                    printf("3- Cart�o de D�bito\n");
                    printf("Escolha uma op��o: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_meia * valor_ingresso_meia;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket �: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_meia, cpf);
                        system("pause");
                        ingressos_olimpiadas_paris_2024 -= quantidade_meia;
                            }
                        }
                } else if (opcao == 3) {
                   limpar();
                    printf("ATEN��O: Apresenta��o de documento obrigat�ria.\n");
                    printf("Informe a idade: ");
                    int idade;
                    scanf("%d", &idade);
                    limparBufferEntrada();

                    if (idade >= 60 || idade <= 6) {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                        limpar();
                        printf("CPF v�lido\n");
                        printf("Quantidade de ingressos de isen��o desejada: ");
                        scanf("%d", &quantidade_isencao);
                        limparBufferEntrada();

                        if (quantidade_isencao <= 0 || quantidade_isencao > ingressos_olimpiadas_paris_2024) {
                            limpar();
                            printf("Quantidade de ingressos de isen��o inv�lida.\n");
                            printf("Ingressos dispon�veis: %d\n", ingressos_olimpiadas_paris_2024);
                        } else {
                            limpar();
                            printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                            int confirmacao;
                            scanf("%d", &confirmacao);
                            limparBufferEntrada();
                            if (confirmacao == 1) {
                            char codigoTicket[7];
                            gerarCodigoTicket(codigoTicket, 6);
                            limpar();
                            printf("Seu ticket �: %s\n", codigoTicket);
                            salvarTicket(codigoTicket, quantidade_isencao, cpf);
                            system("pause");
                            ingressos_olimpiadas_paris_2024 -= quantidade_isencao;
                            }
                        }
                    } else {
                        limpar();
                        printf("Isen��o v�lida apenas para pessoas com 60 anos ou mais e crian�as com menos de 6 anos.\n");
                    }
                }
                break;


            case 4:
                limpar();
                printf("--Copa do Mundo 2026--\n\n");
                printf(" A Copa do Mundo de 2026 est� agendada para ocorrer nos Estados Unidos, Canad�\n"
                       "e M�xico, marcando a primeira vez que o torneio ser� disputado em tr�s na��es distintas.\n"
                       "Este evento esportivo prev� ser grandioso, abrangendo uma variedade significativa de\n"
                       "cidades-sede. No entanto, � aconselh�vel consultar fontes atualizadas para obter informa��es\n"
                       "detalhadas sobre o evento, incluindo dados sobre est�dios, equipes participantes e\n"
                       "outras novidades relacionadas � Copa do Mundo de 2026.\n\n");
                printf("Ingressos dispon�veis: %d\n", ingressos_copa_mundo_2026);
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
                printf("3- Isen��o (Apenas para pessoas acima de 60 anos e crian�as abaixo de 6 anos)\n");
                printf("4- Voltar ao menu inicial\n");
                printf("Escolha uma op��o: ");
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
                    printf("Quantidade de ingressos de entrada inteira inv�lida ou esgotada.\n");
                    printf("Ingressos dispon�veis: %d\n", ingressos_copa_mundo_2026);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF v�lido\n");
                    printf("Escolha o m�todo de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cart�o de Cr�dito\n");
                    printf("3- Cart�o de D�bito\n");
                    printf("Escolha uma op��o: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_inteira * valor_ingresso_inteira;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket �: %s\n", codigoTicket);

                        system("pause");
                        ingressos_copa_mundo_2026 -= quantidade_inteira;
                        }
                    }
                } else if (opcao == 2) {
                    limpar();
                    printf("ATEN��O: Apresenta��o de documento obrigat�ria.\n");
                    printf("Quantidade de ingressos desejada: ");
                    scanf("%d", &quantidade_meia);
                    limparBufferEntrada();
                    if (quantidade_meia <= 0 || quantidade_meia > ingressos_copa_mundo_2026) {
                    limpar();
                    printf("Quantidade de ingressos meia entrada inv�lida ou esgotada.\n");
                    printf("Ingressos dispon�veis: %d\n", ingressos_copa_mundo_2026);
                    printf("Pressione 1 para voltar: ");
                    scanf("%d", &opcao);
                    limparBufferEntrada();
                    if (opcao == 1) {
                        break;
                        }
                    } else {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                    limpar();
                    printf("CPF v�lido\n");
                    printf("Escolha o m�todo de pagamento:\n");
                    printf("1- Pix\n");
                    printf("2- Cart�o de Cr�dito\n");
                    printf("3- Cart�o de D�bito\n");
                    printf("Escolha uma op��o: ");
                    scanf("%d", &metodo_pagamento);
                    limparBufferEntrada();

                    valor_total = quantidade_meia * valor_ingresso_meia;

                    limpar();
                    printf("Valor total: R$%.2f\n", valor_total);
                    printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                    int confirmacao;
                    scanf("%d", &confirmacao);
                    limparBufferEntrada();
                    if (confirmacao == 1) {
                        char codigoTicket[7];
                        gerarCodigoTicket(codigoTicket, 6);
                        limpar();
                        printf("Seu ticket �: %s\n", codigoTicket);
                        salvarTicket(codigoTicket, quantidade_meia, cpf);
                        system("pause");
                        ingressos_copa_mundo_2026 -= quantidade_meia;
                            }
                        }
                } else if (opcao == 3) {
                   limpar();
                    printf("ATEN��O: Apresenta��o de documento obrigat�ria.\n");
                    printf("Informe a idade: ");
                    int idade;
                    scanf("%d", &idade);
                    limparBufferEntrada();

                    if (idade >= 60 || idade <= 6) {
                        limpar();
                        char cpf[12];
                        printf("Digite seu CPF (apenas n�meros): ");
                        scanf("%12s", cpf);
                        limparBufferEntrada();
                        if (strlen(cpf) != 11) {
                            limpar();
                            printf("CPF inv�lido. Deve conter exatamente 11 d�gitos.\n");
                            system("pause");
                            continue;
                        }
                        limpar();
                        printf("CPF v�lido\n");
                        printf("Quantidade de ingressos de isen��o desejada: ");
                        scanf("%d", &quantidade_isencao);
                        limparBufferEntrada();

                        if (quantidade_isencao <= 0 || quantidade_isencao > ingressos_copa_mundo_2026) {
                            limpar();
                            printf("Quantidade de ingressos de isen��o inv�lida.\n");
                            printf("Ingressos dispon�veis: %d\n", ingressos_copa_mundo_2026);
                        } else {
                            limpar();
                            printf("Deseja confirmar o pagamento (1-Sim, 2-N�o)? ");
                            int confirmacao;
                            scanf("%d", &confirmacao);
                            limparBufferEntrada();
                            if (confirmacao == 1) {
                            char codigoTicket[7];
                            gerarCodigoTicket(codigoTicket, 6);
                            limpar();
                            printf("Seu ticket �: %s\n", codigoTicket);
                            salvarTicket(codigoTicket, quantidade_isencao, cpf);
                            system("pause");
                            ingressos_copa_mundo_2026 -= quantidade_isencao;
                            }
                        }
                    } else {
                        limpar();
                        printf("Isen��o v�lida apenas para pessoas com 60 anos ou mais e crian�as com menos de 6 anos.\n");
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
