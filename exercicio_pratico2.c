#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TENTATIVAS 6
#define NUM_PALAVRAS 5

// Lista de palavras pré-definidas
const char *lista_palavras[NUM_PALAVRAS] = {"atitulde", "artefato", "jogo", "obstaculo", "programa"};

// Função para escolher uma palavra aleatoriamente
const char *escolher_palavra() {
    srand(time(NULL));
    int indice = rand() % NUM_PALAVRAS;
    return lista_palavras[indice];
}

// Função para inicializar a palavra oculta com underscores
void inicializar_palavra_oculta(char *palavra_oculta, const char *palavra_secreta) {
    int tamanho = strlen(palavra_secreta);
    for (int i = 0; i < tamanho; i++) {
        palavra_oculta[i] = '_';
    }
    palavra_oculta[tamanho] = '\0'; // Adiciona o terminador nulo
}

// Função para exibir o estado da forca
void exibir_forca(int erros) {
    printf("\n");
    printf(" _________     \n");
    printf(" |       |     \n");
    printf(" |       %c     \n", (erros >= 1) ? 'O' : ' ');
    printf(" |      %c%c%c   \n", (erros >= 3) ? '/' : ' ', (erros >= 2) ? '|' : ' ', (erros >= 4) ? '\\' : ' ');
    printf(" |      %c %c   \n", (erros >= 5) ? '/' : ' ', (erros >= 6) ? '\\' : ' ');
    printf(" |             \n");
    printf("_|_            \n");
    printf("\n");
}

// Função para exibir o progresso do jogo
void exibir_progresso(const char *palavra_oculta, int tentativas_restantes, int erros) {
    exibir_forca(erros);
    printf("Palavra: %s\n", palavra_oculta);
    printf("Tentativas restantes: %d\n", tentativas_restantes);
}

// Função para processar a tentativa do jogador
int tentar_letra(char letra, char *palavra_oculta, const char *palavra_secreta) {
    int acertou = 0;
    int tamanho = strlen(palavra_secreta);
    for (int i = 0; i < tamanho; i++) {
        if (palavra_secreta[i] == letra) {
            palavra_oculta[i] = letra;
            acertou = 1;
        }
    }
    return acertou;
}

// Função principal do jogo
void jogar_forca() {
    const char *palavra_secreta = escolher_palavra();
    int tamanho_palavra = strlen(palavra_secreta);
    char palavra_oculta[tamanho_palavra + 1];
    int tentativas_restantes = MAX_TENTATIVAS;
    int erros = 0;
    int venceu = 0;

    inicializar_palavra_oculta(palavra_oculta, palavra_secreta);

    while (tentativas_restantes > 0) {
        exibir_progresso(palavra_oculta, tentativas_restantes, erros);
        printf("Digite uma letra: ");
        char tentativa;
        scanf(" %c", &tentativa);

        if (!tentar_letra(tentativa, palavra_oculta, palavra_secreta)) {
            erros++;
            tentativas_restantes--;
            printf("Letra incorreta!\n");
        }

        // Verifica se o jogador completou a palavra
        if (strcmp(palavra_oculta, palavra_secreta) == 0) {
            venceu = 1;
            break;
        }
    }

    if (venceu) {
        printf("Parabens! Voce adivinhou a palavra: %s\n", palavra_secreta);
    } else {
        exibir_forca(erros);  // Exibe a forca completa no caso de derrota
        printf("Voce perdeu! A palavra era: %s\n", palavra_secreta);
    }
}

int main() {
    int jogar_novamente = 1;
    while (jogar_novamente) {
        jogar_forca();
        printf("Deseja jogar novamente? (1 - Sim, 0 - Nao): ");
        scanf("%d", &jogar_novamente);
    }
    printf("Obrigado por jogar!\n");
    return 0;
}
