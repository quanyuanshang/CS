.section .data
scenario_text1: .string "1:Easy"
scenario_text2: .string "2:Normal"
scenario_text3: .string "3:Hard"


.globl selected_scenario
selected_scenario: .word 0

.section .text
.globl scenario_select
.type scenario_select, @function

scenario_select:
    # Save return address and any registers we'll modify
    addi sp, sp, -16
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    
    # Load current selection
    mv s1, a0                 # s1 = current_selection
    li s2, 3            # s2 = max selection (3 options)
    
    # Display scenario options
    li a0, 1                 # x coordinate
    li a1, 10                 # y coordinate
    la a2, scenario_text1      # text to display
    li a3, 0xFFFF             # color (WHITE)
    call LCD_ShowString

    li a0, 1                  # x coordinate
    li a1, 30                 # y coordinate
    la a2, scenario_text2     # text to display
    li a3, 0xFFFF             # color (WHITE)
    call LCD_ShowString

    li a0, 1                  # x coordinate
    li a1, 50                 # y coordinate
    la a2, scenario_text3     # text to display
    li a3, 0xFFFF             # color (WHITE)
    call LCD_ShowString

input_loop:
   
    li a0,3            # 检测"上"键
    call Get_Button          # 调用C输入函数（返回a0=按键状态）
    bnez a0, select_up       # 如果按下"上"，跳转

    li a0, 1      # 检测"下"键
    call Get_Button
    bnez a0, select_down

    li a0,4           # 检测"确认"键
    call Get_Button
    bnez a0, confirm_selection

    j input_loop             # 无输入则继续循环
    
select_up:
    # === 选择项减1（最小为1） ===
    li t2, 1
    ble s1, t2, input_loop   # 如果<=1则不处理
    addi s1, s1, -1
    j wait_release_up

select_down:
    # === 选择项加1（最大为3） ===
    bge s1, s2, input_loop   # 如果>=3则不处理
    addi s1, s1, 1
    j wait_release_down

wait_release_up:
wait_loop_up:
    li a0, 3          # 上键的编号
    call Get_Button
    bnez a0, wait_loop_up
    j input_loop

wait_release_down:
wait_loop_down:
    li a0, 1          # 下键的编号
    call Get_Button
    bnez a0, wait_loop_down
    j input_loop

confirm_selection:
    la t0, selected_scenario  # t0 = selected_scenario
    sw s1,0(t0)            

    # === 恢复返回地址并返回 ===
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    addi sp, sp, 16
    ret

