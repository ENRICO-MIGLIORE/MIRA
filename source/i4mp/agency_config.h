#ifndef AGENCY_CONFIG_H
#define AGENCY_CONFIG_H


#define AGENCY__CONFIG__MAX_PATH_SIZE                                    1024
#define AGENCY__CONFIG__SDB_FIELDS_MAX                                   64
#define AGENCY__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define AGENCY__CONFIG__BUFFER_SIZE                                      1024
#define AGENCY__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS                   5
#define AGENCY__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE                    60
#define AGENCY__CONFIG__TOKENS_MAX                                       32

#define AGENCY__CONFIG__MIN_PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE      5
#define AGENCY__CONFIG__CONNECTION_TIME_INTERVAL       60

#define AGENCY__CONFIG__INITIAL_VALUE_OF_PART_COUNTER_IN_SIMULATION_MODE           100


//#define AGENCY__CONFIG__CONNECTION_TIMEOUT            5

//#define AGENCY__AVERAGE_CYCLE_TIME_IN_SIMULATION_MODE                  30.0


//#define AGENCY__TYPE_1                                                   1


#define AGENCY__FILE_CONFIG_MODE                                 0
#define AGENCY__BUFFER_CONFIG_MODE                               1
#define AGENCY__UNESCAPE_SEQUENCE                                "!s"
#define AGENCY__UNESCAPE_SEQUENCE_LEN                            2
#define AGENCY__UNESCAPE_REPLACEMENT_CHAR                        ';'
#define AGENCY__FIELDS_SEPARATORS                                {";"}
#define AGENCY__FIELDS_SEPARATORS_MAX                            1
#define AGENCY__CHARACTER_TO_TRIM                                ' '



#define AGENCY__MACHINE_ID                                                   0
#define AGENCY__MACHINE_NAME                                                 1
#define AGENCY__MACHINE_PART_COUNTER                                       100
#define AGENCY__MACHINE_CYCLE_TIME                                         101
#define AGENCY__MACHINE_PART_PROGRAM_NAME                                  102
#define AGENCY__MACHINE_STATUS_RUN                                         103
#define AGENCY__MACHINE_STATUS_ALARM                                         104


#endif

