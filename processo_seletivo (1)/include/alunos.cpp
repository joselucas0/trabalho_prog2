#include "./funcoes.h"

curso_e_pesos *carregar_cursos_e_pesos() {
  FILE *arq;

  arq = fopen("./arquivos/cursos_e_pesos.txt", "r");

  if (arq == NULL) {
    printf("O arquivo de cursos e pesos não foi encontrado!\n\n");
    return 0;
  }

  int qntdCursos, i = 0;
  int result = fscanf(arq, "%d", &qntdCursos);
  curso_e_pesos *cursos =
      (struct curso_e_pesos *)malloc(qntdCursos * sizeof(curso_e_pesos));

  while (result != EOF) {
    result = fscanf(arq, "%d", &cursos[i].codCurso);

    if (result == EOF)
      break;

    fscanf(arq, " %[^0123456789\t]", cursos[i].nomeCurso);
    fscanf(arq, "%d", &cursos[i].pesoRed);
    fscanf(arq, "%d", &cursos[i].pesoMat);
    fscanf(arq, "%d", &cursos[i].pesoLin);
    fscanf(arq, "%d", &cursos[i].pesoHum);
    fscanf(arq, "%d", &cursos[i].pesoNat);
    i++;
  }

  fclose(arq);
  return cursos;
}

curso_e_vagas *carregar_cursos_e_vagas() {
  FILE *arq;

  arq = fopen("./arquivos/cursos_e_vagas.txt", "r");

  if (arq == NULL) {
    printf("O arquivo de cursos e vagas não foi encontrado!\n\n");
    return 0;
  }

  int qntdCursos, i = 0;
  int result = fscanf(arq, "%d", &qntdCursos);
  curso_e_vagas *cursos =
      (struct curso_e_vagas *)malloc(qntdCursos * sizeof(curso_e_vagas));

  while (result != EOF) {
    result = fscanf(arq, "%d", &cursos[i].codCurso);

    if (result == EOF)
      break;

    fscanf(arq, "%d", &cursos[i].AC);
    fscanf(arq, "%d", &cursos[i].L1);
    fscanf(arq, "%d", &cursos[i].L3);
    fscanf(arq, "%d", &cursos[i].L4);
    fscanf(arq, "%d", &cursos[i].L5);
    fscanf(arq, "%d", &cursos[i].L7);
    fscanf(arq, "%d", &cursos[i].L8);
    fscanf(arq, "%d", &cursos[i].L9);
    fscanf(arq, "%d", &cursos[i].L11);
    fscanf(arq, "%d", &cursos[i].L13);
    fscanf(arq, "%d", &cursos[i].L15);

    i++;
  }

  fclose(arq);
  return cursos;
}

vestibulando *carregar_dados(int &qntdInscritos) {
  FILE *arq;

  arq = fopen("./arquivos/dados.txt", "r");

  if (arq == NULL) {
    printf("O arquivo de dados não foi encontrado!\n\n");
    return 0;
  }

  int totalCandidatos = 0;
  vestibulando *candidatos =
      (struct vestibulando *)malloc(sizeof(vestibulando));

  while (true) {
    int codCurso;
    int result = fscanf(arq, "%d", &codCurso);

    if (result == EOF)
      break;

    int numCandidatos;
    fscanf(arq, "%d", &numCandidatos);

    totalCandidatos += numCandidatos;
    candidatos = (struct vestibulando *)realloc(
        candidatos, totalCandidatos * sizeof(vestibulando));

    for (int i = 0; i < numCandidatos; i++) {
      int posicao = totalCandidatos - numCandidatos + i;
      candidatos[posicao].codCurso = codCurso;
      fscanf(arq, "%d", &candidatos[posicao].insc);
      fscanf(arq, " %[^0123456789]", candidatos[posicao].nome);
      fscanf(arq, "%s", candidatos[posicao].dataNasc);
      fscanf(arq, "%s", candidatos[posicao].vaga);
    }
  }

  fclose(arq);
  qntdInscritos = totalCandidatos;
  return candidatos;
}

