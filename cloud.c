#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>
#include <time.h>
#define BLEN 32

void Addition(LweSample *top1, const LweSample *a6, const LweSample *b6, LweSample *lsb_carry1, LweSample *tmp6, const TFheGateBootstrappingCloudKeySet *bk)
{
    LweSample *temp1 = new_gate_bootstrapping_ciphertext_array(1, bk->params);
    LweSample *temp2 = new_gate_bootstrapping_ciphertext_array(1, bk->params);
    LweSample *temp3 = new_gate_bootstrapping_ciphertext_array(1, bk->params);

    bootsXOR(temp1, a6, b6, bk);            // a xor b
    bootsXOR(top1, temp1, lsb_carry1, bk);  // a xor b xor ci
    bootsAND(temp2, temp1, lsb_carry1, bk); // ci and (a xor b)
    bootsAND(temp3, a6, b6, bk);            // a and b
    bootsOR(tmp6, temp2, temp3, bk);        // a&b + ci*(a xor b)
    bootsCOPY(lsb_carry1, tmp6, bk);
}
void Adder(LweSample *top1, const LweSample *a6, const LweSample *b6, const int nb_bits, const TFheGateBootstrappingCloudKeySet *bk)
{
    LweSample *tmps = new_gate_bootstrapping_ciphertext_array(2, bk->params);
    bootsCONSTANT(&tmps[0], 0, bk); // initialize carry to 0

    // run the elementary comparator gate n times//

    for (int i = 0; i < nb_bits; i++)
    {
        Addition(&top1[i], &a6[i], &b6[i], &tmps[0], &tmps[1], bk);
    }
    delete_gate_bootstrapping_ciphertext_array(2, tmps);
}

struct ciphertext
{
    LweSample *ciphertext1;
    LweSample *ciphertext2;
};
struct ciphertext ciphertext;

int main()
{
    time_t start_time = clock();
    printf("Reading the key...\n");

    // reads the cloud key from file
    FILE *cloud_key = fopen("cloud.key", "rb");
    TFheGateBootstrappingCloudKeySet *bk = new_tfheGateBootstrappingCloudKeySet_fromFile(cloud_key);
    fclose(cloud_key);

    // if necessary, the params are inside the key
    const TFheGateBootstrappingParameterSet *params = bk->params;

    printf("Reading the query data...\n");
    printf("Executing....");
    // read the ciphertexts from the query file//
    ciphertext.ciphertext1 = new_gate_bootstrapping_ciphertext_array(BLEN, params);
    ciphertext.ciphertext2 = new_gate_bootstrapping_ciphertext_array(BLEN, params);
    LweSample *result_val = new_gate_bootstrapping_ciphertext_array(BLEN, params);
    FILE *query_data = fopen("query.data", "rb");
    for (int i = 0; i < BLEN; i++)
    {
        import_gate_bootstrapping_ciphertext_fromFile(query_data, &ciphertext.ciphertext1[i], params);
        import_gate_bootstrapping_ciphertext_fromFile(query_data, &ciphertext.ciphertext2[i], params);
    }
    fclose(query_data);

    // Addition//
    Adder(result_val, ciphertext.ciphertext1, ciphertext.ciphertext2, BLEN, bk);

    // export the answer to a file (for the cloud)
    FILE *answer_data = fopen("answer.data", "wb");
    for (int n = 0; n < BLEN; n++)
    {
        export_gate_bootstrapping_ciphertext_toFile(answer_data, &result_val[n], params);
    }

    fclose(answer_data);

    // clean up all pointers

    delete_gate_bootstrapping_ciphertext_array(BLEN, ciphertext.ciphertext1);
    delete_gate_bootstrapping_ciphertext_array(BLEN, ciphertext.ciphertext2);
    delete_gate_bootstrapping_ciphertext_array(BLEN, result_val);
    delete_gate_bootstrapping_cloud_keyset(bk);

    time_t end_time = clock();
    printf("\nResult is stored in cloud answer file! Time to execute %ld second\n", (end_time - start_time) / 1000000);
    return 0;
}