#ifndef _CALC_H__
#define _CALC_H__

typedef struct Data_tag Data;
typedef struct Question_tag Question;
typedef struct User_tag User;

struct Data_tag{
	int q_number;
	int fault_count;
	int correct_label;
};

struct Question_tag{
	int right;
	int left;
	int answer;
};
struct User_tag{
	Data data;
	Question question;
};


/*typedef struct{
    int number;
    int fault_count;
    int label;
} Count;
*/
Question make_question(void);
Data eval_answer(int recv,User user);
#endif

