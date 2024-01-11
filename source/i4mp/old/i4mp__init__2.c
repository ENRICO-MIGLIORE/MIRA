#include "mira__private.h"
#include "i4mp.h"


static char *fn = "i4mp__init()";


i4mp_t* i4mp;

int i4mp__init__2 (int argc, char* argv[], i4mp__agent_t* agents, size_t agents_max)
{

	int rc;
	size_t size;
	int i;


	/*
	 * allocate the middleware struct
	 */
	i4mp = (i4mp_t*)malloc(sizeof(i4mp_t));
	if (i4mp == NULL)
	{
		printf("error in function %s - malloc() error\n", fn);
		return -100;
	}
	memset(i4mp, '\0', sizeof(i4mp_t));



	/*
	 * allocate the agents
	 */
	size = sizeof(i4mp__agent_t) * agents_max;
	i4mp->agents = (i4mp__agent_t*)malloc(size);
	if (i4mp->agents == NULL)
	{
		printf("error in function %s - malloc() agents returned NULL\n", fn);
		return -200;
	}
	memset(i4mp->agents, '\0', size);

	i4mp->agent_count = (int)agents_max;


	/*
	 * allocate an array of integers
	 */
	size = sizeof(int) * agents_max;
	i4mp->agents_machine_count = (int*)malloc(size);

	
	/*
	 * allocate an array of size_t
	 */
	size = sizeof(size_t) * i4mp->agent_count;
	i4mp->buffer_size = (size_t*)malloc(size);


	/*
	 * allocate an array of size_t
	 */
	size = sizeof(char*) * i4mp->agent_count;
	i4mp->buffer = (char**)malloc(size);


	/*
	 * allocate an array of buffers
	 */
	for (i = 0; i < i4mp->agent_count; i++)
	{
		size = sizeof(char) * agents[i].buffer_size;

		i4mp->buffer[i] = (char*)malloc(size);

		i4mp->buffer_size[i] = size;
	}


	/*
	 * load the agents
	 */
	for (i = 0; i < i4mp->agent_count; i++)
	{
		rc = i4mp__load_agent(i, &agents[i]);
		if (rc != 0)
		{
			printf("error in function %s - i4mp__load_agent() returned %d\n", fn, rc);
			return -300;
		}
	}





	/*
	 * call agents' init() function
	 */
	for (i = 0; i < i4mp->agent_count; i++)
	{
		rc = i4mp->agents[i].init(argc, argv);
		if (rc != 0)
		{
			printf("error in function %s - %s returned %d\n", fn, i4mp->agents[i].init__function_name, rc);
			return -400;
		}
	}


	return 0;
}


