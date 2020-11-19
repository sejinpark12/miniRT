## 1. 준비하기

#### 1. miniLibX를 사용하여 윈도우 생성

**miniRT/cub3d** 프로젝트는 **miniLibX** 그래픽 라이브러리를 사용하여 구현합니다.
그러므로 먼저 **miniLibX**로 윈도우를 생성해보겠습니다.

```c
#include "mlx/mlx.h"

typedef struct 	s_data
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 600, 400, "miniRT");
	img.img = mlx_new_image(mlx, 600, 400);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(t_data *data, int x, int y, 0x0000FF00);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
```

1. 그래픽 시스템 연결
	우선, 작성한 프로그램과 디스플레이 사이의 연결을 초기화하기 위해서 **`mlx_init()`** 함수를 호출합니다. 연결이 성공했다면 **`mlx_init()`** 는 **`void *`** 타입의 포인터를 **연결 식별자로 반환**합니다.([mlx man](https://github.com/psj3205/MiniLibX_man_kor/blob/main/mlx.md)을 참고하세요.)
2. 윈도우 생성
	**`mlx_new_window()`** 함수로 새로운 윈도우를 생성할 수 있습니다.

	```c
	void * mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
	```

	**`size_x`**, **`size_y`** 매개변수로 윈도우의 너비, 높이를 설정할 수 있습니다. **`title`** 매개변수는 타이틀 바의 제목입니다. **`mlx_new_window()`** 가 성공적으로 새로운 윈도우를 생성했다면 **`void *`** 타입의 포인터를 **윈도우 식별자로 반환**합니다.([mlx_new_window man](https://github.com/psj3205/MiniLibX_man_kor/blob/main/mlx_new_window.md)을 참고하세요.)
3. 이미지 생성
	**`mlx_new_image()`** 함수는 새로운 이미지를 생성합니다.

	```c
	void *mlx_new_image(void *mlx_ptr, int width, int height);
	```

	**`width`**, **`height`** 파라미터로 이미지의 크기를 설정합니다. **`mlx_init()`** 호출로 반환 받은 연결 식별자를 **`mlx_ptr`** 파라미터에 지정합니다. **`mlx_new_image()`** 가 성공적으로 새로운 이미지를 생성했다면 **`void *`** 타입의 **식별자를 반환**합니다.([mlx_new_image man](https://github.com/psj3205/MiniLibX_man_kor/blob/main/mlx_new_image.md)을 참고하세요.)
4. 생성된 이미지의 정보 설정
	**`mlx_get_data_addr()`** 함수는 생성된 이미지에 대한 정보를 설정합니다.

	```c
	char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
	```

	**`img_ptr`** 파라미터로는 사용할 이미지를 지정합니다. **`mlx_get_data_addr()`** 는 이미지가 저장되어 있는 메모리의 시작 지점의 주소를 **`char *`** 형 포인터로 반환합니다. **`mlx_get_data_addr()`** 이 성공적으로 호출된다면 다음 세 개의 파라미터에 값이 지정됩니다. **`bits_per_pixel`** 파라미터에는 픽셀의 색상을 표현하는데 필요한 비트의 수가 입력됩니다.**`size_line`** 파라미터에는 이미지 한 줄을 저장하는데 필요한 바이트 수가 입력됩니다. **`endian`** 파라미터는 픽셀 색상의 저장 방식이 little endian(0 지정)인지 big endian(1 지정)인지를 나타냅니다.([mlx_new_image man](https://github.com/psj3205/MiniLibX_man_kor/blob/main/mlx_new_image.md)을 참고하세요.)
5. 이미지 그리기
	**`mlx_put_image_to_window()`** 함수로 특정 윈도우 안에 이미지를 그릴 수 있습니다.

	```c
	int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
	```

	앞의 세 가지 파라미터는 위에서 생성한 mlx, 윈도우, 이미지의 식별자를 지정합니다. **`x`**, **`y`** 파라미터로 윈도우 안 내에서 이미지의 좌표를 지정합니다.

#### 2. 참고
https://github.com/qst0/ft_libgfx#minilibx

https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html
