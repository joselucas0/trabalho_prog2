#include "./include/funcoes.h"

int main() {
  principal *programa = (struct principal *)malloc(sizeof(principal));
  programa->dadosCarregados = false;

  do {
    menu(programa);
  } while (programa->opc != 5);
  printf("Programa encerrado.\n");
}

void menu(principal *programa) {
  printf(".+*****+.Menu.+******+\n");
  if (!programa->dadosCarregados)
    printf("0 - Carregar os arquivos de entrada\n");
  printf("1 - Gerar arquivo de saída .txt\n");
  printf("2 - Pesquisar candidatos .txt\n");
  printf("3 - Gerar arquivo dos candidatos não aprovados\n");
  printf("4 - Alterar nota de redação dos candidatos que entraram com "
         "recurso\n");
  printf("5 - Encerrar programa\n");

  scanf("%d", &programa->opc);
  printf("\n");

  if (programa->opc == 0 && !programa->dadosCarregados) {
    programa->dadosCarregados = true;
    programa->cursos_e_pesos = carregar_cursos_e_pesos();
    programa->cursos_e_vagas = carregar_cursos_e_vagas();
    programa->candidatos = carregar_dados(programa->qntdInscritos);
    programa->notas = carregar_acertos(programa->qntdCandidatos);
    calcularNotasArea(programa->notas, programa->candidatos,
                      programa->cursos_e_pesos, programa->qntdCandidatos);
    ordenarCandidatos(programa->notas, programa->qntdCandidatos);
    return;
  }
  if (programa->opc > 0 && programa->opc < 5 && !programa->dadosCarregados) {
    printf("Por favor carregue os dados antes que possa executar qualquer "
           "outra função!\n\n");
    return;
  }
  if (programa->opc == 1) {
    arquivoSaida(programa->notas, programa->qntdCandidatos);
    return;
  }
  if (programa->opc == 2) {
    pesquisarCandidato(programa->notas, programa->qntdCandidatos);
    return;
  }
  if (programa->opc == 3) {
    naoConvocados(programa->notas, programa->qntdCandidatos,
                  programa->cursos_e_vagas, programa->candidatos,
                  programa->qntdInscritos, programa->cursos_e_pesos);
    return;
  }
  if (programa->opc == 4) {
    alterarNotaRedacao(programa->notas, programa->qntdCandidatos);
    return;
  }
}