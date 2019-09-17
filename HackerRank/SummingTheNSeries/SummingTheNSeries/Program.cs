using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
class Solution {

    /*
     * Complete the summingSeries function below.
     */
    static int summingSeries(long n) {
        /*
         * Write your code here.
         */
        BigInteger nSq = (BigInteger) n*n;
        BigInteger someNumber = (BigInteger ) (Math.Pow(10, 9) + 7);
        int res = (int)(nSq % someNumber);
        return  res;
    }

    static void Main(string[] args) {
        int t = Convert.ToInt32(Console.ReadLine());

        for (int tItr = 0; tItr < t; tItr++) {
            long n = Convert.ToInt64(Console.ReadLine());

            int result = summingSeries(n);

            Console.WriteLine(result);
        }

    }
}