acertos *carregar_acertos(int &qntdCandidatos) {
  FILE *arq;

  arq = fopen("./arquivos/acertos.txt", "r");

  if (arq == NULL) {
    printf("O arquivo de acertos não foi encontrado!\n\n");
    return 0;
  }

  int i = 0;
  int result = fscanf(arq, "%d", &qntdCandidatos);
  acertos *notas = (struct acertos *)malloc(qntdCandidatos * sizeof(acertos));

  while (result != EOF) {
    result = fscanf(arq, "%d", &notas[i].insc);

    if (result == EOF)
      break;

    fscanf(arq, "%d", &notas[i].V_LIN);
    fscanf(arq, "%d", &notas[i].V_MAT);
    fscanf(arq, "%d", &notas[i].V_NAT);
    fscanf(arq, "%d", &notas[i].V_HUM);
    fscanf(arq, "%f", &notas[i].RED);
    i++;
  }

  fclose(arq);
  return notas;
}

void calcularNotasArea(acertos *notas, vestibulando *candidatos,
                       curso_e_pesos *cursos_e_pesos, int qntdCandidatos) {
  // Parte 1 - Calcular a média
  int totalPontosLin, totalPontosMat, totalPontosNat, totalPontosHum;
  totalPontosLin = totalPontosMat = totalPontosNat = totalPontosHum = 0;

  for (int i = 0; i < qntdCandidatos; i++) {
    totalPontosLin += notas[i].V_LIN;
    totalPontosMat += notas[i].V_MAT;
    totalPontosNat += notas[i].V_NAT;
    totalPontosHum += notas[i].V_HUM;
  }

  float mediaLin, mediaMat, mediaNat, mediaHum;
  mediaLin = float(totalPontosLin) / float(qntdCandidatos);
  mediaMat = float(totalPontosMat) / float(qntdCandidatos);
  mediaNat = float(totalPontosNat) / float(qntdCandidatos);
  mediaHum = float(totalPontosHum) / float(qntdCandidatos);

  // Parte 2 - Calcular o desvio padrão
  float desvioLin, desvioMat, desvioNat, desvioHum;
  desvioLin = desvioMat = desvioNat = desvioHum = 0;

  for (int i = 0; i < qntdCandidatos; i++) {
    desvioLin += pow(notas[i].V_LIN - mediaLin, 2);
    desvioMat += pow(notas[i].V_MAT - mediaMat, 2);
    desvioNat += pow(notas[i].V_NAT - mediaNat, 2);
    desvioHum += pow(notas[i].V_HUM - mediaHum, 2);
  }

  desvioLin = sqrt(desvioLin / qntdCandidatos);
  desvioMat = sqrt(desvioMat / qntdCandidatos);
  desvioNat = sqrt(desvioNat / qntdCandidatos);
  desvioHum = sqrt(desvioHum / qntdCandidatos);

  // Parte 3 - Fazer alteração da média e do desvio padrão
  mediaLin *= 2;
  mediaMat *= 2;
  mediaNat *= 2;
  mediaHum *= 2;

  desvioLin *= 2;
  desvioMat *= 2;
  desvioNat *= 2;
  desvioHum *= 2;

  // Parte 4 - Calcular o escore padronizado
  for (int i = 0; i < qntdCandidatos; i++) {
    notas[i].EP_LIN = calcular_escore(notas[i].V_LIN, mediaLin, desvioLin);
    notas[i].EP_MAT = calcular_escore(notas[i].V_MAT, mediaMat, desvioMat);
    notas[i].EP_NAT = calcular_escore(notas[i].V_NAT, mediaNat, desvioNat);
    notas[i].EP_HUM = calcular_escore(notas[i].V_HUM, mediaHum, desvioHum);
  }

  // Parte 5 - Importar pesos
  for (int i = 0; i < qntdCandidatos; i++) {

    int insc = notas[i].insc, j = 0;
    while (true) {
      if (insc == candidatos[j].insc) {
        notas[i].candidato = candidatos[j];
        break;
      }
      j++;
    }

    int codCurso = notas[i].candidato.codCurso, k = 0;
    while (true) {
      if (codCurso == cursos_e_pesos[k].codCurso) {
        notas[i].curso_candidato = cursos_e_pesos[k];
        break;
      }
      k++;
    }

    // Parte 6 - Nota final
    calcularNotaFinal(notas, i);
  }
}

