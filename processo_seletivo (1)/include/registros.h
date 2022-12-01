#define MAX 80

struct curso_e_pesos {
  int codCurso;
  char nomeCurso[MAX];
  int pesoRed;
  int pesoMat;
  int pesoLin;
  int pesoHum;
  int pesoNat;
};

struct curso_e_vagas {
  int codCurso;
  int AC, L1, L3, L4, L5, L7, L8, L9, L11, L13, L15;
};

struct vestibulando {
  int codCurso;
  int insc;
  char nome[MAX];
  char dataNasc[11];
  char vaga[4];
};

struct acertos {
  int insc;
  vestibulando candidato;
  curso_e_pesos curso_candidato;
  int V_LIN, V_MAT, V_NAT, V_HUM;
  float EP_LIN, EP_MAT, EP_NAT, EP_HUM;
  float RED;
  float notaFinal;
};

struct principal {
  int opc;
  bool dadosCarregados;
  curso_e_pesos *cursos_e_pesos;
  curso_e_vagas *cursos_e_vagas;
  vestibulando *candidatos;
  int qntdCursos;
  int qntdInscritos;
  int qntdCandidatos;
  acertos *notas;
};

// struct media_e_desvio {
//   float mediaLin, mediaMat, mediaNat, mediaHum;
//   float desvioLin, desvioMat, desvioNat, desvioHum;
// };