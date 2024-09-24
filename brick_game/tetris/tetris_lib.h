#ifndef C_TETRIS_LIB_H_
#define C_TETRIS_LIB_H_

#include <stdbool.h>

typedef enum { Start, Pause, Exit, Left, Right, Up, Down, Rotate } UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int highest_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

void userInput(UserAction_t user_input, bool hold);
GameInfo_t updateCurrentState(void);

#endif
