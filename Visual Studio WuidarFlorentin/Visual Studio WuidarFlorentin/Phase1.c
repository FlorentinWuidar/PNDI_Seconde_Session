#include "Constance.h"

void main(void) {

	FILE* pDataSubjectInfo = NULL;
	FILE* pTrainSet = NULL;
	FILE* pTestSet = NULL;
	DataSubjectInfo dataSubjectInfo [NB_FILES];

	fopen_s(&pDataSubjectInfo, FILE_DATA_SUBJECT_INFO, "r");

	if (pDataSubjectInfo == NULL) {
		puts("The file \"data_subjects_info.csv\" is not find! Please create it...");
	}
	else {
		fseek(pDataSubjectInfo, 0, SEEK_SET);
		char ignore[1024];
		fgets(ignore, sizeof(ignore), pDataSubjectInfo);
		initDataSubjectInfo(pDataSubjectInfo, dataSubjectInfo);

		fopen_s(&pTrainSet, FILE_TRAIN_SET, "w");
		fopen_s(&pTestSet, FILE_TEST_SET, "w");

		char paths[NB_PATH][PATHLENGHT] = { "dws_1\\", "dws_2\\", "dws_11\\", "jog_9\\", "jog_16\\", "sit_5\\", "sit_13\\", "std_6\\", "std_14\\", "ups_3\\", "ups_4\\", "ups_12\\", "wlk_7\\", "wlk_8\\", "wlk_15\\" };

		int indPath = 0;

		while (indPath < NB_PATH) {

			Data data;
			data.movement = readMouvement(paths, indPath);
			int indFile = 0;
			while (indFile < NB_FILES) {

				data.genre = readGenre(dataSubjectInfo, indFile);
				data.index = (indPath*24) + (indFile + 1);
				FILE* pMovement = NULL;
				char pathFile[PATHLENGHT] = "";
				createPath(pathFile, paths, indPath, indFile);

				fopen_s(&pMovement,pathFile, "r");
				if (pMovement == NULL) {
					printf("The file \"%s\" is not find! Please create it...\n",pathFile);
				}
				else {

					char ignore[1024];
					fgets(ignore, sizeof(ignore), pMovement);

					Movement mvt;

					int indVacc = 0;
					while (!feof(pMovement) && indVacc < NB_LINES) {
						fscanf_s(pMovement, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", &mvt.index
							, &mvt.attitudeRoll, &mvt.attitudePitch, &mvt.attitudeYaw
							, &mvt.gravityX, &mvt.gravityY, &mvt.gravityZ
							, &mvt.rotationRateX, &mvt.rotationRateY, &mvt.rotationRateZ
							, &mvt.userAccelerationX, &mvt.userAccelerationY, &mvt.userAccelerationZ);
						data.vacc[indVacc] = sqrt(square(mvt.userAccelerationX) + square(mvt.userAccelerationY) + square(mvt.userAccelerationZ));
						indVacc++;
					}

					if (rand() % 10 == 0) {
						fprintf(pTestSet, "%d,%d,%d,", data.movement, data.genre, data.index);
						indVacc = 0;
						while (indVacc < NB_LINES) {
							fprintf(pTestSet, "%lf,", data.vacc[indVacc]);
							indVacc++;
						}
						fprintf(pTestSet,"\n");
					}
					else {
						fprintf(pTrainSet, "%d,%d,%d,", data.movement, data.genre, data.index);
						indVacc = 0;
						while (indVacc < NB_LINES) {
							fprintf(pTrainSet, "%lf,", data.vacc[indVacc]);
							indVacc++;
						}
						fprintf(pTrainSet, "\n");
					}
					indFile++;
					fclose(pMovement);
				}	
			}
			indPath++;
		}
		fclose(pTestSet);
		fclose(pTrainSet);
		fclose(pDataSubjectInfo);
	}
	PAUSE;
}

void createPath(char pathFile[PATHLENGHT], char paths[][PATHLENGHT], int indPath,int indFile) {
	strcat_s(pathFile, PATHLENGHT, "Data\\");
	strcat_s(pathFile, PATHLENGHT, paths[indPath]);
	strcat_s(pathFile, PATHLENGHT, "sub_");
	char numFileString[3];
	_itoa_s(indFile + 1, numFileString, 3, 10);
	strcat_s(pathFile, PATHLENGHT, numFileString);
	strcat_s(pathFile, PATHLENGHT, ".csv");
}

int readMouvement(char paths [][PATHLENGHT],int indPath ) {

	char path[4];
	memcpy(path, paths[indPath], 3 * sizeof(char));
	path[3] = '\0';

	if (strcmp(path, "dws") == 0){
		return DOWNSTAIRS;

	}else {
		if (strcmp(path, "ups") == 0) {
			return UPSTAIRS;

		}
		else {
			if (strcmp(path, "jog") == 0) {
				return JOGGING;

			}
			else {
				if (strcmp(path, "sit") == 0) {
					return SITTING;

				}
				else {
					if (strcmp(path, "std") == 0) {
						return STANDUP;

					}
					else {
						return WALKING;

					}
				}
			}
		}
	}
}

void initDataSubjectInfo(FILE* pDataSubjectInfo,DataSubjectInfo datasSubjectInfo[NB_FILES]) {

	int nbSubject = 0;
	 
	while (!feof(pDataSubjectInfo) && nbSubject < NB_FILES) {

		fscanf_s(pDataSubjectInfo, "%d,%d,%d,%d,%d", &datasSubjectInfo[nbSubject].code, &datasSubjectInfo[nbSubject].height, &datasSubjectInfo[nbSubject].weight, &datasSubjectInfo[nbSubject].age, &datasSubjectInfo[nbSubject].genre);
		nbSubject++;
	}
}

int readGenre(DataSubjectInfo dataSubjectInfo[NB_FILES],int indFile) {

	int cpt = 0;
	while (cpt < NB_FILES && dataSubjectInfo[cpt].code != indFile+1) {
		cpt++;
	}

	return dataSubjectInfo[cpt].genre;
}