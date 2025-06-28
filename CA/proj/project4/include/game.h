#ifndef GAME_H
#define GAME_H
typedef struct
{
    int x, y;
    int last_x, last_y;
    int width, height;
} Player;

typedef struct
{
    int x, y;
    int last_x, last_y;
    int width, height;
    float shoot_timer;
    int blood;
    int type;//

} Enemy;

typedef struct
{
    float x, y;
    float last_x, last_y;
    float vx, vy;
    float speed;
    int alive;
    int homing;
    int type; // 0: 点状, 1: 横条, 2: 十字
    int good;
} Bullet;

void player_init(Player *p);
void player_update(Player *player, float dt, Bullet *pool, int max);
void player_render(Player *p);
void enemy_init(Enemy *e);
void enemy_update(Enemy *e, float dt, Bullet *pool, int max);
void enemy_render(Enemy *e);
void bullet_init_pool(Bullet *pool, int max);
void bullet_update(Bullet *bullet, Player *player, Enemy *enemy, float dt);
void bullet_render(Bullet *bullet);
void bullet_spawn(Bullet *pool, int max, float x, float y, float vx, float vy, float speed, int homing,int type,int isgood);

void draw_clear_rect(int x, int y, int w, int h);
void draw_show_fps();
void draw_show_bullet_count(Bullet *pool, int max);

void game_init();
void game_update(float dt);
void game_render();

#endif