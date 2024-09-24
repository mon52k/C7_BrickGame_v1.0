#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "brick_game/tetris/tetris_logic.h"
#include "brick_game/tetris/fsm.h"
#include "brick_game/tetris/tetris_lib.h"

START_TEST(test1){
  ExtendedGameInfo_t game_info_ex = {0};
  restart_func(&game_info_ex);
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
      ck_assert_int_eq(0, game_info_ex.move_field[i][j]);
  ck_assert_int_eq(0, game_info_ex.game_info.score);
  ck_assert_int_eq(0, game_info_ex.game_info.pause);
  ck_assert_int_eq(1, game_info_ex.game_info.level);
}
END_TEST

START_TEST(test2){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
      ck_assert_int_eq(0, game_info_ex.game_info.field[i][j]);
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      ck_assert_int_eq(0, game_info_ex.game_info.next[i][j]);
  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
  ck_assert_ptr_null(game_info_ex.game_info.field);
  ck_assert_ptr_null(game_info_ex.game_info.next);
}
END_TEST

START_TEST(test3){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  for(int i = 0; i < 19; i++)
    for(int j = 0; j < 10; j++)
      game_info_ex.move_field[i][j] = 1;
  prepare_game_field(&game_info_ex);
  for(int i = 0; i < 19; i++)
    for(int j = 0; j < 10; j++)
      ck_assert_int_eq(1, game_info_ex.game_info.field[i][j]);
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      ck_assert_int_eq(0, game_info_ex.game_info.next[i][j]);
  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
END_TEST

START_TEST(test4){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  int i = 0;
  while(i < 1000){
    generate_next_func(&game_info_ex);
    i++;
    ck_assert_float_ne(0,game_info_ex.tetromino.next_type);
  }
  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
END_TEST

START_TEST(test5){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
      game_info_ex.touched_field[i][j] = 1;
  ck_assert_int_eq(1, check_game_over(&game_info_ex));

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
END_TEST

START_TEST(test6){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  generate_next_func(&game_info_ex);
  next_to_tetromino(&game_info_ex);
  ck_assert_int_eq(0, game_info_ex.tetromino.x);
  ck_assert_int_eq(4, game_info_ex.tetromino.y);
  ck_assert_int_ne(0, game_info_ex.tetromino.current_type);
  ck_assert_int_eq(0, game_info_ex.tetromino.next_type);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}

START_TEST(test7){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      game_info_ex.game_info.next[i][j] = 1;
  next_to_tetromino(&game_info_ex);
  brick_to_move_field(&game_info_ex);
  for(int i = 0; i < 4; i++)
    for(int j = 4; j < 8; j++)
      ck_assert_int_eq(1, game_info_ex.move_field[i][j]);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}

START_TEST(test8){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  for(int i = -1; i < 100; i++){
    generate_next_func(&game_info_ex);
    next_to_tetromino(&game_info_ex);
    game_info_ex.tetromino.y = i%9;
    action_func(&game_info_ex);
  }
  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test9){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  generate_next_func(&game_info_ex);
  next_to_tetromino(&game_info_ex);
  move_brick_right(&game_info_ex);
  ck_assert_int_eq(5, game_info_ex.tetromino.y);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test10){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  generate_next_func(&game_info_ex);
  next_to_tetromino(&game_info_ex);
  move_brick_left(&game_info_ex);
  ck_assert_int_eq(3, game_info_ex.tetromino.y);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test11){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.game_info.level = 1;
  bool res = 0;
  res = check_move_to_shift_func(&game_info_ex);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(1, game_info_ex.timer_activated);
  ck_assert_int_ne(0, game_info_ex.timer);
}

START_TEST(test12){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.game_info.level = 1;
  bool res = 0;
  while(!res){
    res = check_move_to_shift_func(&game_info_ex);
  }
  ck_assert_int_eq(1, res);
  ck_assert_int_eq(0, game_info_ex.timer_activated);
  ck_assert_int_eq(0, game_info_ex.timer);
}

START_TEST(test13){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.game_info.level = 1;
  bool res = 0;
  res = check_shifting_to_attaching(&game_info_ex);
  ck_assert_int_eq(0, res);
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
      game_info_ex.touched_field[i][j] = 1;
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
      game_info_ex.move_field[i][j] = 1;
  res = check_shifting_to_attaching(&game_info_ex);
  ck_assert_int_eq(1, res);
  for(int i = 0; i < 20; i++)
    for(int j = 0; j < 10; j++)
      game_info_ex.touched_field[i][j] = 0;
  res = check_shifting_to_attaching(&game_info_ex);
  ck_assert_int_eq(1, res);
}
START_TEST(test14){
  ExtendedGameInfo_t game_info_ex = {0};
  init_func(&game_info_ex);
  generate_next_func(&game_info_ex);
  next_to_tetromino(&game_info_ex);
  move_brick(&game_info_ex);
  ck_assert_int_eq(1, game_info_ex.tetromino.x);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test15){
  ExtendedGameInfo_t game_info_ex = {0};
  for(int i = 0; i < 2; i++)
    for(int j = 0; j < 10; j++)
      game_info_ex.move_field[i][j] = 1;
  move_from_move_to_touch(&game_info_ex);

  for(int i = 0; i < 2; i++)
    for(int j = 0; j < 10; j++)
      ck_assert_int_eq(0, game_info_ex.move_field[i][j]);

  for(int i = 0; i < 2; i++)
    for(int j = 0; j < 10; j++)
      ck_assert_int_eq(1, game_info_ex.touched_field[i][j]);
}
START_TEST(test16){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.game_info.level = 1;
  for(int i = 19; i < 20; i++)
    for(int j = 0; j < 10; j++)
      game_info_ex.touched_field[i][j] = 1;
  count_game_score(&game_info_ex);
  ck_assert_int_eq(100, game_info_ex.game_info.score);
}
START_TEST(test17){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Start;
  finite_state_machine_func(&game_info_ex);
  ck_assert_ptr_nonnull(game_info_ex.game_info.field);
  ck_assert_ptr_nonnull(game_info_ex.game_info.next);
  ck_assert_int_eq(SPAWN, game_info_ex.state);
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Exit;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(EXIT_STATE, game_info_ex.state);
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(3, game_info_ex.game_info.pause);
  ck_assert_ptr_null(game_info_ex.game_info.field);
  ck_assert_ptr_null(game_info_ex.game_info.next);
}

START_TEST(test18){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Start;
  finite_state_machine_func(&game_info_ex);
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(MOVING, game_info_ex.state);
  ck_assert_int_eq(4, game_info_ex.tetromino.y);
  ck_assert_int_eq(0, game_info_ex.tetromino.x);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}

START_TEST(test19){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Start;
  finite_state_machine_func(&game_info_ex);
  finite_state_machine_func(&game_info_ex);
  game_info_ex.new_input = true;
  game_info_ex.input = Rotate;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(MOVING, game_info_ex.state);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test20){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Start;
  finite_state_machine_func(&game_info_ex);
  finite_state_machine_func(&game_info_ex);
  game_info_ex.new_input = true;
  game_info_ex.input = Down;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(SHIFTING, game_info_ex.state);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test21){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Start;
  finite_state_machine_func(&game_info_ex);
  finite_state_machine_func(&game_info_ex);
  game_info_ex.new_input = true;
  game_info_ex.input = Right;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(MOVING, game_info_ex.state);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test22){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Start;
  finite_state_machine_func(&game_info_ex);
  finite_state_machine_func(&game_info_ex);
  game_info_ex.new_input = true;
  game_info_ex.input = Left;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(MOVING, game_info_ex.state);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test23){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Start;
  finite_state_machine_func(&game_info_ex);
  finite_state_machine_func(&game_info_ex);
  game_info_ex.new_input = true;
  game_info_ex.input = Exit;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(EXIT_STATE, game_info_ex.state);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test24){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = START;
  game_info_ex.new_input = true;
  game_info_ex.input = Start;
  finite_state_machine_func(&game_info_ex);
  finite_state_machine_func(&game_info_ex);
  game_info_ex.new_input = true;
  game_info_ex.input = Pause;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(PAUSE, game_info_ex.state);
  ck_assert_int_eq(1, game_info_ex.game_info.pause);

  dealloc_field(&(game_info_ex.game_info.field), 20);
  dealloc_field(&(game_info_ex.game_info.next), 4);
}
START_TEST(test25){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = PAUSE;
  game_info_ex.new_input = true;
  game_info_ex.input = Pause;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(MOVING, game_info_ex.state);
  ck_assert_int_eq(0, game_info_ex.game_info.pause);
  game_info_ex.game_info.pause = 1;
  game_info_ex.state = PAUSE;
  game_info_ex.new_input = true;
  game_info_ex.input = Exit;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(EXIT_STATE, game_info_ex.state);
  ck_assert_int_eq(1, game_info_ex.game_info.pause);
}
START_TEST(test26){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = SHIFTING;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(MOVING, game_info_ex.state);
  game_info_ex.state = SHIFTING;
  for(int i = 19; i < 20; i++)
    for(int j = 0; j < 10; j++)
      game_info_ex.move_field[i][j] = 1;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(ATTACHING, game_info_ex.state);
}
START_TEST(test27){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = ATTACHING;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(SPAWN, game_info_ex.state);
}
START_TEST(test28){
  ExtendedGameInfo_t game_info_ex = {0};
  game_info_ex.state = GAMEOVER;
  finite_state_machine_func(&game_info_ex);
  ck_assert_int_eq(START, game_info_ex.state);
  ck_assert_int_eq(2, game_info_ex.game_info.pause);
}

START_TEST(test29){
  ExtendedGameInfo_t *game_info_ex = NULL;
  game_info_ex = get_current_game_info_ex();
  ck_assert_ptr_nonnull(game_info_ex);
}

START_TEST(test30){
  ExtendedGameInfo_t *game_info_ex = NULL;
  game_info_ex = get_current_game_info_ex();
  GameInfo_t game_info = {0};
  game_info = updateCurrentState();
  ck_assert_ptr_null(game_info.field);
  ck_assert_ptr_null(game_info.next);
  game_info_ex->new_input = true;
  game_info_ex->input = Start;
  game_info = updateCurrentState();
  ck_assert_ptr_nonnull(game_info.field);
  ck_assert_ptr_nonnull(game_info.next);

  dealloc_field(&(game_info_ex->game_info.field), 20);
  dealloc_field(&(game_info_ex->game_info.next), 4);
}
START_TEST(test31){
  ExtendedGameInfo_t *game_info_ex = NULL;
  game_info_ex = get_current_game_info_ex();
  userInput(Rotate, false);
  ck_assert_int_eq(Rotate, game_info_ex->input);
  ck_assert_int_eq(1, game_info_ex->new_input);
}
int main() {
  Suite* suite = suite_create("UNITS");
  TCase* tcase = tcase_create("TESTS");
  SRunner* srunner = srunner_create(suite);
  int val = 0;

  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, test1);
  tcase_add_test(tcase, test2);
  tcase_add_test(tcase, test3);
  tcase_add_test(tcase, test4);
  tcase_add_test(tcase, test5);
  tcase_add_test(tcase, test6);
  tcase_add_test(tcase, test7);
  tcase_add_test(tcase, test8);
  tcase_add_test(tcase, test9);
  tcase_add_test(tcase, test10);
  tcase_add_test(tcase, test11);
  tcase_add_test(tcase, test12);
  tcase_add_test(tcase, test13);
  tcase_add_test(tcase, test14);
  tcase_add_test(tcase, test15);
  tcase_add_test(tcase, test16);
  tcase_add_test(tcase, test17);
  tcase_add_test(tcase, test18);
  tcase_add_test(tcase, test19);
  tcase_add_test(tcase, test20);
  tcase_add_test(tcase, test21);
  tcase_add_test(tcase, test22);
  tcase_add_test(tcase, test23);
  tcase_add_test(tcase, test24);
  tcase_add_test(tcase, test25);
  tcase_add_test(tcase, test26);
  tcase_add_test(tcase, test27);
  tcase_add_test(tcase, test28);
  tcase_add_test(tcase, test29);
  tcase_add_test(tcase, test30);
  tcase_add_test(tcase, test31);

  srunner_run_all(srunner, CK_NORMAL);
  val = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return val == 0 ? 0 : 1;
}

