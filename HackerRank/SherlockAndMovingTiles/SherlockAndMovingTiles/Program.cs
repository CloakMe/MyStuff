using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace SherlockAndMovingTiles
{
    class Solution
    {
        static unsafe double[] movingTiles(BigInteger l, BigInteger s1, BigInteger s2, BigInteger[] queries)
        {
            double[] times = new double[queries.Length];

            BigInteger diff = s1 > s2 ? s1 - s2 : s2 - s1;

            for (int i = 0; i < queries.Length; i++)
            {
                double t = Math.Sqrt((double)2) * (double)l - Math.Sqrt((double)2.0) * Math.Sqrt((double)queries[i]);
                t = t / (double)diff;
                times[i] = t;
            }
            return times;
        }

        static unsafe void Main(string[] args)
        {
            // Read the file and display it line by line.  
            System.IO.StreamReader file =
                new System.IO.StreamReader("input.txt");
            string line;
            string[] lS1S2;
            BigInteger l = 0, s1 = 0, s2 = 0;
            if((line = file.ReadLine()) != null)
            {
                lS1S2 = line.Split(' ');
                l = BigInteger.Parse(lS1S2[0]);

                s1 = BigInteger.Parse(lS1S2[1]);

                s2 = BigInteger.Parse(lS1S2[2]);
            }

            int queriesCount = 0 ;
            if ((line = file.ReadLine()) != null)
            {
                queriesCount = Convert.ToInt32(line);
            }

            BigInteger[] queries = new BigInteger[queriesCount];
            int counter = 0;
            
            while ((line = file.ReadLine()) != null)
            {
                BigInteger queriesItem = BigInteger.Parse(line);
                queries[counter] = queriesItem;
                counter++;
            }
            file.Close();

            double[] result = movingTiles(l, s1, s2, queries);


            System.IO.StreamReader file2 =
                new System.IO.StreamReader("output.txt");

            counter = 0;
            double[] resultExpected = new double[queriesCount];
            while ((line = file2.ReadLine()) != null)
            {
                double resultItem = double.Parse(line);
                resultExpected[counter] = resultItem;
                counter++;
            }

            bool breakHere = false;
            double maxVal = -1.0;
            int save = 0;
            for (int i = 0; i < queriesCount; i++)
            {
                if (Math.Abs(resultExpected[i] - result[i]) > 0.000000001)
                    breakHere = true;
                if (result[i] > maxVal)
                {
                    maxVal = result[i];
                    save = i;
                }
            }
            Console.WriteLine(result[32882]);
            bool yo = true;
        }
    }
}