void calcularNotaFinal(acertos *notas, int i) {
  int pesoRed = notas[i].curso_candidato.pesoRed;
  float notaRed = notas[i].RED;
  int pesoHum = notas[i].curso_candidato.pesoHum;
  float notaHum = notas[i].EP_HUM;
  int pesoNat = notas[i].curso_candidato.pesoNat;
  float notaNat = notas[i].EP_NAT;
  int pesoLin = notas[i].curso_candidato.pesoLin;
  float notaLin = notas[i].EP_LIN;
  int pesoMat = notas[i].curso_candidato.pesoMat;
  float notaMat = notas[i].EP_MAT;

  notas[i].notaFinal =
      ((pesoRed * notaRed) + (pesoHum * notaHum) + (pesoNat * notaNat) +
       (pesoLin * notaLin) + (pesoMat * notaMat)) /
      (pesoRed + pesoHum + pesoNat + pesoLin + pesoMat);
}

float calcular_escore(int pontos, float media, float desvio) {
  return 500 + 100 * (2 * pontos - media) / desvio;
}

void ordenarCandidatos(acertos *notas, int qntdCandidatos) {
  // Etapa 1 - Ordenar por nota
  quick_sort_nota(notas, 0, qntdCandidatos - 1);

  // Etapa 2 - Ordenar por vaga
  quick_sort_vaga(notas, 0, qntdCandidatos - 1);

  // Etapa 3 - Ordenar por tamanho da vaga
  quick_sort_vagaTamanho(notas, 0, qntdCandidatos - 1);

  // Etapa 4 - Ordenar por curso
  quick_sort_nomeCurso(notas, 0, qntdCandidatos - 1);
}

void arquivoSaida(acertos *notas, int qntdCandidatos) {
  FILE *arq;

  arq = fopen("saida1.txt", "w+");
  int codCursoAtual = 0, classificacao = 0;
  char vagaAtual[MAX];

  for (int i = 0; i < qntdCandidatos; i++) {
    if (codCursoAtual != notas[i].curso_candidato.codCurso) {
      if (i > 0) {
        fprintf(arq, "\n");
      }
      fprintf(arq, "%d %s\n", notas[i].curso_candidato.codCurso,
              notas[i].curso_candidato.nomeCurso);
      fprintf(arq,
              "INSC	V_LIN	V_MAT	V_NAT	V_HUM	RED     COTA NOTA "
              "FINAL	CLASSIFICAÇÃO\n");
      codCursoAtual = notas[i].curso_candidato.codCurso;
    }
    if (strcmp(vagaAtual, notas[i].candidato.vaga) != 0) {
      classificacao = 0;
      strcpy(vagaAtual, notas[i].candidato.vaga);
    }
    fprintf(arq, "%d %.2f %.2f %.2f %.2f %.2f %s %.2f %d\n",
            notas[i].candidato.insc, notas[i].EP_LIN, notas[i].EP_MAT,
            notas[i].EP_NAT, notas[i].EP_HUM, notas[i].RED,
            notas[i].candidato.vaga, notas[i].notaFinal, ++classificacao);
  }

  fclose(arq);
}

