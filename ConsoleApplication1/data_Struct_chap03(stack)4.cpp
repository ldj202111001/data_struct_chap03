/*
프로그램 내용: 스택을 이용한 후위 표기 수식의 계산 프로그램
실습날짜: 2024-04-03
학번: 202111001
이름: 이동재
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;

//스택구현
element data[MAX_STACK_SIZE];
int top;

void error(const char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_stack() { top = -1; }  // 스택 초기화
int size() { return top + 1; }
int is_empty() { return (top == -1); }
int is_full() { return (top == MAX_STACK_SIZE - 1); }

void push(element e)
{
	if (is_full())
		error("스택 포화 에러");
	else
		data[++top] = e;
}

element pop()
{
	if (is_empty())
		error("스택 공백 에러");
	else
		return data[top--];
}

element peek()
{
	if (is_empty())
		error("스택 공백 에러");
	else
		return data[top];
}

double calc_postfix(char expr[]) 
{
	char c;
	int i = 0;
	double val, val1, val2;

	init_stack();
	while (expr[i] != '\0') //문자열이 끝날때 까지 반복
	{
		c = expr[i++];
		if (c >= '0' && c <= '9')  // c가 숫자라면
		{
			val = c - '0';
			push(val);
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') // c가 연산자라면
		{
			val2 = pop();
			val1 = pop();
			switch (c)
			{
			case '+': push(val1 + val2); break;
			case '-': push(val1 - val2); break;
			case '*': push(val1 * val2); break;
			case '/': push(val1 / val2); break;
			}
		}
	}
	return pop();

}

void main()
{
    char expr[2][80] = { "8 2 / 3- 3 2 * +", "1 2 / 4 * 1 4 / *" };
	printf("수식: %s = %lf\n", expr[0], calc_postfix(expr[0]));
	printf("수식: %s = %lf\n", expr[1], calc_postfix(expr[1]));
}