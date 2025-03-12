#include <libc.h>

int main(int ac, char **av, char **ev)
{
	for (int i = 0; ev[i]; i++)
	{
		printf("%s\n", ev[i]);
	}
}