void quick_sort_nomeCurso(acertos *notas, int esq, int dir) {
  int pivo = esq, i, j;
  acertos ch;
  for (i = esq + 1; i <= dir; i++) {
    j = i;
    if (strcasecmp(notas[j].curso_candidato.nomeCurso,
                   notas[pivo].curso_candidato.nomeCurso) < 0) {
      ch = notas[j];
      while (j > pivo) {
        notas[j] = notas[j - 1];
        j--;
      }
      notas[j] = ch;
      pivo++;
    } else if (strcasecmp(notas[j].curso_candidato.nomeCurso,
                          notas[pivo].curso_candidato.nomeCurso) == 0) {
      if (notas[j].curso_candidato.codCurso <
          notas[pivo].curso_candidato.codCurso) {
        ch = notas[j];
        while (j > pivo) {
          notas[j] = notas[j - 1];
          j--;
        }
        notas[j] = ch;
        pivo++;
      }
    }
  }
  if (pivo - 1 >= esq) {
    quick_sort_nomeCurso(notas, esq, pivo - 1);
  }
  if (pivo + 1 <= dir) {
    quick_sort_nomeCurso(notas, pivo + 1, dir);
  }
}

void quick_sort_vaga(acertos *notas, int esq, int dir) {
  int pivo = esq, i, j;
  acertos ch;
  for (i = esq + 1; i <= dir; i++) {
    j = i;
    if (strcasecmp(notas[j].candidato.vaga, notas[pivo].candidato.vaga) < 0) {
      ch = notas[j];
      while (j > pivo) {
        notas[j] = notas[j - 1];
        j--;
      }
      notas[j] = ch;
      pivo++;
    }
  }
  if (pivo - 1 >= esq) {
    quick_sort_vaga(notas, esq, pivo - 1);
  }
  if (pivo + 1 <= dir) {
    quick_sort_vaga(notas, pivo + 1, dir);
  }
}

void quick_sort_vagaTamanho(acertos *notas, int esq, int dir) {
  int pivo = esq, i, j, k, l, caracteresJ, caracteresPivo;
  acertos ch;
  for (i = esq + 1; i <= dir; i++) {
    j = i;
    k = l = 0;
    caracteresJ = caracteresPivo = 0;

    while (notas[j].candidato.vaga[k] != '\0') {
      caracteresJ++;
      k++;
    }

    while (notas[pivo].candidato.vaga[l] != '\0') {
      caracteresPivo++;
      l++;
    }

    if (caracteresJ < caracteresPivo) {
      ch = notas[j];
      while (j > pivo) {
        notas[j] = notas[j - 1];
        j--;
      }
      notas[j] = ch;
      pivo++;
    }
  }
  if (pivo - 1 >= esq) {
    quick_sort_vagaTamanho(notas, esq, pivo - 1);
  }
  if (pivo + 1 <= dir) {
    quick_sort_vagaTamanho(notas, pivo + 1, dir);
  }
}

void quick_sort_nota(acertos *notas, int esq, int dir) {
  int pivo = esq, i, j;
  acertos ch;
  for (i = esq + 1; i <= dir; i++) {
    j = i;
    if (notas[j].notaFinal > notas[pivo].notaFinal) {
      ch = notas[j];
      while (j > pivo) {
        notas[j] = notas[j - 1];
        j--;
      }
      notas[j] = ch;
      pivo++;
    } else if (notas[j].notaFinal == notas[pivo].notaFinal) {
      if (notas[j].curso_candidato.codCurso ==
          notas[pivo].curso_candidato.codCurso) {
        if (notas[j].candidato.vaga == notas[pivo].candidato.vaga)
          printf("Fazer ordenação por empate!\n\n");
      }
    }
  }
  if (pivo - 1 >= esq) {
    quick_sort_nota(notas, esq, pivo - 1);
  }
  if (pivo + 1 <= dir) {
    quick_sort_nota(notas, pivo + 1, dir);
  }
}

