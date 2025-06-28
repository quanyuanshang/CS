pro1：

1. `_mm_load_si128`: Loads 128-bit data from a **16-byte aligned memory address**
2. `_mm_loadu_si128`: Loads 128-bit data from an **unaligned memory address**
3. `_mm_load_pd`: Loads 128-bit **packed double-precision (64-bit)** floating-point values from aligned memory
4. `_mm_load1_pd`: Loads a single double-precision value and broadcasts it to all elements of the 128-bit register

### Header files for each intrinsic:

1. `__m128i _mm_abs_epi16 (__m128i a)`: `<tmmintrin.h>` (SSSE3)
2. `__m128i _mm_add_epi32 (__m128i a, __m128i b)`: `<emmintrin.h>` (SSE2)
3. `__m128 _mm_ceil_ps (__m128 a)`: `<smmintrin.h>` (SSE4.1)
4. `_mm_load1_pd`: `<emmintrin.h>` (SSE2)





4：`-O0` 编译效果：

- 每次 `a += 1` 和 `a += i` 都是内存读 → 加法 → 写回。
- 两个 for 循环都生成完整的跳转逻辑，i 每次递增都触发跳转判断。

### 🚀 `-O3` 编译效果：

- `a += 1` 循环等价于 `a += 1000`
- `a += i` 的等价表达式是：`a += (999*1000)/2 = 499500`
- 编译器会直接将 `a` 设置为 `1000 + 499500 = 500500`，**根本不需要执行循环！**