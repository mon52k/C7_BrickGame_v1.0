#include "tetris.h"

int main(void){
  enable_ncurses();
  game_loop();
  disable_ncurses();
  return 0;
}

void user_input_to_action(int user_input)
{
  switch(user_input)
  {
    case KEY_LEFT:
      userInput(Left, false);
      break;
    case KEY_RIGHT:
      userInput(Right, false);
      break;
    case KEY_UP:
      userInput(Up, false);
      break;
    case KEY_DOWN:
      userInput(Down, false);
      break;
    case 'r':
      userInput(Rotate, false);
      break;
    case 's':
      userInput(Start, false);
      break;
    case 'p':
      userInput(Pause, false);
      break;
    case 'e':
      userInput(Exit, false);
      break;
    default:
      break;
  }
}

void game_loop(void)
{
  GameInfo_t game_info = {0};
  while(game_info.pause != 3)
  {
    game_info = updateCurrentState();
    frontend_general_func(game_info);
    user_input_to_action(getch());
  }
}
