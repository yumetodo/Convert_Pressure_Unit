#include<stdio.h>
#include<stdlib.h>
#include<limits.h>//in gcc
#include<errno.h>//in gcc
#ifndef __cplusplus
#define nullptr NULL
#endif

int get_integer_num(const int max, const int min){
	//�@�\�F�W�����͂𐔎��ɕϊ�����B
	//�����F�߂�l�̍ő�l,�߂�l�̍ŏ��l
	//�߂�l�F���͂��������A�G���[����-1,EOF�̂Ƃ���EOF
	char s[100];
	char *endptr;
	if (nullptr == fgets(s, 100, stdin)){
		if (feof(stdin)){//�G���[�̌�����EOF���؂蕪��
			return EOF;
		}
		return INT_MIN;
	}
	if ('\n' == s[0]) return INT_MIN;
	errno = 0;
	const long t = strtol(s, &endptr, 10);
	if (0 != errno || '\n' != *endptr || t < min || max < t)
		return INT_MIN;
	return (int)t;
}

int getnum_customized_type_int(const int max, const int min){
	if (max < min)   return -1;
	int flag0;
	bool temp_judge;
	do{
		flag0 = get_integer_num(max, min);
		temp_judge = (INT_MIN == flag0);
		if (temp_judge){
			system("cls");
			puts("�ē��͂��Ă��������B");
		}
	} while (temp_judge);
	return flag0;
}


double getnum(const double max, const double min, double* isError){
	//�@�\�F�W�����͂𐔎��ɕϊ�����B
	//�����F�߂�l�̍ő�l,�߂�l�̍ŏ��l
	//�߂�l�F���͂��������A�G���[����-1,EOF�̂Ƃ���EOF
	char s[100];
	char *endptr;
	if (nullptr == fgets(s, 100, stdin)){
		if (nullptr != isError) *isError = -1;
		return 0;
	}
	if ('\n' == s[0]){
		if (nullptr != isError) *isError = -1;
		return 0;
	}
	errno = 0;
	const double t = strtod(s, &endptr);
	if (0 != errno || '\n' != *endptr || t < min || max < t)
		if (nullptr != isError) *isError = -1;
	return t;
}

double getnum_customized_type_double(const double max, const double min){
	if (max < min)   return -1;
	double flag0 = 0;
	double return_num;
	bool temp_judge;
	do{
		return_num = getnum(max, min, &flag0);
		temp_judge = (-1 == flag0);
		if (temp_judge){
			//system("cls");
			puts("�ē��͂��Ă��������B");
		}
	} while (temp_judge);
	return return_num;
}

void common_message(void){
	printf("�C���ϊ��c�[��\n\n");
}

void hPa_to_mmHg(void){
	printf("�C��(hPa)����͂��Ă��������B\n");
	double Pa = getnum_customized_type_double(5000, 0);
	system("cls");
	double calc_mmHg = Pa * 760 / 1013;
	common_message();
	printf("%fhPa��%fmmHg�ł��B\n", Pa, calc_mmHg);
}

void mmHg_to_hPa(void){
	printf("�C��(mmHg)����͂��Ă��������B\n");
	double mmHg = getnum_customized_type_double(5000, 0);
	system("cls");
	double calc_Pa = mmHg * 1013 / 760;
	common_message();
	printf("%fmmHg��%fPa�ł��B\n", mmHg, calc_Pa);
}

void clear_screen(void){
	system("pause");
	system("cls");
}

void roop(void){
	int flag = 0;
	int flag2;
	int end = 0;
	do{
		common_message();
		switch (flag){
		case 0:{
			flag2 = 0;
			printf("Pa����mmHg�ɕϊ�����ꍇ�͂P�AmmHg����Pa�ɕϊ�����ꍇ�͂Q����͂���Enter�L�[�������Ă��������B\n"
				"���������I������ꍇ�͂R����͂��Ă��������B\n");
			flag = getnum_customized_type_int(3, 1);
			system("cls");
			break;
		}
		case 1:{
			hPa_to_mmHg();
			flag = 4;
			clear_screen();
			break;
		}
		case 2:{
			mmHg_to_hPa();
			flag = 4;
			clear_screen();
			break;
		}
		case 3:{
			end = 1;
			break;
		}
		case 4:{
			printf("�v�Z�𑱂��܂����H\n�͂��c�P�@�������c�Q\n");
			flag2 = getnum_customized_type_int(2, 1);
			if (flag2 == 1) flag = 0;
			if (flag2 == 2) flag = 3;
			system("cls");
			break;
		}
		default:
			break;
		}
	} while (end == 0);
}

int main(void){
	roop();
	return 0;
}