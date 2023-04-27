void compare_bit(LweSample* result, const LweSample* a, const LweSample* b, LweSample* lsb_carry, LweSample* tmp, const TFheGateBootstrappingCloudKeySet* bk) {
     LweSample* temp1=new_gate_bootstrapping_ciphertext_array(1, bk->params);
    LweSample* temp2=new_gate_bootstrapping_ciphertext_array(1, bk->params);
    LweSample* temp3=new_gate_bootstrapping_ciphertext_array(1,bk->params);
    LweSample* temp4=new_gate_bootstrapping_ciphertext_array(1,bk->params);
    LweSample* temp5=new_gate_bootstrapping_ciphertext_array(1,bk->params);

    bootsXOR(temp1, a, b, bk);  //a xorb
    // printf(" a xor b executed");   
    bootsXOR(result,temp1,lsb_carry,bk);  //a xor b xor ci
    
    bootsNOT(temp4,a,bk);  // complement of a
    bootsAND(temp3,temp4,b,bk); // complement a and b

    bootsNOT(temp5,temp1,bk);  // complement of a XOR b

    bootsAND(temp2,temp5,lsb_carry,bk);// complement of a XOR b AND lasb_carry
  
    bootsOR(tmp,temp2,temp3,bk);       // a&b + ci*(a xor b)
    bootsCOPY(lsb_carry,tmp,bk);

   //bootsXNOR(result,a,b,bk);
  /*FILE* secret_key = fopen("secret.key","rb");
    TFheGateBootstrappingSecretKeySet* key = new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
     int ir = bootsSymDecrypt(result, key)>0;
     int co=bootsSymDecrypt(tmp, key)>0;
    int ir1 = bootsSymDecrypt(a, key)>0;
     int co1=bootsSymDecrypt(b, key)>0;
    printf("result=%d",ir);
    printf(" carry=%d",co);
    printf("a=%d",ir1);
    printf("b=%d\n",co1);
	fclose(secret_key);*/
   

    //printf(" carry calculation completed");*/
    //bootsMUX(result, tmp, lsb_carry, a, bk);
}


 void Addition(LweSample* top1, const LweSample* a6, const LweSample* b6, LweSample* lsb_carry1, LweSample* tmp6, const TFheGateBootstrappingCloudKeySet* bk) {
     LweSample* temp1=new_gate_bootstrapping_ciphertext_array(1, bk->params);
    LweSample* temp2=new_gate_bootstrapping_ciphertext_array(1, bk->params);
    LweSample* temp3=new_gate_bootstrapping_ciphertext_array(1,bk->params);
    
    bootsXOR(temp1, a6, b6, bk);  //a xorb
    // printf(" a xor b executed");   
    bootsXOR(top1,temp1,lsb_carry1,bk);  //a xor b xor ci
    //printf("a xorb xor c ");
    bootsAND(temp2,temp1,lsb_carry1,bk);   //ci and (a xor b)
    //printf("ci and axor b");
    bootsAND(temp3,a6,b6,bk);             // a and b 
   // printf("a and b");
    bootsOR(tmp6,temp2,temp3,bk);       // a&b + ci*(a xor b)
    bootsCOPY(lsb_carry1,tmp6,bk);


}
