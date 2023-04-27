#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>
#define row_num 3
#define data_size 16

struct plaintext
{

  int cust_id;
  int age;
  int balance;

};
struct ciphertext
{

  LweSample *ci_cust_key;
  LweSample *ci_age;
  LweSample *ci_balance;
 
};
struct ciphertext ciphertext[row_num];
struct plaintext plaintext[row_num];
int main()
{

  // reads the secret key from file
  FILE *secret_key = fopen("secret.key", "rb");
  TFheGateBootstrappingSecretKeySet *key = new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
  fclose(secret_key);

  // if necessary, the params are inside the key
  const TFheGateBootstrappingParameterSet *params = key->params;

  // read the ciphertexts of the result
  for (int i = 0; i < row_num; i++)
  {

    ciphertext[i].ci_cust_key = new_gate_bootstrapping_ciphertext_array(data_size, params);
    ciphertext[i].ci_age = new_gate_bootstrapping_ciphertext_array(data_size, params);
    ciphertext[i].ci_balance = new_gate_bootstrapping_ciphertext_array(data_size, params);
   
  }

  // import answer /home/user/database/Select/Cloud storage
  FILE *answer_data = fopen("answer.data", "rb");

  for (int j = 0; j < row_num; j++)
  {
    for (int i = 0; i < data_size; i++)
    {

      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_cust_key[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_age[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_balance[i], params);
    
    }
  }

  fclose(answer_data);

  // decrypt and rebuild the answer

  for (int j = 0; j < row_num; j++)
  {

    int32_t answer = 0;
    int32_t answer1 = 0;
    int32_t answer2 = 0;
    
    for (int i = 0; i < data_size; i++)
    {
      int abc = bootsSymDecrypt(&ciphertext[j].ci_cust_key[i], key) > 0;
      answer |= (abc << i);
      int abc1 = bootsSymDecrypt(&ciphertext[j].ci_age[i], key) > 0;
      answer1 |= (abc1 << i);
      int abc2 = bootsSymDecrypt(&ciphertext[j].ci_balance[i], key) > 0;
      answer2 |= (abc2 << i);
   
    }
    plaintext[j].cust_id = answer;
    plaintext[j].age = answer1;
    plaintext[j].balance = answer2;
   

    // printf("\npregnancy=%d\tglucose=%d\t blood_p=%d\t skin thik=%d\t insulin=%d\t BMI=%d\t diabeties_pedig=%d\tage=%d\t outcome=%d", answer,answer1,answer2,answer3,answer4,answer5,answer6,answer7,answer8);
  }
  // printf("\n");
  // printf("a\tb\tc\td\te\tf\tg\th\ti\t");
  printf(" ");
  for (int i = 0; i < row_num; i++)
  {
    printf("%d,%d,%d", plaintext[i].cust_id, plaintext[i].age, plaintext[i].balance);
    printf(" ");
  } // printf(" completed!! \n");
  // clean up all pointers
  for (int i = 0; i < row_num; i++)
  {

    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_cust_key);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_age);
    delete_gate_bootstrapping_ciphertext_array(data_size, ciphertext[i].ci_balance);
  
  }
  delete_gate_bootstrapping_secret_keyset(key);

  return 0;
}