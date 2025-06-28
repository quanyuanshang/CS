.section .text
.globl draw
.type draw, @function
draw:

    # 设置矩形参数 (x1, y1, x2, y2, color)
	li a0,120
	li a1,15
	li a2,80
	li a3,60
	addi sp,sp,-4
	sw ra,0(sp)
	jal LCD_DrawRectangle
	lw ra,0(sp)
	addi sp,sp,4
