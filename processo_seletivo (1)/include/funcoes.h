#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./registros.h"

void menu(principal *programa);
curso_e_pesos *carregar_cursos_e_pesos();
curso_e_vagas *carregar_cursos_e_vagas();
vestibulando *carregar_dados(int &qntdInscritos);
acertos *carregar_acertos(int &qntdCandidatos);
void calcularNotasArea(acertos *notas, vestibulando *candidatos,
                       curso_e_pesos *cursos_e_pesos, int qntdCandidatos);
void calcularNotaFinal(acertos *notas, int i);
float calcular_escore(int pontos, float media, float desvio);
void ordenarCandidatos(acertos *notas, int qntdCandidatos);
void arquivoSaida(acertos *notas, int qntdCandidatos);
void quick_sort_nomeCurso(acertos *notas, int esq, int dir);
void quick_sort_vaga(acertos *notas, int esq, int dir);
void quick_sort_vagaTamanho(acertos *notas, int esq, int dir);
void quick_sort_nota(acertos *notas, int esq, int dir);
void quick_sort_nome(acertos *notas, int esq, int dir);
void pesquisarCandidato(acertos *notas, int qntdCandidatos);
void ordenarCandidatosNaoConvocados(acertos *notas, int qntdCandidatos);
void naoConvocados(acertos *notas, int qntdCandidatos,
                   curso_e_vagas *cursos_e_vagas, vestibulando *candidatos,
                   int &qntdInscritos, curso_e_pesos *cursos_e_pesos);
void alterarNotaRedacao(acertos *notas, int qntdCandidatos);