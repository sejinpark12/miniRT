# miniRT

---

## 1. miniLibX로 윈도우 생성과 간단한 도형 그리기

**miniRT/cub3d** 프로젝트는 **miniLibX** 그래픽 라이브러리를 사용하여 구현합니다.
그러므로 먼저 **miniLibX**로 윈도우를 생성하고 간단한 도형을 그려보겠습니다.

```c
#include "mlx/mlx.h"

typedef struct  s_data
{
  void	*img;
  char	*addr;
  int	bits_per_pixel;
  int	line_length;
  int	endian;
}               t_data;

void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char *dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int*)dst = color;
}

int main(void)
{
  void	  *mlx;
  void	  *mlx_win;
  t_data  img;
  int     i;
  int     j;
  int     k;

  mlx = mlx_init();
  mlx_win = mlx_new_window(mlx, 600, 400, "miniRT");
  img.img = mlx_new_image(mlx, 600, 400);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  for (i = 250, k = 99; i < 300; i++, k -= 2)
  {
    for (j = 150 + k; j < 250; j++)
      my_mlx_pixel_put(&img, i, j, 0x0000FF00);
  }
  for (i = 300, k = 0; i < 350; i++, k += 2)
  {
    for (j = 150 + k; j < 250; j++)
      my_mlx_pixel_put(&img, i, j, 0x0000FF00);
  }
  mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
  mlx_loop(mlx);
  return (0);
}
```

### 1. 그래픽 시스템 연결

