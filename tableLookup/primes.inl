inline primes_s::primes_s()
{
   primes[0] = 2;
   primes[1] = 3;
   primes[2] = 5;
   primes[3] = 7;
   primes[4] = 11;
   primes[5] = 13;
   primes[6] = 17;
   primes[7] = 19;
   primes[8] = 23;
   primes[9] = 29;
   primes[10] = 31;
   primes[11] = 37;
   primes[12] = 41;
   primes[13] = 43;
   primes[14] = 47;
   primes[15] = 53;
   primes[16] = 59;
   primes[17] = 61;
   primes[18] = 67;
   primes[19] = 71;
   primes[20] = 73;
   primes[21] = 79;
   primes[22] = 83;
   primes[23] = 89;
   primes[24] = 97;
   primes[25] = 101;
   primes[26] = 103;
   primes[27] = 107;
   primes[28] = 109;
   primes[29] = 113;
   primes[30] = 127;
   primes[31] = 131;
   primes[32] = 137;
   primes[33] = 139;
   primes[34] = 149;
   primes[35] = 151;
   primes[36] = 157;
   primes[37] = 163;
   primes[38] = 167;
   primes[39] = 173;
   primes[40] = 179;
   primes[41] = 181;
   primes[42] = 191;
   primes[43] = 193;
   primes[44] = 197;
   primes[45] = 199;
   primes[46] = 211;
   primes[47] = 223;
   primes[48] = 227;
   primes[49] = 229;
   primes[50] = 233;
   primes[51] = 239;
}

inline const primes_s &primes_s::getInstance()
{
   static primes_s instance;

   return instance;
}

inline const unsigned long long int &primes_s::operator[](unsigned int i) const
{
   return primes[i];
}
