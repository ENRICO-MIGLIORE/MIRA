#include "users.h"
#include "sessions.h"


static char *fn = "sessions__load__sessions()";


//FGG__CONFIG__SYSTEM__USERS_MAX

int sessions__load__sessions (void)
{
	int rc;
	unsigned long size;
	unsigned long len;
	unsigned long i;
	int active;
	unsigned long k;
	unsigned long fk_user_pk_id;
	unsigned long status_session;
	int exit;

	rc = users__sdb__select_active_count_from_users (&sessions->data_count);
	if (rc != 0)
	{
		utils__printf__error(fn, -10, "users__sdb__select_active_count_from_users() error");
		return -10;
	}

	size = sizeof(sessions__data_t);
	size = size * sessions->data_count;
	sessions->data = (sessions__data_t *) malloc(size);

	if (sessions->data == NULL)
	{
		utils__printf__error(UTILS__ERROR, fn, -10, "malloc() error");
		return -10;
	}

	memset (sessions->data, 0, size);


	for (i = 0; i < sessions->file_sdb[0].record_count; i++)
	{
		rc = sessions__sdb__select_session_from_sessions(i+1, &sessions->sdb, 0, SDB__DEFAULT_READ_LANG);
		if (rc != 0)
		{
			utils__printf(UTILS__ERROR, fn, -10, "sessions__sdb__select_session_from_sessions() error");
			return -10;
		}

		if (active != FGGR__RECORD_ACTIVE)
		{
			continue;
		}

		rc = utils__libc__atoul (sessions->sdb.value[SESSIONS__FIELD__FK_USERS_PK_ID], sessions->sdb.value_len[SESSIONS__FIELD__FK_USERS_PK_ID], &fk_user_pk_id);
		if (rc != 0)
		{
			utils__printf(UTILS__ERROR, fn, -20, "utils__libc__atoul() returned %d", rc);
			return 1;
		}

		rc = utils__libc__atoul (sessions->sdb.value[SESSIONS__FIELD__STATUS], sessions->sdb.value_len[SESSIONS__FIELD__STATUS], &status_session);
		if (rc != 0)
		{
			utils__printf(UTILS__ERROR, fn, -20, "utils__libc__atoul() returned %d", rc);
			return 1;
		}

		exit = 0;
		for (k = 0; (k < sessions->data_count) && (exit == 0); k++)
		{
			
			if (sessions->data[k].user_pk_id == fk_user_pk_id)
			{
				len = strlen (sessions->data[k].id);
				if (len == sessions->sdb.value_len[SESSIONS__FIELD__SESSION_ID])
				{
				    rc = memcmp(sessions->data[k].id, sessions->sdb.value[SESSIONS__FIELD__SESSION_ID], len);
				    if (rc == 0)
				    {
				        sessions->data[k].status = (int) status_session;
				        memcpy(sessions->data[k].time, sessions->sdb.value[SESSIONS__FIELD__TIME], sessions->sdb.value_len[SESSIONS__FIELD__TIME]);
				        memcpy(sessions->data[k].date, sessions->sdb.value[SESSIONS__FIELD__DATE], sessions->sdb.value_len[SESSIONS__FIELD__DATE]);
				
				        exit = 1;
				    }
				}

				if (exit == 0)
				{
					//e' un problema
				}

			}
			else if (sessions->data[k].user_pk_id == 0)
			{
				sessions->data[k].user_pk_id = fk_user_pk_id;
				sessions->data[k].status = (int) status_session;
				memcpy(sessions->data[k].time, sessions->sdb.value[SESSIONS__FIELD__TIME], sessions->sdb.value_len[SESSIONS__FIELD__TIME]);
				memcpy(sessions->data[k].date, sessions->sdb.value[SESSIONS__FIELD__DATE], sessions->sdb.value_len[SESSIONS__FIELD__DATE]);
				memcpy(sessions->data[k].id, sessions->sdb.value[SESSIONS__FIELD__SESSION_ID], sessions->sdb.value_len[SESSIONS__FIELD__SESSION_ID]);
				exit = 1;
			}
		}
		
	}



	return 0;

}