우선, 작성한 프로그램과 디스플레이 사이의 연결을 초기화하기 위해서 **`mlx_init()`** 함수를 호출합니다. 연결이 성공했다면 **`mlx_init()`** 는 **`void *`** 타입의 포인터를 **연결 식별자로 반환**합니다.([mlx man](https://github.com/psj3205/MiniLibX_man_kor/blob/main/mlx.md)을 참고하세요.)

### 2. 윈도우 생성

**`mlx_new_window()`** 함수로 새로운 윈도우를 생성할 수 있습니다.

```c
void * mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
```

**`size_x`**, **`size_y`** 매개변수로 윈도우의 너비, 높이를 설정할 수 있습니다. **`title`** 매개변수는 타이틀 바의 제목입니다. **`mlx_new_window()`** 가 성공적으로 새로운 윈도우를 생성했다면 **`void *`** 타입의 포인터를 **윈도우 식별자로 반환**합니다.([mlx_new_window man](https://github.com/psj3205/MiniLibX_man_kor/blob/main/mlx_new_window.md)을 참고하세요.)

### 3. 이미지 생성

**`mlx_new_image()`** 함수는 새로운 이미지를 생성합니다.

```c
void *mlx_new_image(void *mlx_ptr, int width, int height);
```

**`width`**, **`height`** 파라미터로 이미지의 크기를 설정합니다. **`mlx_init()`** 호출로 반환 받은 연결 식별자를 **`mlx_ptr`** 파라미터에 지정합니다. **`mlx_new_image()`** 가 성공적으로 새로운 이미지를 생성했다면 **`void *`** 타입의 **식별자를 반환**합니다.([mlx_new_image man](https://github.com/psj3205/MiniLibX_man_kor/blob/main/mlx_new_image.md)을 참고하세요.)

### 4. 생성된 이미지의 정보 설정

**`mlx_get_data_addr()`** 함수는 생성된 이미지에 대한 정보를 설정합니다.

```c
char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
```

**`img_ptr`** 파라미터로는 사용할 이미지를 지정합니다. **`mlx_get_data_addr()`** 는 이미지가 저장되어 있는 메모리의 시작 지점의 주소를 **`char *`** 형 포인터로 반환합니다. **`mlx_get_data_addr()`** 이 성공적으로 호출된다면 다음 세 개의 파라미터에 값이 지정됩니다. **`bits_per_pixel`** 파라미터에는 픽셀의 색상을 표현하는데 필요한 비트의 수가 입력됩니다.**`size_line`** 파라미터에는 이미지 한 줄을 저장하는데 필요한 바이트 수가 입력됩니다. **`endian`** 파라미터는 픽셀 색상의 저장 방식이 little endian(0 지정)인지 big endian(1 지정)인지를 나타냅니다.([mlx_new_image man](https://github.com/psj3205/MiniLibX_man_kor/blob/main/mlx_new_image.md)을 참고하세요.)

### 5. 픽셀 색상 지정하기

**`mlx_get_data_addr()`** 함수로 생성한 이미지의 시작 주소를 가지고 있지만, 이 주소의 메모리는 색상 값이 없는 비어있는 상태입니다. 그러므로 이미지의 시작 주소를 이용하여 각 픽셀의 색상을 지정해 줍니다. 여기에서는 **miniLibX**의 **`mlx_pixel_put()`** 함수 대신에 동작을 모방하여 구현한 **`my_mlx_pixel_put()`** 함수를 사용했습니다. line_length는 이미지의 가로 한 줄의 바이트 수이므로 **(line_length * y좌표)** 로 해당 픽셀 좌표의 y좌표만큼의 메모리 주소로 일단 이동합니다. bits_per_pixel이 픽셀 당 비트의 수이므로 바이트 단위로 바꾸기 위해 8로 나누면 픽셀 당 바이트를 구할 수 있습니다. **(bits_per_pixel / 8 * y좌표)** 로 x좌표만큼의 메모리 주소를 이동하여 최종적으로 (x, y) 좌표의 픽셀의 메모리 주소를 구할 수 있습니다. ([writing pixel to a image](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#writing-pixels-to-a-image)을 참고하세요.)

### 6. 이미지 그리기

마침내 **`mlx_put_image_to_window()`** 함수로 특정 윈도우 안에 이미지를 그릴 수 있습니다.

```c
int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
```

앞의 파라미터 3개는 위에서 생성한 mlx, 윈도우, 이미지의 식별자를 지정합니다. **`x`**, **`y`** 파라미터로 윈도우 안에서 이미지의 좌표를 지정합니다.

### 7. 윈도우 생성

컴파일 후 실행파일을 실행하면 아래와 같은 삼각형 이미지를 확인할 수 있습니다.

<p align="center"><img src="https://user-images.githubusercontent.com/19530862/99638554-bfb30a00-2a89-11eb-900d-ca511d517360.png"></p>

## 참고
https://github.com/qst0/ft_libgfx#minilibx

https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

---

## 2. 키보드 입력으로 도형 움직이기

키보드 입력으로 위에서 생성한 삼각형을 움직여보도록 하겠습니다.
miniLibX에서 키보드, 마우스 등으로부터 입력을 받기 위해서 **이벤트** 개념을 알아야 합니다. 이벤트는 프로그램에 의해 감지되고 처리될 수 있는 동작이나 사건을 말합니다([위키백과](https://ko.wikipedia.org/wiki/%EC%9D%B4%EB%B2%A4%ED%8A%B8_(%EC%BB%B4%ED%93%A8%ED%8C%85))). **miniLibX**는 이벤트를 처리하기 위해서 **`mlx_loop()`** 라는 루프문이 필요합니다. 이 함수는 이벤트의 수신을 기다리고 있다가, 해당 이벤트를 생성시킵니다.

```c
#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define	UP          126
#define	DOWN        125
#define	LEFT        123
#define	RIGHT       124
#define ESC         53
#define KeyPress    2
#define KeyRelease  3

typedef struct 	s_data
{
  void  *mlx;
  void  *mlx_win;
  int   width, height;
  int   x, y;
  int   up, down, left, right;
  void  *img;
  char  *addr;
  int   bits_per_pixel;
  int   line_length;
  int   endian;
}               t_data;

void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int   ft_move(t_data *data)
{
  if (data->left == 1 && data->x > 0)
  {
    data->x -= 3;
    printf("x = %d, y= %d\n", data->x, data->y);
  }
  if (data->right == 1 && data->x < data->width)
  {
    data->x += 3;
    printf("x = %d, y= %d\n", data->x, data->y);
  }
  if (data->up == 1 && data->y > 0)
  {
    data->y -= 3;
    printf("x = %d, y= %d\n", data->x, data->y);
  }
  if (data->down == 1 && data->y < data->height)
  {
    data->y += 3;
    printf("x = %d, y= %d\n", data->x, data->y);
  }
  return (0);
}

int    ft_key_press(int keycode, t_data *data)
{
  if (keycode == ESC)
  {
    mlx_destroy_window(data->mlx, data->mlx_win);
    exit(0);
  }
  if (keycode == LEFT)
    data->left = 1;
  if (keycode == RIGHT)
    data->right = 1;
  if (keycode == UP)
    data->up = 1;
  if (keycode == DOWN)
    data->down = 1;
  return (0);
}

int     ft_key_release(int keycode, t_data *data)
{
  if (keycode == LEFT)
    data->left = 0;
  if (keycode == RIGHT)
    data->right = 0;
  if (keycode == UP)
    data->up = 0;
  if (keycode == DOWN)
    data->down = 0;
  return (0);
}

int     ft_draw(t_data *data)
{
  int i;
  int j;
  int k;
  int x = data->x;
  int y = data->y;

  for (i = 0; i < data->width; i++)
  {
    for (j = 0; j < data->height; j++)
      my_mlx_pixel_put(data, i, j, 0x00000000);
  }
  for (i = x, k = 99; i < x + 50; i++, k -= 2)
  {
    for (j = y + k; j < y + 100; j++)
      my_mlx_pixel_put(data, i, j, 0x0000FF00);
  }
  for (i = x + 50, k = 0; i < x + 100; i++, k += 2)
  {
    for (j = y + k; j < y + 100; j++)
      my_mlx_pixel_put(data, i, j, 0x0000FF00);
  }
  mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
  return (0);
}

int main_loop(t_data *data)
{
  ft_draw(data);
  ft_move(data);
  return (0);
}

int	main(void)
{
  t_data  data;

  data.mlx = mlx_init();
  data.width = 600;
  data.height = 400;
  data.mlx_win = mlx_new_window(data.mlx, data.width, data.height, "miniRT");
  data.img = mlx_new_image(data.mlx, 600, 400);
  data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

  data.x = 250;
  data.y = 150;
  mlx_hook(data.mlx_win, KeyPress, 1L<<0, ft_key_press, &data);
  mlx_hook(data.mlx_win, KeyRelease, 1L<<1, ft_key_release, &data);
  mlx_loop_hook(data.mlx, main_loop, &data);
  mlx_loop(data.mlx);
  return (0);
}

```

### 1. 이벤트 생성하기
**`mlx_hook()`** 함수로 이벤트를 생성할 수 있습니다. **`mlx_key_hook()`**, **`mlx_mouse_hook()`**, **`mlx_expose_hook()`** 의 각각 특정 이벤트에 대한 정의를 **`mlx_hook()`** 을 사용하여 모두 처리할 수 있습니다.

```c
int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct_ptr)(), void *param);
```

이벤트를 생성하려는 윈도우의 식별자를 **`win_ptr`** 파리미터에 지정해 줍니다. **`x_event`**, **`x_mask`** 파라미터로 이벤트 상황을 지정해줍니다([X11/X.h 문서 참고](https://refspecs.linuxfoundation.org/LSB_3.2.0/LSB-Desktop-generic/LSB-Desktop-generic/libx11-ddefs.html)). **miniLibX**의 **`mlx_hook()`** 함수에서는 파라미터로 `x_mask`를 받지만 내부에서 사용을 하지 않으므로 0으로 값을 지정해도 무관합니다. **`funct_ptr`** 파라미터는 해당 이벤트가 발생할 때, 실행할 함수의 주소를 받는 함수 포인터 파라미터입니다. **`param`** 파라미터는 **`funct_ptr`** 로 호출한 함수에 필요한 파라미터 데이터를 보내주는 파라미터입니다.

### 2. 이벤트 수신하기
생성한 이벤트를 수신하기 위해서는 **`mlx_loop()`** 함수가 필요합니다. **`mlx_loop()`** 함수는 이벤트를 수신하고 연동된 함수를 호출하는 동작을 반복적으로 수행합니다.

### 3. 프레임 업데이트하기
이벤트를 수신하고 연동된 함수를 호출하여 키 입력에 대한 이미지의 x, y 좌표값 변경 작업을 성공적으로 수행했다 하더라도 화면에는 아직 반영이 되지 않았습니다. 다음 프레임에 변경된 사항을 업데이트 해주기 위해 필요한 함수가 바로 **`mlx_loop_hook()`** 함수입니다.

```c
int mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);
```

**`mlx_ptr`** 파라미터는 연결 식별자입니다. **`funct_ptr`** 파라미터, **`param`** 파라미터는 **`mlx_hook()`** 의 **`funct_ptr`** 파라미터, **`param`** 파라미터와 동일합니다.
**`mlx_loop_hook()`** 함수는 **`mlx_loop()`** 함수가 동작하는 동안 **`funct_ptr`** 파라미터로 받은 함수를 반복적으로 호출합니다. 그렇기 때문에 이미지를 그리는 함수를 **`funct_ptr`** 파라미터에 넣어주면 새로운 좌표값에 맞는 이미지를 다시 화면에 반영할 수 있게됩니다.

<p align="center"><img src="https://user-images.githubusercontent.com/19530862/99901744-5ab31a80-2cfc-11eb-8ea5-f050da4ff738.gif"></p>

## 참고
https://github.com/qst0/ft_libgfx#minilibx

https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html

https://github.com/l-yohai/cub3d/blob/master/mlx_example/05_sprite_raycast.c

## 3. 벡터 구조체 만들기
그래픽 연산을 하기 위해 필요한 벡터 구조체와 벡터 함수들을 만들겠습니다. 이 벡터 구조체로 색상, 위치, 방향 등등의 많은 것들을 표현할 수 있습니다.
먼저 벡터 구조체와 함수의 선언을 `vec3.h` 헤더 파일에 작성합니다.

### 1. 벡터 정의하기
**벡터 구조체**
```c
typedef struct s_vec3
{
  float        x;
  float        y;
  float        z;
}              t_vec3;
```

**벡터 사칙연산 함수**
```c
t_vec3  *ft_vec3_add(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_sub(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_multi(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_div(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_multi_float(t_vec3 *target, float t, t_vec3 *v);
t_vec3  *ft_vec3_div_float(t_vec3 *target, float t, t_vec3 *v);
```

**벡터 내적, 외적 연산 함수**
```c
float   ft_vec3_dot(t_vec3 *u, t_vec3 *v);
t_vec3  *ft_vec3_cross(t_vec3 *target, t_vec3 *u, t_vec3 *v);
```

**기타 함수**
```c
float   ft_vec3_len(t_vec3 *target);
float   ft_vec3_len_sqr(t_vec3 *target);
t_vec3  *ft_vec3_unit_vec(t_vec3 *target, t_vec3 *v);
t_vec3  *ft_vec3_set_xyz(t_vec3 *target, float x, float y, float z);
```

함수의 정의를 `vec3.c` 파일에 작성하겠습니다.
기본적으로 모든 함수는 함수 내에서 동적할당을 하지 않기 위해 매개변수로 `target`이라는 포인터 변수를 받아 함수 밖에서 동적할당한 변수에 접근하도록 작성했습니다.

**벡터 사칙연산 함수 정의**
```c
t_vec3  *ft_vec3_add(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->x + v->x;
  target->y = u->y + v->y;
  target->z = u->z + v->z;
  return (target);
}

t_vec3  *ft_vec3_sub(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->x - v->x;
  target->y = u->y - v->y;
  target->z = u->z - v->z;
  return (target);
}

t_vec3  *ft_vec3_multi(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->x * v->x;
  target->y = u->y * v->y;
  target->z = u->z * v->z;
  return (target);
}

t_vec3  *ft_vec3_div(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->x / v->x;
  target->y = u->y / v->y;
  target->z = u->z / v->z;
  return (target);
}

t_vec3  *ft_vec3_multi_float(t_vec3 *target, float t, t_vec3 *v)
{
  target->x = v->x * t;
  target->y = v->y * t;
  target->z = v->z * t;
  return (target);
}

t_vec3  *ft_vec3_div_float(t_vec3 *target, float t, t_vec3 *v)
{
  return (ft_vec3_multi_float(target, (1 / t), v));
}
```

**벡터 내적, 외적 연산 함수 정의**

```c
float   ft_vec3_dot(t_vec3 *u, t_vec3 *v)
{
  return (u->x * v->x + u->y * v->y + u->z * v->z);
}

t_vec3  *ft_vec3_cross(t_vec3 *target, t_vec3 *u, t_vec3 *v)
{
  target->x = u->y * v->z - u->z * v->y;
  target->y = u->z * v->x - u->x * v->z;
  target->z = u->x * v->y - u->y * v->x;
  return (target);
}
```

**기타 함수 정의**

```c
float   ft_vec3_len(t_vec3 *target)
{
  return (sqrt(ft_vec3_len_sqr(target)));
}

float   ft_vec3_len_sqr(t_vec3 *target)
{
  float result;

  result = pow(target->x, 2.0)
          + pow(target->y, 2.0)
          + pow(target->z, 2.0);
  return (result);
}

t_vec3  *ft_vec3_unit_vec(t_vec3 *target, t_vec3 *v)
{
  return (ft_vec3_div_float(target, ft_vec3_len(v)), v);
}

t_vec3  *ft_vec3_set_xyz(t_vec3 *target, float x, float y, float z)
{
  target->x = x;
  target->y = y;
  target->z = z;
  return (target);
}
```

### 2. 벡터 구조체로 이미지 생성하기

벡터 구조체를 이용하여 이미지를 만들어 보겠습니다. **`ft_draw()`** 함수로 윈도우의 좌표에 따라 색상을 계산하고 그 rgb값을 벡터 구조체인 `t_vec3` 타입의 `color`에 넣어 색상을 표현합니다.

```c
int ft_draw(t_data *data)
{
  int i;
  int j;
  t_vec3  color;

  j = data->height - 1;
  while (j >= 0)
  {
    i = 0;
    ft_putstr_fd("\rScanlines remaining: ", 1);
    ft_putnbr_fd(j, 1);
    ft_putchar_fd(' ', 1);
    while (i < data->width)
    {
      ft_vec3_set_xyz(&color, (float)i / (data->width - 1), (float)j / (data->height - 1), 0.25);
      my_mlx_pixel_put(data, i, data->height - 1 - j, &color);
      i++;
    }
    j--;
  }
  mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
  return (0);
}
```

윈도우의 왼쪽 상단이 원점입니다. (픽셀의 x좌표 / 너비), (픽셀의 y좌표 / 높이)로 r값과 g값을 지정하고 b값은 0.25로 고정합니다. 그다음 지난 시간에 구현했던 **`my_mlx_pixel_put()`** 함수로 픽셀의 색상을 이미지의 올바른 메모리 위치에 입력합니다. 완성한 **`ft_draw()`** 함수를 main문에 추가하여 실행하면 다음과 같은 이미지를 얻을 수 있습니다.

<p align="center"><img src="https://user-images.githubusercontent.com/19530862/100335935-e2f53080-3018-11eb-9cd8-eca44b0607cb.png"></p>

## 참고
https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class
