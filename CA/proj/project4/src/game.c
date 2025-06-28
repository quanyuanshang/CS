#include "game.h"
#include "lcd/lcd.h"
#include "utils.h"

#define MAX_BULLETS 300
#include <math.h>       // for sqrt
#define DEBOUNCE_MS 300 // 0.3s
#define DEBOUNCE_CYCLES (1 / (SystemCoreClock / 4000) * DEBOUNCE_MS)

// Forward declarations for functions defined later in this file

Bullet bullets[MAX_BULLETS];
Player player;
Enemy enemy[3];
int bullet_count = 0;
int last_press_time[6] = {0}; // 用于防抖动3,1,2,4,5

int Get_Button_Debounced(int key)
{

    uint64_t now = get_timer_value();

    // 这里用你的原始按键读取接口，比如 Get_Button(key) 返回0/1
    int pressed = Get_Button(key);

    if (pressed)
    {
        if (now - last_press_time[key] >= DEBOUNCE_CYCLES)
        {
            last_press_time[key] = now;
            return 1; // 按键触发（防抖通过）
        }
        else
        {
            return 0; // 冷却中，不触发
        }
    }
    else
    {
        return 0; // 未按下，不触发
    }
}

void draw_clear_rect(int x, int y, int w, int h)
{
    LCD_Fill(x, y, x + w, y + h, BLACK); // 用填充矩形清除
}

void draw_show_fps()
{
    static uint64_t last = 0;
    static int frame = 0;
    static float fps = 0.0f;
    frame++;
    uint64_t now = get_timer_value();

    if (now - last >= 1 / (SystemCoreClock / 8)) // 0.5个周期
    {
        fps = frame / ((float)(now - last) / ((float)SystemCoreClock / 2));
        frame = 0;
        last = now;
    }
    LCD_ShowString(1, 60, (u8 *)"FPS:", WHITE);
    LCD_ShowNum(40, 60, (int)fps, 3, RED);
}

void draw_show_bullet_count(Bullet *pool, int max)
{

    LCD_ShowString(70, 60, (u8 *)"Bullet:", WHITE);
    LCD_ShowNum(125, 60, bullet_count, 3, BLUE);
}

void bullet_spawn(Bullet *pool, int max, float x, float y, float vx, float vy, float speed, int homing, int type, int isgood)
{
    for (int i = 0; i < max; i++)
    {

        if (!pool[i].alive)
        {
            pool[i].x = x;
            pool[i].y = y;
            pool[i].vx = vx;
            pool[i].vy = vy;
            pool[i].speed = speed;
            pool[i].alive = 1;
            pool[i].homing = homing;
            pool[i].type = type; // 0: 点状, 1: 横条, 2: 十字
            pool[i].good = isgood;
            bullet_count++;
            break;
        }
    }
}
void player_init(Player *p)
{
    p->x = 70;
    p->y = 40;
    p->width = 12;
    p->height = 12;
}

void player_update(Player *player, float dt, Bullet *pool, int max)
{
    player->last_x = player->x;
    player->last_y = player->y;
    if (Get_Button_Debounced(JOY_UP))
        player->y -= 5;
    if (Get_Button_Debounced(JOY_DOWN))
        player->y += 5;
    if (Get_Button_Debounced(JOY_LEFT))
        player->x -= 5;
    if (Get_Button_Debounced(JOY_RIGHT))
        player->x += 5;
    if (Get_Button_Debounced(BUTTON_1))
    {
        bullet_spawn(pool, max, player->x, player->y, 0, -1, 100.0f, 1, 0, 1);
    }
    if (player->x < 0)
        player->x = 0;
    if (player->x + player->width > LCD_W)
        player->x = LCD_W - player->width;
    if (player->y < 0)
        player->y = 0;
    if (player->y + player->height > 50)
        player->y = 50 - player->height;
}

void player_render(Player *p)
{
    LCD_DrawCircle(p->x + p->width / 2, p->y + p->height / 2, p->width / 2, BLUE);
}

void enemy_init(Enemy *e)
{

    e[0].x = 110;
    e[0].y = 30;
    e[0].width = 12;
    e[0].height = 12;
    e[0].shoot_timer = 0;
    e[0].blood = 200;
    e[0].type = 0;

    e[1].x = 30;
    e[1].y = 30;
    e[1].width = 12;
    e[1].height = 12;
    e[1].shoot_timer = 0;
    e[1].blood = 200;
    e[1].type = 1;

    e[2].x = 70;
    e[2].y = 30;
    e[2].width = 12;
    e[2].height = 12;
    e[2].shoot_timer = 0;
    e[2].blood = 200;
    e[2].type = 2;
}

