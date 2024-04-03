/*
���α׷� ����: ������ �̿��� ��ȣ�˻� ���α׷�
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
			printf(" ��ȣ����: %s\n", expr[i]);
		else
			printf(" ��ȣ����: %s (����%d ����)\n", expr[i], err);
	}

}