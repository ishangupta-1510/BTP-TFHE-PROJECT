#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>
#define row_num 4
#define data_size 16

struct ciphertext
{

  LweSample *ci_pregnancies;
  LweSample *ci_glucose;
  LweSample *ci_blood_p;
  LweSample *ci_skin_thik;
  LweSample *ci_insulin;
  LweSample *ci_BMI;
  LweSample *ci_diabeties_pedig;
  LweSample *ci_age;
  LweSample *ci_outcome;
};
struct ciphertext ciphertext[row_num];

int main()
{

  // reads the secret key from file
  FILE *secret_key = fopen("secreto.key", "rb");
  TFheGateBootstrappingSecretKeySet *key = new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
  fclose(secret_key);

  // if necessary, the params are inside the key
  const TFheGateBootstrappingParameterSet *params = key->params;

  // read the ciphertexts of the result
  for (int i = 0; i < row_num; i++)
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

  // import answer /home/user/database/Select/Cloud storage
  FILE *answer_data = fopen("answero.data", "rb");

  for (int j = 0; j < row_num; j++)
  {
    for (int i = 0; i < data_size; i++)
    {

      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_pregnancies[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_glucose[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_blood_p[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_skin_thik[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_insulin[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_BMI[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_diabeties_pedig[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_age[i], params);
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &ciphertext[j].ci_outcome[i], params);
    }
  }

  fclose(answer_data);

  // decrypt and rebuild the answer

  for (int j = 0; j < row_num; j++)
  {

    int32_t answer = 0;
    int32_t answer1 = 0;
    int32_t answer2 = 0;
    int32_t answer3 = 0;
    int32_t answer4 = 0;
    int32_t answer5 = 0;
    int32_t answer6 = 0;
    int32_t answer7 = 0;
    int32_t answer8 = 0;
    for (int i = 0; i < data_size; i++)
    {
      int abc = bootsSymDecrypt(&ciphertext[j].ci_pregnancies[i], key) > 0;
      answer |= (abc << i);
      int abc1 = bootsSymDecrypt(&ciphertext[j].ci_glucose[i], key) > 0;
      answer1 |= (abc1 << i);
      int abc2 = bootsSymDecrypt(&ciphertext[j].ci_blood_p[i], key) > 0;
      answer2 |= (abc2 << i);
      int abc3 = bootsSymDecrypt(&ciphertext[j].ci_skin_thik[i], key) > 0;
      answer3 |= (abc3 << i);
      int abc4 = bootsSymDecrypt(&ciphertext[j].ci_insulin[i], key) > 0;
      answer4 |= (abc4 << i);
      int abc5 = bootsSymDecrypt(&ciphertext[j].ci_BMI[i], key) > 0;
      answer5 |= (abc5 << i);
      int abc6 = bootsSymDecrypt(&ciphertext[j].ci_diabeties_pedig[i], key) > 0;
      answer6 |= (abc6 << i);
      int abc7 = bootsSymDecrypt(&ciphertext[j].ci_age[i], key) > 0;
      answer7 |= (abc7 << i);
      int abc8 = bootsSymDecrypt(&ciphertext[j].ci_outcome[i], key) > 0;
      answer8 |= (abc8 << i);
    }
    printf("\npregnancy=%d\tglucose=%d\t blood_p=%d\t skin thik=%d\t insulin=%d\t BMI=%d\t diabeties_pedig=%d\tage=%d\t outcome=%d", answer, answer1, answer2, answer3, answer4, answer5, answer6, answer7, answer8);
  }
  printf("\n");

  // printf(" completed!! \n");
  // clean up all pointers
  for (int i = 0; i < row_num; i++)
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
  delete_gate_bootstrapping_secret_keyset(key);

  return 0;
}
