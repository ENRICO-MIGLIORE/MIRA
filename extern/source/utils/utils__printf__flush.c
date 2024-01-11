#include "utils__libc.h"
#include "utils__printf.h"


int utils__printf__flush (utils__printf_t* pf, char** token, int* token_type, size_t tokens_max)
{
	size_t i;
	size_t len;	
	FILE* f;
	size_t white_spaces_len;
	char white_spaces[96];  /* the minimum white_spaces size is 64 */
	size_t white_spaces_size;

	if (pf == NULL)
	{
		return -100;
	}

	if (tokens_max == 0)
	{
		return -200;
	}

	for (i = 0; i < tokens_max; i++)
	{
		if (token[i] == NULL)
		{
			return -300;
		}
	}

	white_spaces_size = sizeof(white_spaces);
	memset(white_spaces, ' ', white_spaces_size - 1);
	white_spaces[white_spaces_size - 1] = '\0';


	if (pf->config.enable_printf != 0)
	{
		if (pf->config.enable_table_layout_output != 0)
		{
			for (i = 0; i < tokens_max; i++)
			{
				if (i < tokens_max - 1)
				{

					if (token_type[i] == pf->info)
					{
						printf("%s      ", token[i]);
					}
					else if (token_type[i] == pf->error)
					{
						printf("%s     ", token[i]);
					}
					else if (token_type[i] == pf->warning)
					{
						printf("%s   ", token[i]);
					}
					else
					{
						if (i == 0)
						{
							printf("\"%s\"  ", token[i]);
						}
						else
						{
							printf("%s  ", token[i]);
						}
						

						if (i == 0)
						{
							/*
							 * section name
							 */
							len = strlen(token[i]);
							if (len < 32)
							{
								white_spaces_len = (size_t)(32 - len);
								printf("%.*s", (int) white_spaces_len, white_spaces);
							}
						}
						else if (i == 4)
						{
							/*
							 * function name
							 */
							len = strlen(token[i]);
							if (len < 64)
							{
								white_spaces_len = (size_t)(64 - len);
								printf("%.*s", (int) white_spaces_len, white_spaces);
							}
						}
						else if (i == 5)
						{
							/*
							 * function return code
							 */
							printf("  ");
						}
					}
				}
				else
				{
					/*
					 * message
					 */
					printf("\"%s\"", token[i]);
				}
			}
		}
		else
		{
			for (i = 0; i < tokens_max; i++)
			{
				printf("%s ", token[i]);
			}
		}

		printf("\n");
	}

	if (pf->log_file_flood_in_progress >= 4)
	{
		return 0;
	}

	if (pf->log_file_flood_in_progress == 3)
	{
		pf->log_file_flood_in_progress = 4;
	}


	if ((pf->config.enable_log_file != 0) && (pf->config.log_file_name_len > 0))
	{


		f = fopen(pf->config.log_file_name, "ab");

		if (f == NULL)
		{
			return -200;
		}


		if (pf->config.enable_table_layout_output != 0)
		{
			for (i = 0; i < tokens_max; i++)
			{
				if (i < tokens_max - 1)
				{

					if (token_type[i] == pf->info)
					{
						fprintf(f, "%s      ", token[i]);
					}
					else if (token_type[i] == pf->error)
					{
						fprintf(f, "%s     ", token[i]);
					}
					else if (token_type[i] == pf->warning)
					{
						fprintf(f, "%s   ", token[i]);
					}
					else
					{
						if (i == 0)
						{
							fprintf(f, "\"%s\"  ", token[i]);
						}
						else
						{
							fprintf(f, "%s  ", token[i]);
						}


						if (i == 0)
						{
							/*
							 * section name
							 */
							len = strlen(token[i]);
							if (len < 32)
							{
								white_spaces_len = (size_t)(32 - len);
								fprintf(f, "%.*s", (int)white_spaces_len, white_spaces);
							}
						}
						else if (i == 4)
						{
							/*
							 * function name
							 */
							len = strlen(token[i]);
							if (len < 64)
							{
								white_spaces_len = (size_t)(64 - len);
								fprintf(f, "%.*s", (int)white_spaces_len, white_spaces);
							}
						}
						else if (i == 5)
						{
							/*
							 * function return code
							 */
							fprintf(f, "  ");
						}
					}
				}
				else
				{
					/*
					 * message
					 */
					fprintf(f, "\"%s\"", token[i]);
				}
			}
		}
		else
		{
			for (i = 0; i < tokens_max; i++)
			{
				fprintf(f, "%s ", token[i]);
			}
		}


		/*
		 * End of line signature
		 */
		fprintf(f, "\r\n");

		fclose(f);

		pf->log_file_line_count++;
	}

	return 0;
}



