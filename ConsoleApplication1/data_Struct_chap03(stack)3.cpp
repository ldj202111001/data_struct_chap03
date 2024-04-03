/*
프로그램 내용: 스택을 이용한 괄호검사 프로그램
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

int check_matching(char expr[])
{
	int i = 0, prev;
	char ch;
	init_stack();
	while (expr[i] != '\0')
	{
		ch = expr[i++];
		if (ch == '[' || ch == '(' || ch == '{')
			push(ch);
		else if (ch == ']' || ch == ')' || ch == '}')
		{
			if (is_empty())
				return 2;
			prev = pop();
			if ((ch == ']' && prev != '[') ||
				(ch == ')' && prev != '(') ||
				(ch == '}' && prev != '{'))
			{
				return 3;
			}
		}	    
	}
	if (is_empty() == 0)
		return 1;

	return 0;
}

int main()
{
	char expr[4][80] = { "{A[(i+1)]=0;}", "if((i==0) && (j==0)",
                           "A[(i+1])=0;", "A[i] =f)(;" };
	int err, i;
	for (i = 0; i < 4; i++) {
		err = check_matching(expr[i]);
		if (err == 0)
			printf(" 괄호정상: %s\n", expr[i]);
		else
			printf(" 괄호오류: %s (조건%d 위반)\n", expr[i], err);
	}

}