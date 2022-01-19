#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calc.h"

Question make_question(){
	Question quest;
	srand((unsigned int)time(NULL));
       	quest.left = 1 + rand() % 9;
	srand((unsigned int)time(NULL));
       	quest.right = 1 + rand() % 9;
	quest.answer = quest.left+quest.right;
	quest.statement_size = sprintf(quest.statement, "%d + %d = ?",quest.left,quest.right);
	return quest;
}
Data eval_answer(int recv,int fault_count,Question q,int que_number){
    Data d;
    if(recv == q.answer){
        d.q_number = que_number + 1;
        d.fault_count = fault_count;
        d.correct_label = 1;
    }else{
        //printf("正しい答えを入力してください\n");
        d.q_number = que_number;
        d.fault_count = fault_count + 1;
        d.correct_label = 0;
    }
    return d;
}
/*
int main(){
	Question quests[10];
	int i;
	//Question* quests = (Question*)malloc(sizeof(Question*) * 10);
	for(i=0;i<10;i++){
		if(i>1&&quests[i].answer==quests[i-1].answer){
		quests[i] = make_Question();
		}
	}
	for(i=0;i<10;i++){
		printf("answer = %d\n",quests[i].answer);
	}
	return 0;
}
*/