//int utils__printf__flush__good(utils__printf_t* pf, char** token, int* token_type, size_t tokens_max)
//{
//	size_t i;
//	size_t len;
//	FILE* f;
//	size_t white_spaces_len;
//	char white_spaces[32];
//	size_t white_spaces_size;
//
//	if (pf == NULL)
//	{
//		return -100;
//	}
//
//	if (tokens_max == 0)
//	{
//		return -110;
//	}
//
//	for (i = 0; i < tokens_max; i++)
//	{
//		if (token[i] == NULL)
//		{
//			return -120;
//		}
//	}
//
//	white_spaces_size = sizeof(white_spaces);
//	memset(white_spaces, ' ', white_spaces_size - 1);
//	white_spaces[white_spaces_size - 1] = '\0';
//
//
//	if (pf->config.enable_printf != 0)
//	{
//		if (pf->config.enable_table_layout_output != 0)
//		{
//			for (i = 0; i < tokens_max; i++)
//			{
//				if (i < tokens_max - 1)
//				{
//
//					if (token_type[i] == pf->info)
//					{
//						printf("[%s]      ", token[i]);
//					}
//					else if (token_type[i] == pf->error)
//					{
//						printf("[%s]     ", token[i]);
//					}
//					else if (token_type[i] == pf->warning)
//					{
//						printf("[%s]   ", token[i]);
//					}
//					else
//					{
//						printf("[%s]  ", token[i]);
//
//						if (i == 0)
//						{
//							/*
//							 * Section name
//							 */
//							len = strlen(token[i]);
//							if (len < white_spaces_size - 2)
//							{
//								white_spaces_len = (size_t)(white_spaces_size - 2 - len);
//								printf("%.*s", (int)white_spaces_len, white_spaces);
//							}
//						}
//					}
//				}
//				else
//				{
//					printf("[%s]", token[i]);
//				}
//			}
//		}
//		else
//		{
//			for (i = 0; i < tokens_max; i++)
//			{
//				printf("%s ", token[i]);
//			}
//		}
//
//		printf("\n");
//	}
//
//	if (pf->log_file_flood_in_progress >= 4)
//	{
//		return 0;
//	}
//
//	if (pf->log_file_flood_in_progress == 3)
//	{
//		pf->log_file_flood_in_progress = 4;
//	}
//
//
//	if ((pf->config.enable_log_file != 0) && (pf->config.log_file_name_len > 0))
//	{
//
//		f = fopen(pf->config.log_file_name, "ab");
//
//		if (f == NULL)
//		{
//			return -200;
//		}
//
//		if (pf->config.enable_table_layout_output != 0)
//		{
//
//			for (i = 0; i < tokens_max; i++)
//			{
//				if (i < tokens_max - 1)
//				{
//
//					if (token_type[i] == pf->info)
//					{
//						fprintf(f, "[%s]      ", token[i]);
//					}
//					else if (token_type[i] == pf->error)
//					{
//						fprintf(f, "[%s]     ", token[i]);
//					}
//					else if (token_type[i] == pf->warning)
//					{
//						fprintf(f, "[%s]   ", token[i]);
//					}
//					else
//					{
//						fprintf(f, "[%s]  ", token[i]);
//
//						if (i == 0)
//						{
//							/*
//							 * Section name
//							 */
//							len = strlen(token[i]);
//							if (len < white_spaces_size - 2)
//							{
//								white_spaces_len = (size_t)(white_spaces_size - 2 - len);
//								fprintf(f, "%.*s", (int)white_spaces_len, white_spaces);
//							}
//						}
//					}
//				}
//				else
//				{
//					fprintf(f, "[%s]", token[i]);
//				}
//			}
//		}
//		else
//		{
//			for (i = 0; i < tokens_max; i++)
//			{
//				fprintf(f, "%s ", token[i]);
//			}
//		}
//
//
//		/*
//		 * End of line signature
//		 */
//		fprintf(f, "\r\n");
//
//		fclose(f);
//
//		pf->log_file_line_count++;
//	}
//
//	return 0;
//}
