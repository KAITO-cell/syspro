#ifndef _CALC_H__
#define _CALC_H__

typedef struct {
	int right;
	int left;
	int answer;
	char* sentence;
} Question;

typedef struct {
	int q_number;
	int fault_count;
	int correct_label;
}Data;

/*typedef struct{
    int number;
    int fault_count;
    int label;
} Count;
*/
Question make_question(void);
Data eval_answer(int recv,int fault_count,Question q,int que_number);
#endif