void enemy_update(Enemy *e, float dt, Bullet *pool, int max)
{
    for (int i = 0; i < 3; i++)
    {
        if (e[i].blood <= 0)
            continue;
        e[i].last_x = e[i].x;
        e[i].last_y = e[i].y;
        e[i].shoot_timer += dt;
        if (e[i].shoot_timer > 0.05f)
        {
            switch (e[i].type)
            {
            case 0: // 单发
                bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 0, 0);

                break;
            case 1: // 扇形
                bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, -0.5f, 1, 100.0f, 0, 1, 0);

                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0.0f, 1, 100.0f, 0, 1, 0);

                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0.5f, 1, 100.0f, 0, 1, 0);

                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0.0f, 1, 100.0f, 0, 1, 0);
                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0.5f, 1, 100.0f, 0, 1, 0);
                break;
            case 2: // 三连发
                bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0, 1, 100.0f, 0, 2, 0);

                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, -0.5f, 1, 100.0f, 0, 2, 0);

                // bullet_spawn(pool, max, e[i].x + 6, e[i].y + 6, 0.5f, 1, 100.0f, 0, 2, 0);
                break;
            }

            e[i].shoot_timer = 0;
        }
        e[i].x += 1;
        if (e[i].x > LCD_W)
            e[i].x = 0;
    }
}

void enemy_render(Enemy *e)
{

    for (int i = 0; i < 3; i++)
    {
        if (e[i].blood <= 0)
            continue;
        LCD_DrawCircle(e[i].x + e[i].width / 2, e[i].y + e[i].height / 2, e[i].width / 2, RED);
    }
}

void bullet_init_pool(Bullet *pool, int max)
{
    for (int i = 0; i < max; i++)
        pool[i].alive = 0;
}

void bullet_update(Bullet *bullet, Player *player, Enemy *enemy, float dt)
{
    if (!bullet->alive)
        return;
    bullet->last_x = bullet->x;
    bullet->last_y = bullet->y;
    if (bullet->homing)
    {
        for (int i = 0; i < 3; i++)
        {
            if (enemy[i].blood <= 0)
                continue;
            float dx = enemy[i].x - bullet->x;
            float dy = enemy[i].y - bullet->y;
            float dist = sqrt(dx * dx + dy * dy);
            bullet->vx = (dx / dist) * bullet->speed;
            bullet->vy = (dy / dist) * bullet->speed;
        }
    }
    else
    {
        switch (bullet->type)
        {
            // case 0: // 直线
            //     bullet->vx = 0;
            //     bullet->vy = -bullet->speed;
            //     break;
            // case 1:
            //     bullet->vx = 30 * sin(bullet->y * 0.1f); // 初始 vx 固定
            //     bullet->vy = 30 * cos(bullet->y * 0.1f); // 初始 vy 固定

            //     break;
            // case 2:                    // 抛物线轨迹
            //     bullet->vx -= 50 * dt; // 初始 vx 固定
            //     bullet->vy -= 50 * dt; // 模拟重力加速度
            //     break;

        case 0: // 直线向上
            bullet->vx = enemy[0].x;
            bullet->vy = -enemy[0].y;
            break;
        case 1:
            bullet->vx -= 50 * dt; // 初始 vx 固定
            bullet->vy -= 50 * dt; // 模拟重力加速度
            break;

        case 2: // 锯齿（Zigzag）
            bullet->vy = -bullet->speed;
            if (fmodf(bullet->y, 20.0f) < 10.0f)
                bullet->vx = bullet->speed * 0.5f;
            else
                bullet->vx = -bullet->speed * 0.5f;
            break;
        }
    }
    bullet->x += bullet->vx * dt;
    bullet->y += bullet->vy * dt;
    if (bullet->x <= 0 || bullet->x >= LCD_W || bullet->y <= 0 || bullet->y >= 50) //|| (bullet->x == enemy[0].x && bullet->y == enemy[0].y) || (bullet->x == enemy[1].x && bullet->y == enemy[1].y) || (bullet->x == player->x && bullet->y == player->y))
    {
        bullet->alive = 0;
        bullet_count--;
    }
    if (bullet->good == 0)
    {
        if (bullet->x >= player->x && bullet->x <= player->x + player->width &&
            bullet->y >= player->y && bullet->y <= player->y + player->height)
        {
            bullet->alive = 0;
            bullet_count--;
            return;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (enemy[i].blood > 0 && bullet->good == 1 && bullet->alive &&
            bullet->x >= enemy[i].x && bullet->x <= enemy[i].x + enemy[i].width &&
            bullet->y >= enemy[i].y && bullet->y <= enemy[i].y + enemy[i].height)
        {
            bullet->alive = 0;
            bullet_count--;
            enemy[i].blood--;
            return;
        }
    }
}

void bullet_render(Bullet *pool)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!pool[i].alive)
            continue;

        int x = (int)pool[i].x;
        int y = (int)pool[i].y;
        switch (pool[i].type)
        {
        case 0: // 点
            LCD_DrawPoint(x, y, WHITE);
            break;
        case 1: // 横条
            LCD_DrawLine(x - 2, y, x + 2, y, GREEN);
            break;
        case 2: // 十字
            LCD_DrawLine(x - 2, y, x + 2, y, YELLOW);
            LCD_DrawLine(x, y - 2, x, y + 2, YELLOW);
            break;
        }
    }
}

