# Libft

## 목록
  Part1 Functions
  [1. ft_memset](#ft_memset)
  [2. ft_bzero](#ft_bzero)
  [3. ft_memcpy](#ft_memcpy)
  [4. ft_memccpy](#ft_memccpy)
  [5. ft_memmove](#ft_memmove)
  [6. ft_memchr](#ft_memchr)
  [7. ft_memcmp](#ft_memcmp)
  [8. ft_strlen](#ft_strlen)
  [9. ft_strlcpy](#ft_strlcpy)
  [10. ft_strlcat](#ft_strlcat)
  [11. ft_strchr](#ft_strchr)
  [12. ft_strrchr](#ft_strrchr)
  [13. ft_strnstr](#ft_strnstr)
  [14. ft_strncmp](#ft_strncmp)
  [15. ft_atoi](#ft_atoi)
  [16. ft_isalpha](#ft_isalpha)
  [17. ft_isdigit](#ft_isdigit)
  [18. ft_isalnum](#ft_isalnum)
  [19. ft_isascii](#ft_isascii)
  [20. ft_isprint](#ft_isprint)
  [21. ft_toupper](#ft_toupper)
  [22. ft_tolower](#ft_tolower)

  Part2 Functions

  Bonus Functions

## 1. Part1 Functions
### ft_memset
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  | void *ft_memset(void *b, int c, size_t len) | ft_memset(str, 65, 10); | b에 len 개수만큼 c를 채우는 함수 |
  - 매개변수 **`int c`를 `unsigned char c`로** 형변환 시킨 후 b에 대입한다.
  - 반환값은 **`b`의 시작주소**
---
### ft_bzero
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  | void ft_bzero(void *s, size_t n) | ft_bzero(str, 10); | s에 n 개수만큼 0을 채우는 함수 |
  - 오로지 0으로 값을 채우는 것을 제외하고 **ft_memset**과 동일한 로직으로 작동
---
### ft_memcpy
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  | void *ft_memcpy(void *restrict dst, const void *restrict src, size_t n) | ft_memcpy(dst, src, 10); | src 위치의 메모리 n만큼 dst에 복사하는 함수 |
  - dst와 src가 **오버랩되는 상황은 정의되어 있지않기 때문에** 제대로 복사가 안됨.
    - `string = "apple"`이고 `ft_memcpy(str[2], str[0], 3)`을 실행한다면
      - **a p p l e** ===> 초기 상태
      - **a p a l e** ===> str[0]이 str[2]로 대입되어 ***나중에 복사해야할 str[2]값이 사라진다.***
      - **a p a p e** ===> str[1]이 str[3]에 복사
      - **a p a p a** ===> 원래 str[2]값이 아닌 새로 복사된 str[2]이 str[4]에 복사되어 문제가 발생
    - 기대했던 **a p a p p**가 아니라 **a p a p a**가 리턴된다.

  - **ft_memmove**함수를 사용하면 오버랩이 되어도 메모리가 안전하게 복사됨
  - dst와 src가 모두 `NULL`일 경우 `NULL`을 리턴
  - **restrict** 키워드?
---
### ft_memccpy
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_memmove
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_memchr
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_memcmp
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_strlen
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_strlcpy
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_strlcat
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_strchr
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_strrchr
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_strnstr
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_strncmp
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_atoi
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_isalpha
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_isdigit
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_isalnum
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_isascii
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_isprint
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_toupper
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
### ft_tolower
  | 함수의 원형 | 예  | 설명  |
  | --- | ---- | -------- |
  |  |  |  |
---
## 2. Part2 Functions

## 3. Bonus Functions
