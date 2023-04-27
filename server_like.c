#include <stdio.h>
#include<stdlib.h>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include<time.h>
#define row_num 10
#define data_size 16
struct query{
LweSample* first;
LweSample* second;
LweSample* third;
//LweSample* age;
};
struct name{
LweSample* first;
LweSample* second;
LweSample* third;
LweSample* fourth;
LweSample* fivth;
LweSample* sixth;
LweSample* sevth;
LweSample* eith;
};


struct ciphertext
 {

  struct name name[row_num]; 
  LweSample* ci_cust_key;
  LweSample* ci_age;
  LweSample* ci_balance;
  

 };
struct answer
 {

  //struct name name[4]; 
  LweSample* ans_cust_key;
  LweSample* ans_age;
  LweSample* ans_balance;
  

 };
struct answer answer[row_num];
struct ciphertext ciphertext[row_num];
struct query query;
void compare_bit(LweSample* result, const LweSample* a, const LweSample* b, LweSample* lsb_carry, LweSample* tmp, const TFheGateBootstrappingCloudKeySet* bk) {
      LweSample* temp1=new_gate_bootstrapping_ciphertext_array(1, bk->params);
      LweSample* temp2=new_gate_bootstrapping_ciphertext_array(1, bk->params);
      LweSample* temp3=new_gate_bootstrapping_ciphertext_array(1,bk->params);
      LweSample* temp4=new_gate_bootstrapping_ciphertext_array(1,bk->params);
      LweSample* temp5=new_gate_bootstrapping_ciphertext_array(1,bk->params);

      bootsXOR(temp1, a, b, bk);  //a xorb
      bootsXOR(result,temp1,lsb_carry,bk);  //a xor b xor ci
      bootsNOT(temp4,a,bk);  // complement of a
      bootsAND(temp3,temp4,b,bk); // complement a and b
      bootsNOT(temp5,temp1,bk);  // complement of a XOR b
      bootsAND(temp2,temp5,lsb_carry,bk);// complement of a XOR b AND lasb_carry
  
      bootsOR(tmp,temp2,temp3,bk);       // a&b + ci*(a xor b)
      bootsCOPY(lsb_carry,tmp,bk);
    }
void subtract(LweSample* result, LweSample* tmps, const LweSample* a, const LweSample* b, const int nb_bits, const TFheGateBootstrappingCloudKeySet* bk) {
    
    //run the elementary comparator gate n times//
      
  	     for (int i=0; i<nb_bits; i++) {
        compare_bit(&result[i], &a[i], &b[i], &tmps[0], &tmps[1], bk);
        }
    }
 void compare(LweSample* output,LweSample* first_input,LweSample* second_input,LweSample* select_line,const int nb_bit, const TFheGateBootstrappingCloudKeySet* bk)
  {
      int m=0;
      for(int i=0;i<nb_bit;i++)
        {
         bootsMUX(&output[i],&select_line[m],&second_input[i],&first_input[i],bk);
        }
  }
int main()
 {
time_t start_time = clock();
FILE* cloud_key = fopen("cloud.key","rb");
    TFheGateBootstrappingCloudKeySet* bk = new_tfheGateBootstrappingCloudKeySet_fromFile(cloud_key);
    fclose(cloud_key);
    //if necessary, the params are inside the key
    const TFheGateBootstrappingParameterSet* params = bk->params;
      query.first = new_gate_bootstrapping_ciphertext_array(16, params);
      query.second = new_gate_bootstrapping_ciphertext_array(16, params);
     query.third = new_gate_bootstrapping_ciphertext_array(16, params);
   // query.age = new_gate_bootstrapping_ciphertext_array(16, params);
for(int i=0;i<row_num;i++)
{
 ciphertext[i].name[i].first=new_gate_bootstrapping_ciphertext_array(data_size,params);
 ciphertext[i].name[i].second=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].name[i].third=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].name[i].fourth=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].name[i].fivth=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].name[i].sixth=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].name[i].sevth=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].name[i].eith=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].ci_cust_key=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].ci_age=new_gate_bootstrapping_ciphertext_array(data_size,params);
ciphertext[i].ci_balance=new_gate_bootstrapping_ciphertext_array(data_size,params);
          

}
 for(int i=0;i<row_num;i++){
   answer[i].ans_cust_key=new_gate_bootstrapping_ciphertext_array(data_size,params);
   answer[i].ans_age=new_gate_bootstrapping_ciphertext_array(data_size,params);
   answer[i].ans_balance=new_gate_bootstrapping_ciphertext_array(data_size,params);
 }
     // ciphertext[i].ci_skin_thik = new_gate_bootstrapping_ciphertext_array(data_size, params);

printf("reading the query...\n");
    FILE* query_data = fopen("Queryl.data","rb");
 
    for(int i=0;i<16;i++)
      {
        import_gate_bootstrapping_ciphertext_fromFile(query_data, &query.first[i], params); 
        import_gate_bootstrapping_ciphertext_fromFile(query_data, &query.second[i], params); 
        import_gate_bootstrapping_ciphertext_fromFile(query_data, &query.third[i], params); 
        //import_gate_bootstrapping_ciphertext_fromFile(query_data, &query.age[i], params);
      }

printf("reading from cloud...\n");
    FILE* cloud_data = fopen("cloud_like.data","rb");

    for(int j=0;j<row_num;j++){
     for(int n=0;n<16;n++)
      {

      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].name[j].first[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].name[j].second[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].name[j].third[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].name[j].fourth[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].name[j].fivth[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].name[j].sixth[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].name[j].sevth[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].name[j].eith[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_cust_key[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_age[n],params);
      import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_balance[n],params);

      }
  }
     fclose(cloud_data);
FILE* secret_key = fopen("secret.key","rb");
      TFheGateBootstrappingSecretKeySet* key = new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
