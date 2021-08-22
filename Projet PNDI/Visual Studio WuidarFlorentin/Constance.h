#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILE_DATA_SUBJECT_INFO "data_subjects_info.csv"
#define FILE_TRAIN_SET "train_set.csv"
#define FILE_TEST_SET "test_set.csv"
#define FILE_MODEL "fi_model.csv"
#define FILE_MODEL_MEN "fi_model_men.csv"
#define FILE_MODEL_WOMEN "fi_model_women.csv"
#define NB_PATH 15
#define NB_FILES 24
#define NB_LINES 600
#define PATHLENGHT 23
#define square(nb) (nb)*(nb)
#define PAUSE system("Pause")

typedef enum typeMovement TypeMovement;
enum typeMovement
{
	DOWNSTAIRS = 1,
	UPSTAIRS,
	JOGGING,
	SITTING,
	STANDUP,
	WALKING
};

typedef struct dataSubjectInfo DataSubjectInfo;
struct dataSubjectInfo
{
	int code;
	int weight;
	int height;
	int age;
	int genre;
};

typedef struct data Data;
struct data
{
	int movement;
	int genre;
	int index;
	double vacc[NB_LINES];
};

typedef struct movement Movement;
struct movement {
	int index;
	double attitudeRoll;
	double attitudePitch;
	double attitudeYaw;
	double gravityX;
	double gravityY;
	double gravityZ;
	double rotationRateX;
	double rotationRateY;
	double rotationRateZ;
	double userAccelerationX;
	double userAccelerationY;
	double userAccelerationZ;
};

typedef struct fiModel FiModel;
struct fiModel {
	int movement;
	double vacc[NB_LINES];
};

int readMouvement(char paths[][PATHLENGHT], int indPath);
void initDataSubjectInfo(FILE* pDataSubjectInfo, DataSubjectInfo dataSubjectInfo[NB_FILES]);
int readGenre(DataSubjectInfo dataSubjectInfo[NB_FILES], int indFile);
void createPath(char pathFile[PATHLENGHT], char paths[][PATHLENGHT], int indPath, int indFile);
void readInFiModel(FILE* pFile, FiModel fiModel);