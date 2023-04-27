#include <stdio.h>
#include<stdlib.h>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include"bitadder.h"

#include<time.h>
#define row_num 10 

#define data_size 16

struct ciphertext
  {
     
     LweSample* ci_pregnancies;
     LweSample* ci_glucose;
     LweSample* ci_blood_p;
     LweSample* ci_skin_thik;
     LweSample* ci_insulin;
     LweSample* ci_BMI;
     LweSample* ci_diabeties_pedig;
     LweSample* ci_age;
     LweSample* ci_outcome;
   };
 


 struct query
   {
     LweSample* query1;
     LweSample* query2;
    

   };
  
  struct query query;   
 
  struct ciphertext ciphertext[row_num];
  LweSample* tmps;
  LweSample* tmps1;

void subtract(LweSample* result, const LweSample* a, const LweSample* b, const int nb_bits, const TFheGateBootstrappingCloudKeySet* bk) {
    
    //printf("adder funcrion");
    //initialize the carry to 0
    bootsCONSTANT(&tmps[0], 0, bk);

    //run the elementary comparator gate n times
        
    for (int i=0; i<nb_bits; i++) 
        {
        compare_bit(&result[i], &a[i], &b[i], &tmps[0], &tmps[1], bk);
         
       }
 
    
  }
void subtract1(LweSample* result, const LweSample* a, const LweSample* b, const int nb_bits, const TFheGateBootstrappingCloudKeySet* bk) {
    
    //printf("adder funcrion");
    //initialize the carry to 0
    bootsCONSTANT(&tmps1[0], 0, bk);

    //run the elementary comparator gate n times
        
    for (int i=0; i<nb_bits; i++) 
        {
        compare_bit(&result[i], &a[i], &b[i], &tmps1[0], &tmps1[1], bk);
         
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

 void Adder(LweSample* top1, const LweSample* a6, const LweSample* b6, const int nb_bits, const TFheGateBootstrappingCloudKeySet* bk)
   {
     //printf("adder funcrion");
     LweSample* tmps6 = new_gate_bootstrapping_ciphertext_array(2, bk->params);
    //initialize the carry to 0
    bootsCONSTANT(&tmps6[0], 0, bk);

    //run the elementary comparator gate n times
        
    for (int i=0; i<nb_bits; i++) 
        {
        Addition(&top1[i], &a6[i], &b6[i], &tmps6[0], &tmps6[1], bk);
         
       }
     delete_gate_bootstrapping_ciphertext_array(2, tmps6);    
   }


int main()
 {
   //printf("\n Reading the key");
   time_t start_time = clock();
  
      
   
    FILE* cloud_key = fopen("cloud.key","rb");
    TFheGateBootstrappingCloudKeySet* bk = new_tfheGateBootstrappingCloudKeySet_fromFile(cloud_key);
    fclose(cloud_key);
    //if necessary, the params are inside the key
    const TFheGateBootstrappingParameterSet* params = bk->params;
    // variable declarartion

    
    tmps = new_gate_bootstrapping_ciphertext_array(2, params);
    tmps1 = new_gate_bootstrapping_ciphertext_array(2, params);
      
    query.query1 = new_gate_bootstrapping_ciphertext_array(data_size, params);
    query.query2 = new_gate_bootstrapping_ciphertext_array(data_size, params);
   
      
    
    for(int i=0;i<row_num;i++)
     {
     
      ciphertext[i].ci_pregnancies = new_gate_bootstrapping_ciphertext_array(data_size, params);
      ciphertext[i].ci_glucose = new_gate_bootstrapping_ciphertext_array(data_size, params);
      ciphertext[i].ci_blood_p = new_gate_bootstrapping_ciphertext_array(data_size, params);
      ciphertext[i].ci_skin_thik = new_gate_bootstrapping_ciphertext_array(data_size, params);
      ciphertext[i].ci_insulin = new_gate_bootstrapping_ciphertext_array(data_size, params);
      ciphertext[i].ci_BMI = new_gate_bootstrapping_ciphertext_array(data_size, params);
      ciphertext[i].ci_diabeties_pedig = new_gate_bootstrapping_ciphertext_array(data_size, params);
      ciphertext[i].ci_age = new_gate_bootstrapping_ciphertext_array(data_size, params);
      ciphertext[i].ci_outcome = new_gate_bootstrapping_ciphertext_array(data_size, params);
      
     }


    LweSample* result = new_gate_bootstrapping_ciphertext_array(data_size, params);
    LweSample* result1 = new_gate_bootstrapping_ciphertext_array(data_size, params);
    LweSample* result2 = new_gate_bootstrapping_ciphertext_array(data_size, params);  
    LweSample* result3 = new_gate_bootstrapping_ciphertext_array(data_size, params);
    LweSample* result4 = new_gate_bootstrapping_ciphertext_array(data_size, params);
    LweSample* computation = new_gate_bootstrapping_ciphertext_array(data_size, params);
    
    LweSample* ans= new_gate_bootstrapping_ciphertext_array(1,params);
    LweSample* ans1= new_gate_bootstrapping_ciphertext_array(1,params);

    LweSample* complement = new_gate_bootstrapping_ciphertext_array(1,params);//complement 0
    LweSample* complement1 = new_gate_bootstrapping_ciphertext_array(1,params);//complement 0
    LweSample* AC_out = new_gate_bootstrapping_ciphertext_array(1,params);

    printf("reading the query...\n");
    FILE* query_data = fopen("query.data","rb");
    for(int i=0;i<data_size;i++)
      {
        import_gate_bootstrapping_ciphertext_fromFile(query_data, &query.query1[i], params);
        import_gate_bootstrapping_ciphertext_fromFile(query_data, &query.query2[i], params);
      
      }
    fclose(query_data);
  
    printf("reading the cloud data...\n");
    FILE* cloud_data = fopen("cloud.data","rb");
    for(int j=0;j<row_num;j++)
      {
         for (int i=0; i<data_size; i++) 
           {
             
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_pregnancies[i], params);
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_glucose[i], params);
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_blood_p[i], params);
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_skin_thik[i], params);
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_insulin[i], params);
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_BMI[i], params);
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_diabeties_pedig[i], params);
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_age[i], params);
             import_gate_bootstrapping_ciphertext_fromFile(cloud_data, &ciphertext[j].ci_outcome[i], params);
                     
           }
       }
    fclose(cloud_data);
    
 
    printf("doing the homomorphic computation...\n");
    
    //do some operations on the ciphertexts: here, we will compute the
    //addition of two no.
       //FILE* secret_key = fopen("secret.key","rb");
      //TFheGateBootstrappingSecretKeySet* key = new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);

       
    
 
      for(int j=0;j<row_num;j++)
        { //equality check 2
          subtract(result2, query.query2, ciphertext[j].ci_age, data_size, bk);
          subtract1(result3,ciphertext[j].ci_age,query.query2,data_size,bk); 
          bootsOR(ans1,tmps,tmps1,bk);      
          bootsNOT(complement1,ans1,bk);
         
           //int com; 
          //int com1; 
        
           //com=bootsSymDecrypt(&complement[0],key)>0;
           //com1=bootsSymDecrypt(&complement1[0],key)>0; 
        
          //printf("\nage compare=%d \t ",com1);

          // bitwise AND
          // LweSample* E_out= new_gate_bootstrapping_ciphertext_array(1,params);
          //bootsAND(E_out,AC_out,complement1,bk);
         //int and; 
          //and=bootsSymDecrypt(&E_out[0],key)>0; 
           //printf("\tE_out for MUX=%d\n",and); 
  
          //Fhe addition
         //Adder(computation,ciphertext[j].ci_outcome,query.query3,data_size,bk);   

          //compare
          compare(result4,ciphertext[j].ci_BMI,query.query1,complement1,data_size,bk); 

          // copy  result4 value to ciphertext[j].ci_outcome
          int16_t compute=0;
          int out1; 
          int16_t answer=0;
          int out;  
          for(int i=0;i<data_size;i++) 
           {
             bootsCOPY(&ciphertext[j].ci_BMI[i],&result4[i],bk);
            //out=bootsSymDecrypt(&ciphertext[j].ci_outcome[i],key)>0;
            //answer|=(out<<i); 
            //out1=bootsSymDecrypt(&computation[i],key)>0;
            //compute|=(out1<<i);          
           }

         //printf("\n \n updated_outcome= %d\t Adder_compute=%d\n" , answer,compute);
         
        
        }
      
     cloud_data=fopen("cloud.data","wb");
    
     for(int j=0;j<row_num;j++){
     for(int n=0;n<16;n++)
      {
      
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_pregnancies[n],params); 
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_glucose[n],params);
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_blood_p[n],params);
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_skin_thik[n],params); 
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_insulin[n],params);
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_BMI[n],params);
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_diabeties_pedig[n],params); 
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_age[n],params);
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext[j].ci_outcome[n],params);
       
      }
  }
      fclose(cloud_data);
              time_t end_time = clock();

        printf("\n......computation of the 16 binary + 32 mux gates took: %ld microsecs\n",end_time-start_time); 
         
       // fclose(secret_key);
  for(int i=0;i<row_num;i++)
  {
    
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_pregnancies);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_glucose);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_blood_p);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_skin_thik);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_insulin);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_BMI);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_diabeties_pedig);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_age);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_outcome);
    
  }
    
    delete_gate_bootstrapping_ciphertext_array(1,ans1); 
    delete_gate_bootstrapping_ciphertext_array(1, complement1);

    delete_gate_bootstrapping_ciphertext_array(1,ans); 
    delete_gate_bootstrapping_ciphertext_array(1, complement);
    delete_gate_bootstrapping_ciphertext_array(data_size, query.query1);
    delete_gate_bootstrapping_ciphertext_array(data_size, query.query2);
  //  delete_gate_bootstrapping_ciphertext_array(data_size, query.query3); 
    delete_gate_bootstrapping_ciphertext_array(data_size, result);
    delete_gate_bootstrapping_ciphertext_array(data_size, result1); 
    delete_gate_bootstrapping_ciphertext_array(data_size, result2); 
    delete_gate_bootstrapping_ciphertext_array(data_size, result3); 
    delete_gate_bootstrapping_ciphertext_array(data_size, result4); 
    delete_gate_bootstrapping_ciphertext_array(data_size, computation);
    delete_gate_bootstrapping_ciphertext_array(1, AC_out);
     delete_gate_bootstrapping_ciphertext_array(2, tmps1);     
    delete_gate_bootstrapping_ciphertext_array(2, tmps);   
    delete_gate_bootstrapping_cloud_keyset(bk);

  
 printf("\n......complete");
 
 }





 


