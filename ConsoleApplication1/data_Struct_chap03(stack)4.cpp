/*
���α׷� ����: ������ �̿��� ���� ǥ�� ������ ��� ���α׷�
�ǽ���¥: 2024-04-03
�й�: 202111001
�̸�: �̵���
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;

//���ñ���
element data[MAX_STACK_SIZE];
int top;

void error(const char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_stack() { top = -1; }  // ���� �ʱ�ȭ
int size() { return top + 1; }
int is_empty() { return (top == -1); }
int is_full() { return (top == MAX_STACK_SIZE - 1); }

void push(element e)
{
	if (is_full())
		error("���� ��ȭ ����");
	else
		data[++top] = e;
}

element pop()
{
	if (is_empty())
		error("���� ���� ����");
	else
		return data[top--];
}

element peek()
{
	if (is_empty())
		error("���� ���� ����");
	else
		return data[top];
}

double calc_postfix(char expr[]) 
{
	char c;
	int i = 0;
	double val, val1, val2;

	init_stack();
	while (expr[i] != '\0') //���ڿ��� ������ ���� �ݺ�
	{
		c = expr[i++];
		if (c >= '0' && c <= '9')  // c�� ���ڶ��
		{
			val = c - '0';
			push(val);
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') // c�� �����ڶ��
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
	printf("����: %s = %lf\n", expr[0], calc_postfix(expr[0]));
	printf("����: %s = %lf\n", expr[1], calc_postfix(expr[1]));
}