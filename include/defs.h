#ifndef MAX_STR
#define MAX_STR 50
#endif

#ifndef DEF_PRECO_PEIXE
#define DEF_PRECO_PEIXE
// Enum com os preços dos peixes
typedef enum PrecoPeixe
{
  MULLET = 100,  // Tainha 
  SNAPPER = 150, // Cioba  
  SEABASS = 200  // Robalo
} PrecoPeixe;
#endif

#ifndef DEF_POSICAO
#define DEF_POSICAO
// Estrutura de posição - Fornecido na questão
typedef struct POSICAO
{
  int x, y;
} Posicao;
#endif

#ifndef DEF_PLAYER
#define DEF_PLAYER

// Estrutura dos bots - Fornecido na questão
typedef struct Player
{
  char id[MAX_STR];
  Posicao posicao;
} Bot;
#endif

// Estrutura personalizada do Bot com carga
#ifndef DEF_MYBOT
#define DEF_MYBOT
typedef struct MYBOT
{
  Bot bot;
  int charge;
} MyBot;
#endif