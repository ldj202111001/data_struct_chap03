/*
���α׷� ����: ������ �̿��� ���� ǥ�� ��ȯ ���α׷� // ���� ǥ�� ��ģ��
�ǽ���¥: 2024 - 04 - 05
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
		data[++top] = e; // top�� ++�ϰ� ���� ����
}

element pop()
{
	if (is_empty())
		error("���� ���� ����");
	else
		return data[top--]; // top �� --�ϰ� ���� ������
}

element peek()
{
	if (is_empty())
		error("���� ���� ����");
	else
		return data[top];
}

int precedence(char op)  // �������� �켱������ ��ȯ�ϴ� �Լ� ( �������� �켱������ ����)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1; // �߸��Է��� ���
}

void infix_to_postfix(char expr[])
{
	
	int i = 0;
	char c, op; // c: ����, op: ����

	init_stack();
	while (expr[i] != '\0') // ���ڿ��� ������ ���� �ݺ�
	{
		c = expr[i++];
		if ((c >= '0' && c <= '9')) // �ǿ�����(����) �� ���
		{
			printf("%c", c);
		}
		else if (c == '(')
			push(c);
		else if (c == ')') // ������ ��ȣ�� ���
		{
			while (is_empty() == 0)
			{
				op = pop(); // ���ÿ��� ����
				if (op == '(') break; // ���� ��ȣ�� ������ ����
				else printf("%c", op);
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') // �������� ���
		{
			while (is_empty() == 0) // ������ ����ִٸ�
			{
				op = peek(); // op: ������ top�� �ִ� ������
				if (precedence(c) <= precedence(op))  // ���� ���õ� �����ڿ� ������ top���ִ� �������� �켱������ ���Ѵ�.
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
	printf("��������: %s ==> ��������:", expr[0]);
	infix_to_postfix(expr[0]);
	printf("��������: %s ==> ��������:", expr[1]);
	infix_to_postfix(expr[1]);
}