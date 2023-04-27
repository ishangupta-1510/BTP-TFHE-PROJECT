#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>
#define BLEN 32
struct ciphertext{
  	LweSample* ciphertext1;
  	LweSample* ciphertext2;
};

  struct ciphertext ciphertext;
int main() {
    //generate a keyset
    const int minimum_lambda = 110;
    TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);

    //generate a random key
    uint32_t seed[] = { 314, 1592, 657 };
    tfhe_random_generator_setSeed(seed,3);
    TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);
 
   //taking input from the user
    int32_t a,b;
    printf("\nEnter value of A :");
    scanf("%d", &a);
    printf("\nEnter value of B :");
    scanf("%d", &b);
    printf("working");
 //initialization 
    ciphertext.ciphertext1=new_gate_bootstrapping_ciphertext_array(BLEN,params);
    ciphertext.ciphertext2=new_gate_bootstrapping_ciphertext_array(BLEN,params);
    //encrypting the input

    for (int i = 0; i < BLEN; i++){
         bootsSymEncrypt(&ciphertext.ciphertext1[i], (a>>i)&1, key);
		 bootsSymEncrypt(&ciphertext.ciphertext2[i], (b>>i)&1, key);
    }
   
   
    
    
    //export the secret key to file for later use
    FILE* secret_key = fopen("secret.key","wb");
    export_tfheGateBootstrappingSecretKeySet_toFile(secret_key, key);
    fclose(secret_key);

    //export the cloud key to a file (for the cloud)
    FILE* cloud_key = fopen("./cloud.key","wb");
	
    export_tfheGateBootstrappingCloudKeySet_toFile(cloud_key, &key->cloud);
    fclose(cloud_key);

  
//export the input to cloud
   FILE* query_data=fopen("./query.data","wb");
    
     
     for(int n=0;n<BLEN;n++)
      {
      export_gate_bootstrapping_ciphertext_toFile(query_data, &ciphertext.ciphertext1[n],params);
      
      export_gate_bootstrapping_ciphertext_toFile(query_data, &ciphertext.ciphertext2[n],params);
      }
      fclose(query_data);
      printf(" A + B = ? \n");
    //clean up all pointer

	delete_gate_bootstrapping_ciphertext_array(BLEN,ciphertext.ciphertext1);
    delete_gate_bootstrapping_ciphertext_array(BLEN,ciphertext.ciphertext2);
    delete_gate_bootstrapping_secret_keyset(key);
    delete_gate_bootstrapping_parameters(params);
return 0;
}
