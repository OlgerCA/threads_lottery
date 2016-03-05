#include "FileLoader.h"

const char *SEPARATOR = ":";

const char *SEPARATOR_LIST = ",";

const char *TYPE_TAG = "type";
const char *NUM_THREADS_TAG = "numThreads";
const char *TICKETS_TAG = "tickets";
const char *WORK_TAG = "work";
const char *LIMIT_TAG = "limit";

//Free any allocated memory of the File Loader
void FileLoader_Free(FileLoader *this) {
    free(this->tickets);
    free(this->work);
    free(this);
}

//Creates a new File Loader
void FileLoader_Init(char *fileName) {
    Loader = (FileLoader*) (malloc(sizeof(FileLoader)));

    FILE *settingsFile = fopen(fileName, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (settingsFile == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, settingsFile)) != -1) {
        char *token;
        token = strtok(line, SEPARATOR);
        if (strcmp(token, TYPE_TAG) == 0) {
            token = strtok(NULL, SEPARATOR);
            Loader->preemptive = (int) strtol(token, (char **)NULL, 10);
        } else if (strcmp(token, NUM_THREADS_TAG) == 0) {
            token = strtok(NULL, SEPARATOR);
            Loader->numThreads = (int) strtol(token, (char **)NULL, 10);
            Loader->tickets = (long*) malloc(Loader->numThreads * sizeof(long));
            Loader->work = (long*) malloc(Loader->numThreads * sizeof(long));
        } else if (strcmp(token, TICKETS_TAG) == 0) {
            token = strtok(NULL, SEPARATOR);
            char *work = strtok(token, SEPARATOR_LIST);
            int index = 0;
            while(work != NULL && index < Loader->numThreads){
                Loader->tickets[index] = strtol(work, (char **)NULL, 10);
                work = strtok(NULL, SEPARATOR_LIST);
                index++;
            }
        } else if (strcmp(token, WORK_TAG) == 0) {
            token = strtok(NULL, SEPARATOR);
            char *work = strtok(token, SEPARATOR_LIST);
            int index = 0;
            while(work != NULL && index < Loader->numThreads) {
                Loader->work[index] = strtol(work, (char **) NULL, 10);
                work = strtok(NULL, SEPARATOR_LIST);
                index++;
            }
        } else if (strcmp(token, LIMIT_TAG) == 0) {
            token = strtok(NULL, SEPARATOR);
            Loader->limit = (unsigned int) strtol(token, (char **) NULL, 10);
        } else {
            printf("Unknown setting\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(settingsFile);
    if (line)
        free(line);
}
