#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calc.h"

Question make_Question(){
    Question quest;
    srand((unsigned int)time(NULL));
    quest.left = 1 + rand() % 9;
    quest.right = 1 + rand() % 9;
    quest.answer = quest.left + quest.right;
    return quest;
}

// void calc(int recv,User_data user_data){
//     Question quest[10];
//     for(int i=0;i<10;i++){
//         quest[i] = make_Question();
//     }
//     user_data.question = quest;
//     int i = 0;
//     while(1){
//         if(recv == user_data.question->answer){
//             i++;
//             break;
//         }else{
//             user_data.fault_count++;
//         }
//     }
// }

Count calc(int recv,int fault_count,Question q,int que_number){
    Count count;
    if(recv == q.answer){
        count.number = que_number + 1;
        count.fault_count = fault_count;
        count.label = 0;
    }else{
        printf("正しい答えを入力してください\n");
        count.number = que_number;
        count.fault_count = fault_count + 1;
        count.label = 1;
    }
    return count;
}


// int main(){
//     int recv=0;
//     User_data u;
//     for(int i=0;i<10;i++){
//         u.question[i] = make_Question();
//     }
//     u.fault_count = 0;
//     int i = 0;
//     int correct = 0;
//     while(1){
//         printf("%d + %d = %d",u.question[i].left,u.question[i].right,u.question[i].answer);
//         scanf("%d",&recv);
//         calc(recv,u,i,correct);
//         i++;
//         if(correct==10){
//             break;
//         }
//     }
//     printf("間違えた回数:%d\n",u.fault_count);
//     return 0;
// }


// int main(){
//     int recv=0;
//     User_data u;
//     for(int i=0;i<10;i++){
//         u.question[i] = make_Question();
//     }
//     u.fault_count = 0;
//     int i = 0;
//     int correct = 0;
//     while(1){
//         printf("%d + %d = %d",u.question[i].left,u.question[i].right,u.question[i].answer);
//         scanf("%d",&recv);
//         calc(recv,u,i,correct);
//         if(i==10){
//             break;
//         }
//     }
//     printf("間違えた回数:%d\n",u.fault_count);
//     return 0;
// }

int main(){
    int recv,fault_count=0;
    Question q[10];
    Count c;
    c.label = 0;
    int i=0;
    while (1){
        if(c.label == 0){
            q[i]=make_Question();
        }
        printf("%d + %d = ",q[i].left,q[i].right);
        scanf("%d",&recv);
        c = calc(recv,fault_count,q[i],i);
        i = c.number;
        fault_count = c.fault_count;
        if(i==10){
            break;
        }
    }
    printf("間違えた回数:%d\n",fault_count);
    return 0;
}
    