void quick_sort_nome(acertos *notas, int esq, int dir) {
  int pivo = esq, i, j;
  acertos ch;
  for (i = esq + 1; i <= dir; i++) {
    j = i;
    if (strcasecmp(notas[j].candidato.nome, notas[pivo].candidato.nome) < 0) {
      ch = notas[j];
      while (j > pivo) {
        notas[j] = notas[j - 1];
        j--;
      }
      notas[j] = ch;
      pivo++;
    }
  }
  if (pivo - 1 >= esq) {
    quick_sort_nome(notas, esq, pivo - 1);
  }
  if (pivo + 1 <= dir) {
    quick_sort_nome(notas, pivo + 1, dir);
  }
}

void pesquisarCandidato(acertos *notas, int qntdCandidatos) {
  int insc;
  printf("VOCE ENTROU NO MENU DE PESQUISA...\n\n");

  while (true) {
    printf(
        "\nINFORME A MATRICULA DO CANDIDATO OU 0 PARA ENCERRAR A PESQUISA: ");
    scanf("%d", &insc);

    if (insc == 0)
      break;

    for (int i = 0; i < qntdCandidatos; i++) {
      if (insc == notas[i].candidato.insc) {
        printf("%d %s %s %d %s\n", notas[i].candidato.insc,
               notas[i].candidato.nome, notas[i].candidato.dataNasc,
               notas[i].curso_candidato.codCurso,
               notas[i].curso_candidato.nomeCurso);
        break;
      }
      if (i == qntdCandidatos - 1)
        printf("CANDIDATO NAO ENCONTRADO\n");
    }
  };

  printf("\n\n");
}

void ordenarCandidatosNaoConvocados(acertos *notas, int qntdCandidatos) {
  // Etapa 1 - Ordenar por nome
  quick_sort_nome(notas, 0, qntdCandidatos - 1);

  // Etapa 2 - Ordenar por curso
  quick_sort_nomeCurso(notas, 0, qntdCandidatos - 1);
}

