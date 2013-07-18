#include "ai.h"

void ai_get_respond(enum _CELL_STATE state)
{
     ai_enemy_field[ai_last_shot.x][ai_last_shot.y] = state;
 
     if( !got_target && state == CELL_SHIP_FIRE)
         got_target = 1;
     if( got_target && state != CELL_SHIP_DEAD)
     {
         got_target = 0;
         ai_ship_mark_dead();
         ai_last_shot_suc.x = -1;
         ai_last_shot_suc.y = -1;
     }
 
     if( got_target )
         ai_choose_direction(state);
 
     if(state == CELL_SHIP_FIRE)
         ai_last_shot_suc = ai_last_shot;
}

