#include "Constance.h"

void main(void) {

	FILE* pTrainSet = NULL;
	FILE* pFiModel = NULL;
	FILE* pFiModelMen = NULL;
	FILE* pFiModelWomen = NULL;

	fopen_s(&pFiModel, FILE_MODEL, "w");
	fopen_s(&pFiModelMen, FILE_MODEL_MEN, "w");
	fopen_s(&pFiModelWomen, FILE_MODEL_WOMEN, "w");

	fopen_s(&pTrainSet, FILE_TRAIN_SET, "r");
	if (pTrainSet == NULL || pFiModel==NULL|| pFiModelMen == NULL||pFiModelWomen == NULL){
		puts("The file \"train_set.csv\" is not find! Please create it...");

	}else {
		Data dataRead;
		int nbMen = 0;
		int nbWomen = 0;
		FiModel fiModelMen;
		FiModel fiModelWomen;
		FiModel fiModel;
		for (int i = 0; i < NB_LINES; i++){

			fiModelMen.vacc[i] = 0;
			fiModelWomen.vacc[i] = 0;
		}
		fscanf_s(pTrainSet, "%d,%d,%d,", &dataRead.movement, &dataRead.genre, &dataRead.index);
		while (!feof(pTrainSet)) {
			int movement = dataRead.movement;
			fiModel.movement = movement;
			fiModelMen.movement = movement;
			fiModelWomen.movement = movement;
			while (!feof(pTrainSet) && movement == dataRead.movement ) {
				int indVacc = 0;
				while (indVacc < NB_LINES) {
					fscanf_s(pTrainSet, "%lf,", &dataRead.vacc[indVacc]);
					indVacc++;
				}

				if (dataRead.genre == 1) {
					for (int i = 0; i < NB_LINES; i++) {
						fiModelMen.vacc[i] += dataRead.vacc[i];
					}
					nbMen++;
				}
				else {
					for (int i = 0; i < NB_LINES; i++) {
						fiModelWomen.vacc[i] += dataRead.vacc[i];
					}
					nbWomen++;
				}
				fscanf_s(pTrainSet, "%d,%d,%d,", &dataRead.movement, &dataRead.genre, &dataRead.index);
			}
			for (int i = 0; i < NB_LINES; i++) {
				int nbPeople = nbMen + nbWomen;
				fiModel.vacc[i] = (fiModelMen.vacc[i] + fiModelWomen.vacc[i]) / nbPeople;
				fiModelMen.vacc[i] /= nbMen;
				fiModelWomen.vacc[i] /= nbWomen;
			}
			readInFiModel(pFiModel, fiModel);
			readInFiModel(pFiModelMen, fiModelMen);
			readInFiModel(pFiModelWomen, fiModelWomen);
		}
		PAUSE;
		fclose(pFiModel);
		fclose(pFiModelMen);
		fclose(pFiModelWomen);
		fclose(pTrainSet);
	}
}

void readInFiModel(FILE* pFile,FiModel fiModel) {
	fprintf(pFile, "%d,", fiModel.movement);
	int indVacc = 0;
	while (indVacc < NB_LINES) {
		fprintf(pFile, "%lf,", fiModel.vacc[indVacc]);
		indVacc++;
	}
	fprintf(pFile, "\n");
}