void game_init()
{
    LCD_Clear(BLACK);
    player_init(&player);
    enemy_init(enemy);
    bullet_init_pool(bullets, MAX_BULLETS);
}

void game_update(float dt)
{
    player_update(&player, dt, bullets, MAX_BULLETS);
    enemy_update(enemy, dt, bullets, MAX_BULLETS);
    for (int i = 0; i < MAX_BULLETS; i++)
    {

        bullet_update(&bullets[i], &player, enemy, dt);
    }
    game_render(); // 局部刷新屏幕
}
void game_render()
{

    LCD_DrawCircle(player.last_x + player.width / 2, player.last_y + player.height / 2, player.width / 2, BLACK);
    player_render(&player);
    if (enemy[0].blood >= 0)
    {
        LCD_DrawCircle(enemy[0].last_x + enemy[0].width / 2, enemy[0].last_y + enemy[0].height / 2, enemy[0].width / 2, BLACK);
    }
    if (enemy[1].blood >= 0)
    {
        LCD_DrawRectangle(enemy[1].last_x, enemy[1].last_y, enemy[1].last_x + enemy[1].width, enemy[1].last_y + enemy[1].height, BLACK);
    }
    if (enemy[2].blood >= 0)
    {
        LCD_DrawRectangle(enemy[2].last_x, enemy[2].last_y, enemy[2].last_x + enemy[2].width, enemy[2].last_y + enemy[2].height, BLACK);
    }
    if (enemy[0].blood > 0)
    {
        LCD_DrawCircle(enemy[0].x + enemy[0].width / 2, enemy[0].y + enemy[0].height / 2, enemy[0].width / 2, RED);
    }
    if (enemy[1].blood > 0)
    {
        LCD_DrawRectangle(enemy[1].x, enemy[1].y, enemy[1].x + enemy[1].width, enemy[1].y + enemy[1].height, GREEN);
    }
    if (enemy[2].blood > 0)
    {
        LCD_DrawRectangle(enemy[2].x, enemy[2].y, enemy[2].x + enemy[2].width, enemy[2].y + enemy[2].height, YELLOW);
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {

        switch (bullets[i].type)
        {
        case 0: // 点
            LCD_DrawPoint(bullets[i].last_x, bullets[i].last_y, BLACK);
            break;
        case 1: // 横条
            LCD_DrawLine(bullets[i].last_x - 2, bullets[i].last_y, bullets[i].last_x + 2, bullets[i].last_y, BLACK);
            break;
        case 2:                                                                                                      // 十字
            LCD_DrawLine(bullets[i].last_x - 2, bullets[i].last_y, bullets[i].last_x + 2, bullets[i].last_y, BLACK); // 横线
            LCD_DrawLine(bullets[i].last_x, bullets[i].last_y - 2, bullets[i].last_x, bullets[i].last_y + 2, BLACK); // 竖线
            break;
        }
    }

    bullet_render(bullets);

    draw_show_fps();
    draw_show_bullet_count(bullets, MAX_BULLETS);
}