/*int16_t int_answer4=0;
for(int i=0;i<16;i++){
int ai5=bootsSymDecrypt(&ciphertext[0].name[0].second[i],key)>0;
          int_answer4|=(ai5<<i);}
printf("%d",int_answer4);*/
    LweSample* signbit = new_gate_bootstrapping_ciphertext_array(2, params);
    LweSample* signbit1 = new_gate_bootstrapping_ciphertext_array(2, params);
    LweSample* signbit2 = new_gate_bootstrapping_ciphertext_array(2, params);
    LweSample* signbit3 = new_gate_bootstrapping_ciphertext_array(2, params);
    LweSample* signbit4 = new_gate_bootstrapping_ciphertext_array(2, params);
    LweSample* signbit5 = new_gate_bootstrapping_ciphertext_array(2, params); 
    LweSample* signbit6 = new_gate_bootstrapping_ciphertext_array(2, params);
    LweSample* signbit7 = new_gate_bootstrapping_ciphertext_array(2, params); 
    LweSample* result = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* result1 = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* result2 = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* result3 = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* result4 = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* result5 = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* result6 = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* result7 = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* enc_th = new_gate_bootstrapping_ciphertext_array(16, params);
    
    LweSample* ans= new_gate_bootstrapping_ciphertext_array(1,params);
    LweSample* ans1= new_gate_bootstrapping_ciphertext_array(1,params);
    LweSample* ans2= new_gate_bootstrapping_ciphertext_array(1,params);
    LweSample* ans3= new_gate_bootstrapping_ciphertext_array(1,params);
    LweSample* complement = new_gate_bootstrapping_ciphertext_array(1,params);
    LweSample* complement1 = new_gate_bootstrapping_ciphertext_array(1,params);
    LweSample* complement2 = new_gate_bootstrapping_ciphertext_array(1,params);  
    LweSample* complement3 = new_gate_bootstrapping_ciphertext_array(1,params);  
    LweSample* match = new_gate_bootstrapping_ciphertext_array(1,params);  
    LweSample* match_result = new_gate_bootstrapping_ciphertext_array(1,params); 
    LweSample* final_match = new_gate_bootstrapping_ciphertext_array(1,params); 
    //printf("helloo");
   for(int j=0;j<3;j++){
    
   bootsCONSTANT(&signbit[0], 0, bk);
   bootsCONSTANT(&signbit1[0], 0, bk);
   bootsCONSTANT(&signbit2[0], 0, bk);
   bootsCONSTANT(&signbit3[0], 0, bk);
   bootsCONSTANT(&signbit4[0], 0, bk);
   bootsCONSTANT(&signbit5[0], 0, bk); 
   bootsCONSTANT(&signbit6[0], 0, bk);
   bootsCONSTANT(&signbit7[0], 0, bk); 
   
   subtract(result,signbit, query.first, ciphertext[j].name[j].first,data_size,bk);   //
   subtract(result1,signbit1,ciphertext[j].name[j].first,query.first,data_size,bk); 
        bootsOR(ans,signbit,signbit1,bk);
        bootsNOT(complement,ans,bk); 

    subtract(result2,signbit2, query.second, ciphertext[j].name[j].second,data_size,bk);   //
    subtract(result3,signbit3,ciphertext[j].name[j].second,query.second,data_size,bk); 
        bootsOR(ans1,signbit2,signbit3,bk);
        bootsNOT(complement1,ans1,bk); 
   subtract(result4,signbit4, query.third, ciphertext[j].name[j].third,data_size,bk);   //
   subtract(result5,signbit5,ciphertext[j].name[j].third,query.third,data_size,bk); 
        bootsOR(ans2,signbit4,signbit5,bk);
        bootsNOT(complement2,ans2,bk); 

        bootsAND(match,complement,complement1,bk);
        bootsAND(match_result,match,complement2,bk);
        
       // subtract(result6,signbit6, query.age, ciphertext[j].ci_age,data_size,bk); 
        //subtract(result7,signbit7, ciphertext[j].ci_age, query.age, data_size,bk);
          
       // bootsOR(ans3,signbit6,signbit7,bk);
       // bootsNOT(complement3,ans3,bk); 
       
       // bootsAND(final_match,match_result,complement3,bk); 
        
for(int i=0;i<16;i++){bootsCOPY(&enc_th[i],&match_result[0],bk);}
    compare(answer[j].ans_cust_key,enc_th,ciphertext[j].ci_cust_key,match_result,data_size,bk);
    compare(answer[j].ans_age,enc_th,ciphertext[j].ci_age,match_result,data_size,bk);
    compare(answer[j].ans_balance,enc_th,ciphertext[j].ci_balance,match_result,data_size,bk);
  /* int16_t int_answer5=0;
for(int i=0;i<16;i++){
int ai6=bootsSymDecrypt(&answer[j].ans_cust_key[i],key)>0;
          int_answer5|=(ai6<<i);}
printf("\t%d",int_answer5);*/
   }
  
   
    fclose(query_data);
FILE* answer_data=fopen("answer.data","wb");
     for(int j=0;j<row_num;j++){
     for(int n=0;n<data_size;n++)
      {

     export_gate_bootstrapping_ciphertext_toFile(answer_data, &answer[j].ans_cust_key[n],params);
      export_gate_bootstrapping_ciphertext_toFile(answer_data, &answer[j].ans_age[n],params);
      export_gate_bootstrapping_ciphertext_toFile(answer_data, &answer[j].ans_balance[n],params);
      
           

      }
  }
	   
      fclose(answer_data);
    time_t end_time = clock();

        printf("\nResult is stored in cloud answer file! Time to execute %ld second\n",(end_time-start_time)/1000000);
printf("\ncomplete");
}
























