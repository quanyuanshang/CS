#include "lcd/lcd.h"
#include "utils.h"
#include "assembly/scenario_select.h"
#include "systick.h"
#include "game.h"
#include "gd32vf103.h"

#define LCD_WIDTH 240
#define LCD_HEIGHT 135

#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 10
#define PLAYER_SPEED 5

#define ENEMY_WIDTH 10
#define ENEMY_HEIGHT 10

#define BULLET_SPEED -5
#define ENEMY_BULLET_SPEED 3
#define MAX_BULLETS 20
#define MAX_ENEMIES 5

extern int current_scenario;
void Inp_init(void)
{
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOC);

  gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ,
            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  gpio_init(GPIOC, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ,
            GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
}

void IO_init(void)
{
  Inp_init(); // inport init
  Lcd_Init(); // LCD init
}

// void Board_self_test(void)
// {
//   int selected_scenario = 0;

//   while (1)
//   {
//     LCD_ShowString(60, 25, (u8 *)"TEST (25s)", WHITE);
//     if (Get_Button(JOY_LEFT))
//     {
//       LCD_ShowString(5, 25, (u8 *)"L", BLUE);
//       LCD_ShowString(60, 25, (u8 *)"TEST", RED);
//     }
//     if (Get_Button(JOY_DOWN))
//     {
//       LCD_ShowString(25, 45, (u8 *)"D", BLUE);
//       LCD_ShowString(60, 25, (u8 *)"TEST", GREEN);
//     }
//     if (Get_Button(JOY_UP))
//     {
//       LCD_ShowString(25, 5, (u8 *)"U", BLUE);
//     }
//     if (Get_Button(JOY_RIGHT))
//     {
//       LCD_ShowString(45, 25, (u8 *)"R", BLUE);
//     }
//     if (Get_Button(JOY_CTR))
//     {
//       LCD_ShowString(25, 25, (u8 *)"C", BLUE);
//     }
//     if (Get_Button(BUTTON_1))
//     {
//       LCD_ShowString(60, 5, (u8 *)"SW1", BLUE);
//     }
//     if (Get_Button(BUTTON_2))
//     {
//       LCD_ShowString(60, 45, (u8 *)"SW2", BLUE);
//     }

//     // Call the scenario selection function and get the selected scenario

//     // Display the currently selected scenario
//     LCD_ShowString(5, 120, (u8 *)"Selected: ", WHITE);
//     LCD_ShowNum(80, 120, selected_scenario, 1, RED);

//     delay_1ms(10);
//     LCD_Clear(BLACK);
//   }
// }
// void LCD_ClearArea(u16 x, u16 y, u16 w, u16 h)
// {
//   LCD_Fill(x, y, x + w - 1, y + h - 1, BLACK); // 使用现有填充函数
// }
extern int selected_scenario;
int main(void)
{

  IO_init();
  LCD_Clear(BLACK);
  scenario_select(1);
  LCD_ShowString(60, 50, (u8 *)"Selected: ", WHITE);
  LCD_ShowNum(140, 50, selected_scenario, 1, WHITE);
  //  pause 2s
  uint32_t last_time = get_timer_value();
  delay_1ms(1000);
  LCD_Clear(BLACK);
  game_init(); // 初始化游戏状态
  while (1)
  {
    uint32_t now = get_timer_value();
    float dt = (float)(now - last_time) / (float)SystemCoreClock; // 转换成秒
    last_time = now;

    last_time = now;
    game_update(dt); // 更新游戏状态
    
  }

}