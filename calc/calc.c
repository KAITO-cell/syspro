#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
    int easy_ope_1[6];
    int easy_ope_2[6];
    int easy_ans[6];
    double diff_ope_1[3];
    double diff_ope_2[3];
    double diff_ans[3];
    int fault_count;
}user_data;

user_data u;

Expression* make_expression(){
	Expression expression;
	int i=0;
	for(i=0;i<10;i++){
        	expression->left = 1 + rand() % 9;
        	expression->right = 1 + rand() % 9;
		expression->answer = left+right;
		expression++;
	}
	return expression;
}
	



}

int main(void){
    srand((unsigned int)time(NULL));
    //簡単な問題(1問目:足し算,2問目:引き算,3問目:掛け算)
    for(int i = 0; i < 3; i++){
        u.easy_ope_1[i] = 1 + rand() % 9;
        u.easy_ope_2[i] = 1 + rand() % 9;
        if(i == 0){
            u.easy_ans[i] = u->easy_ope_1[i] + u.easy_ope_2[i];
        }
        if(i == 1){
            u.easy_ans[i] = u.easy_ope_1[i] - u.easy_ope_2[i];
        }
        if(i == 2){
            u.easy_ans[i] = u.easy_ope_1[i] * u.easy_ope_2[i];
        }
    }
    //標準問題(4問目:足し算,5問目:引き算,6問目:掛け算)
    for(int i = 3; i < 6; i++){
        u.easy_ope_1[i] = 10 + rand() % 90;
        u.easy_ope_2[i] = 10 + rand() % 90;
        if(i == 3){
            u.easy_ans[i] = u.easy_ope_1[i] + u.easy_ope_2[i];
        }
        if(i == 4){
            u.easy_ans[i] = u.easy_ope_1[i] - u.easy_ope_2[i];
        }
        if(i == 5){
            u.easy_ans[i] = u.easy_ope_1[i] * u.easy_ope_2[i];
        }
    }
    
    int i = 0;
    int easy_in;
    u.fault_count = 0;
    
    while(1){
        if(i == 0 || i == 3){
            printf("%d + %d = ",u.easy_ope_1[i],u.easy_ope_2[i]);
        }else if(i == 1 || i == 4){
            printf("%d - %d = ",u.easy_ope_1[i],u.easy_ope_2[i]);
        }else{
            printf("%d * %d = ",u.easy_ope_1[i],u.easy_ope_2[i]);
        }
        scanf("%d",&easy_in);
        if(u.easy_ans[i] == easy_in){
            i++;
        }else{
            u.fault_count++;
        }
        if(i == 6){
            break;
        }
    }
    //難しい問題(7問目:足し算,8問目:引き算,9問目:掛け算)
    for(int i = 0; i < 3; i++){
        u.diff_ope_1[i] = (10 + rand() % 90) / 10.0;
        u.diff_ope_2[i] = (10 + rand() % 90) / 10.0;
        if(i == 0){
            u.diff_ans[i] = u.diff_ope_1[i] + u.diff_ope_2[i];
        }
        if(i == 1){
            u.diff_ans[i] = u.diff_ope_1[i] - u.diff_ope_2[i];
        }
        if(i == 2){
            u.diff_ans[i] = u.diff_ope_1[i] * u.diff_ope_2[i];
        }
    }
    int j = 0;
    double diff_in;

    while(1){
        if(j == 0){
            printf("%g + %g = %g j=%d ",u.diff_ope_1[j],u.diff_ope_2[j],u.diff_ans[j],j);
        }else if(j == 1){
            printf("%g - %g = %g j=%d ",u.diff_ope_1[j],u.diff_ope_2[j],u.diff_ans[j],j);
        }else{
            printf("%g * %g = %g j=%d ",u.diff_ope_1[j],u.diff_ope_2[j],u.diff_ans[j],j);
        }
        scanf("%lg",&diff_in);
        if(u.diff_ans[j] == diff_in){
            j++;
        }else{
            u.fault_count++;
        }
        if(j == 3){
            break;
        }
    }


    if(u.fault_count == 0){
        printf("You are perfect! Conguratulation!\n");
    }else if(u.fault_count == 1){
        printf("You made once mistake\n");
    }else if(u.fault_count == 2){
        printf("You made twice mistakes\n");
    }else{
        printf("You made %d times mistakes\n",u.fault_count);
    }
    return 0;
}
