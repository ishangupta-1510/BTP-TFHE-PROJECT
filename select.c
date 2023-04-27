#include <stdio.h>
#include <stdlib.h>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
int main()
{
  // get secrete key
  FILE *secret_key = fopen("secret.key", "rb");
  TFheGateBootstrappingSecretKeySet *key = new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
  fclose(secret_key);

  const TFheGateBootstrappingParameterSet *params = key->params;
  /*The value to check*/
  int32_t age;
  scanf("%d", &age);

  LweSample *ciphertext = new_gate_bootstrapping_ciphertext_array(16, params);
  /* encrypt the value */
  for (int i = 0; i < 16; i++)
  {
    bootsSymEncrypt(&ciphertext[i], (age >> i) & 1, key);
  }

  /* store the encrypted value */

  FILE *query_data = fopen("query.data", "wb");
  for (int i = 0; i < 16; i++)
  {
    export_gate_bootstrapping_ciphertext_toFile(query_data, &ciphertext[i], params);
  }
  fclose(query_data);
  delete_gate_bootstrapping_ciphertext_array(16, ciphertext);
  delete_gate_bootstrapping_secret_keyset(key);
  // delete_gate_bootstrapping_parameters(params);
}
