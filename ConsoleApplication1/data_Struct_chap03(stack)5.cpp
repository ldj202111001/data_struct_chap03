/*
프로그램 내용: 스택을 이용한 후위 표기 변환 프로그램 // 후위 표기 합친기
실습날짜: 2024 - 04 - 05
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
		data[++top] = e; // top을 ++하고 값을 넣음
}

element pop()
{
	if (is_empty())
		error("스택 공백 에러");
	else
		return data[top--]; // top 을 --하고 값을 추출함
}

element peek()
{
	if (is_empty())
		error("스택 공백 에러");
	else
		return data[top];
}

int precedence(char op)  // 연산자의 우선순위를 반환하는 함수 ( 높을수록 우선순위가 높다)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1; // 잘못입력한 경우
}

void infix_to_postfix(char expr[])
{
	
	int i = 0;
	char c, op; // c: 현재, op: 스택

	init_stack();
	while (expr[i] != '\0') // 문자열이 끝날때 까지 반복
	{
		c = expr[i++];
		if ((c >= '0' && c <= '9')) // 피연산자(숫자) 일 경우
		{
			printf("%c", c);
		}
		else if (c == '(')
			push(c);
		else if (c == ')') // 닫히는 괄호일 경우
		{
			while (is_empty() == 0)
			{
				op = pop(); // 스택에서 꺼냄
				if (op == '(') break; // 여는 괄호를 만날때 까지
				else printf("%c", op);
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') // 연산자일 경우
		{
			while (is_empty() == 0) // 스택이 비어있다면
			{
				op = peek(); // op: 스택의 top에 있는 연산자
				if (precedence(c) <= precedence(op))  // 현재 선택된 연산자와 스택의 top에있는 연산자의 우선순위를 비교한다.
				{
					printf("%c", op);
					pop();
				}
				else break;
			}
			push(c);
		}
	}

	while (is_empty() == 0)
	{
		printf("%c", pop());
	}
	printf("\n");
}

int main()
{
	char expr[2][80] = { "8/2-3+(3*2)", "1/2* 4 * (1/4)" };
	printf("중위수식: %s ==> 후위수식:", expr[0]);
	infix_to_postfix(expr[0]);
	printf("중위수식: %s ==> 후위수식:", expr[1]);
	infix_to_postfix(expr[1]);
}