void naoConvocados(acertos *notas, int qntdCandidatos,
                   curso_e_vagas *cursos_e_vagas, vestibulando *candidatos,
                   int &qntdInscritos, curso_e_pesos *cursos_e_pesos) {
  int codCursoAtual = 0, qntdCursos = 0, qntdNaoConvocados = 0;
  acertos *naoConvocados = (struct acertos *)malloc(sizeof(acertos));
  curso_e_vagas *vagasRestantes =
      (struct curso_e_vagas *)malloc(sizeof(curso_e_vagas));

  for (int i = 0; i < qntdCandidatos; i++) {
    int j = 0, k = -1;
    while (codCursoAtual != notas[i].candidato.codCurso) {
      codCursoAtual = cursos_e_vagas[j].codCurso;
      j++;
    }
    while (k < qntdCursos && codCursoAtual != vagasRestantes[k].codCurso) {
      if (k == qntdCursos - 1) {
        qntdCursos++;
        vagasRestantes = (struct curso_e_vagas *)realloc(
            vagasRestantes, qntdCursos * sizeof(curso_e_vagas));
        vagasRestantes[qntdCursos - 1] = cursos_e_vagas[j - 1];
        codCursoAtual = vagasRestantes[qntdCursos - 1].codCurso;
      }
      k++;
    }
    if (!strcmp(notas[i].candidato.vaga, "AC") && vagasRestantes[k].AC)
      vagasRestantes[k].AC--;
    else if (!strcmp(notas[i].candidato.vaga, "L1") && vagasRestantes[k].L1)
      vagasRestantes[k].L1--;
    else if (!strcmp(notas[i].candidato.vaga, "L3") && vagasRestantes[k].L3)
      vagasRestantes[k].L3--;
    else if (!strcmp(notas[i].candidato.vaga, "L4") && vagasRestantes[k].L4)
      vagasRestantes[k].L4--;
    else if (!strcmp(notas[i].candidato.vaga, "L5") && vagasRestantes[k].L5)
      vagasRestantes[k].L5--;
    else if (!strcmp(notas[i].candidato.vaga, "L7") && vagasRestantes[k].L7)
      vagasRestantes[k].L7--;
    else if (!strcmp(notas[i].candidato.vaga, "L8") && vagasRestantes[k].L8)
      vagasRestantes[k].L8--;
    else if (!strcmp(notas[i].candidato.vaga, "L9") && vagasRestantes[k].L9)
      vagasRestantes[k].L9--;
    else if (!strcmp(notas[i].candidato.vaga, "L11") && vagasRestantes[k].L11)
      vagasRestantes[k].L11--;
    else if (!strcmp(notas[i].candidato.vaga, "L13") && vagasRestantes[k].L13)
      vagasRestantes[k].L13--;
    else if (!strcmp(notas[i].candidato.vaga, "L15") && vagasRestantes[k].L15)
      vagasRestantes[k].L15--;
    else {
      qntdNaoConvocados++;
      naoConvocados = (struct acertos *)realloc(
          naoConvocados, qntdNaoConvocados * sizeof(acertos));
      naoConvocados[qntdNaoConvocados - 1] = notas[i];
    }
  }

  for (int i = 0; i < qntdInscritos; i++) {
    for (int j = 0; j < qntdCandidatos; j++) {
      if (candidatos[i].insc == notas[j].candidato.insc)
        break;
      if (j == qntdCandidatos - 1) {
        qntdNaoConvocados++;
        naoConvocados = (struct acertos *)realloc(
            naoConvocados, qntdNaoConvocados * sizeof(acertos));
        naoConvocados[qntdNaoConvocados - 1].candidato = candidatos[i];
        int k = 0;
        while (true) {
          if (candidatos[i].codCurso == cursos_e_pesos[k].codCurso)
            break;
          k++;
        }
        naoConvocados[qntdNaoConvocados - 1].curso_candidato =
            cursos_e_pesos[k];
      }
    }
  }

  ordenarCandidatosNaoConvocados(naoConvocados, qntdNaoConvocados);

  FILE *arq;

  arq = fopen("saida2.txt", "w+");
  int codCurso = 0;

  fprintf(arq, ".+*******+.NAO APROVADOS.+*******+.\n");

  for (int i = 0; i < qntdNaoConvocados; i++) {
    if (codCurso != naoConvocados[i].curso_candidato.codCurso) {
      fprintf(arq, "\n%d %s\n", naoConvocados[i].curso_candidato.codCurso,
              naoConvocados[i].curso_candidato.nomeCurso);
      codCurso = naoConvocados[i].curso_candidato.codCurso;
    }
    fprintf(arq, "%d %s\n", naoConvocados[i].candidato.insc,
            naoConvocados[i].candidato.nome);
  }

  fclose(arq);
}

void alterarNotaRedacao(acertos *notas, int qntdCandidatos) {
  FILE *arq;
  char nomeArq[MAX];

  printf("DIGITE O NOME DO ARQUIVO DE ALTERACAO DE NOTAS DE REDACAO: ");
  scanf("%s", nomeArq);
  printf("\n");
  arq = fopen(nomeArq, "r");

  if (arq == NULL) {
    printf("O arquivo de recursos da redação não foi encontrado!\n\n");
    return;
  }

  int qntdRecursos, insc;
  float notaAnterior, notaAlterada;
  int result = fscanf(arq, "%d", &qntdRecursos);

  while (result != EOF) {
    result = fscanf(arq, "%d", &insc);

    if (result == EOF)
      break;

    fscanf(arq, "%f", &notaAnterior);
    fscanf(arq, "%f", &notaAlterada);

    for (int i = 0; i < qntdCandidatos; i++) {
      if (insc == notas[i].candidato.insc) {
        if (notas[i].RED != notaAnterior)
          printf("Inconsistência na nota anterior de redação!\n\n");
        notas[i].RED = notaAlterada;
        calcularNotaFinal(notas, i);
        break;
      }
    }
  }

  fclose(arq);
}