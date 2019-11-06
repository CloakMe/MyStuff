using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using System.Collections.Generic;


namespace PerfectionQuotents
{
    class Solution
    {
        static bool IsPerfQuotant(BigInteger value)
        {
            if (value % 2 == 1)
                return false;

            BigInteger sqrtVal = (BigInteger) Math.Sqrt((double)value);

            BigInteger sum = value + 1;
            BigInteger i = 2;
            int counter = 0;
            while (i <= sqrtVal)
            {
                if (value % i == 0)
                {
                    sum += i + value / i;
                    counter++;
                }                    
                i++;
            }

            BigInteger residual = sum % value;
            if(residual * 2 == value)
                return true;

            return false;
        }

        static bool IsPerfQuotant2(BigInteger value)
        {
            int[] powers = new int[divLen];

            BigInteger valueClone = value;
            HashSet<int> powerPosition = new HashSet<int>();
            for (int i = 0; i < divisors.Length; i++)
            {
                while (valueClone % divisors[i] == 0)
                {
                    valueClone = valueClone / divisors[i];
                    powers[i]++;
                    powerPosition.Add(i);
                }
            }

            BigInteger allCombinations = 1;
            foreach (int pos in powerPosition)
            {
                allCombinations *= (powers[pos] + 1);
            }

            BigInteger sum = 0;
            //HashSet<BigInteger> divisorSet = new HashSet<BigInteger>();
            int counter = 0;
            for (BigInteger i = 0; i < allCombinations; i++)
            {
                BigInteger allCombinationsClone = i;
                BigInteger divisor = 1;
                foreach (int pos in powerPosition)
                {
                    int pow = (int)(allCombinationsClone % (BigInteger) (powers[pos] + 1));
                    allCombinationsClone = allCombinationsClone / (powers[pos] + 1);
                    divisor *= BigInteger.Pow(divisors[pos], pow);
                }
                //divisorSet.Add(divisor);
                counter++;
                sum += divisor;
            }

            BigInteger residual = sum % value;
            if (residual * 2 == value)
            {
                Console.Write(value);
                Console.Write(" ");
                Console.WriteLine(counter);
                return true;
            }
            return false;
        }

        public static ulong[] divisors = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
                                 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
                                 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
                                 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 
                                 241, 251, 257, 263, 269, 271, 277 ,281, 283, 293, 307, 311, 313, 
                                 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 
                                 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 
                                 479, 487, 491, 499 };//
        
        public static int divLen = divisors.Count();
        static bool IsPerfQuotant3(ulong value)
        {
            int[] powers = new int[divLen];

            ulong valueClone = value;
            HashSet<int> powerPosition = new HashSet<int>();
            for (int i = 0; i < divisors.Length; i++)
            {
                while (valueClone % divisors[i] == 0)
                {
                    valueClone = valueClone / divisors[i];
                    powers[i]++;
                    powerPosition.Add(i);
                }
            }
            //==============================================
            //HashSet<int> powerPosition 
            //int[] powers //divLen
            ulong allCombinations = 1;
            foreach (int pos in powerPosition)
            {
                allCombinations *= (ulong)(powers[pos] + 1);
            }


            ulong sum = 0;
            //HashSet<BigInteger> divisorSet = new HashSet<BigInteger>();
            for (ulong i = 0; i < allCombinations; i++)
            {
                ulong allCombinationsClone = i;
                ulong divisor = 1;
                foreach (int pos in powerPosition)
                {
                    int pow = (int)(allCombinationsClone % (ulong)(powers[pos] + 1));
                    allCombinationsClone = allCombinationsClone / (ulong)(powers[pos] + 1);
                    for (int k = 0; k < pow; k++)
                        divisor *= divisors[pos];
                }
                //divisorSet.Add(divisor);
                sum += divisor;
            }

            ulong residual = sum % value;
            if (residual * 2 == value)
            {
                Console.Write(value);
                Console.Write(" ");
                Console.Write(divisors[powerPosition.Last()]);
                Console.Write(" ");
                Console.WriteLine(allCombinations);
                return true;
            }
            return false;
        }


        static string getSum(BigInteger value, List<BigInteger> set, List<BigInteger> resList)
        {
            
            for (int i = 1; i < set.Count; i++)
            {
                if (set[i-1] <= value && value < set[i] )
                    return resList[i - 1].ToString();
            }

            return resList[resList.Count-1].ToString();
        }

        static void Main(string[] args)
        {
            List<BigInteger> set = new List<BigInteger>();
            List<BigInteger> resList = new List<BigInteger>();   
            set.Add(2);
            set.Add(24);           
            set.Add(4320);
            set.Add(4680);
            set.Add(26208);            
            set.Add(8910720);
            set.Add(17428320);
            set.Add(20427264);
            set.Add(91963648);
            set.Add(197064960);
            set.Add(8583644160);
            set.Add(10200236032);
            set.Add(21857648640);
            set.Add(57575890944);
            set.Add(57629644800);            
            set.Add(206166804480);
            set.Add(17116004505600);
            set.Add(1416963251404800);            
            set.Add(15338300494970880);
            set.Add(75462255348480000);
            set.Add(88898072401645056);
            set.Add(301183421949935616);
            set.Add(6219051710415667200);
            set.Add(6275163455171297280);    
            
            set.Add( BigInteger.Parse("14031414189615513600")); 
            set.Add( BigInteger.Parse("200286975596707184640") );
            
            set.Add( BigInteger.Parse("215594611071909888000") );
            set.Add( BigInteger.Parse("352444116692828160000"));
            set.Add( BigInteger.Parse("835095457414213632000"));
            set.Add( BigInteger.Parse("5997579964837140234240"));
            set.Add( BigInteger.Parse("39887491844324122951680"));
            set.Add( BigInteger.Parse("59485231752222033838080"));
            set.Add( BigInteger.Parse("64031599488357236736000"));
            set.Add( BigInteger.Parse("189478877946949032837120"));
            set.Add( BigInteger.Parse("464993138593758319902720"));
                

            //BigInteger summ = 0;
            //for (int i = 0; i < set.Count; i++)
            //{
            //    if (i < set.Count-1)
            //        if (set[i] > set[i + 1])
            //            Console.WriteLine("ERROR");
            //    summ = 0;
            //    for (int j = 0; j <= i; j++)
            //    {
            //        summ += set[j];
            //    }
            //    Console.WriteLine(summ);
            //}

            //return;

            resList.Add(2);
            resList.Add(26);
            resList.Add(4346);
            resList.Add(9026);
            resList.Add(35234);
            resList.Add(8945954);
            resList.Add(26374274);
            resList.Add(46801538);
            resList.Add(138765186);
            resList.Add(335830146);
            resList.Add(8919474306);
            resList.Add(19119710338);
            resList.Add(40977358978);
            resList.Add(98553249922);
            resList.Add(156182894722);
            resList.Add(362349699202);
            resList.Add(17478354204802);
            resList.Add(1434441605609602);
            resList.Add(16772742100580482);
            resList.Add(92234997449060482);
            resList.Add(181133069850705538);
            resList.Add(482316491800641154);
            resList.Add(6701368202216308354);
            resList.Add(12976531657387605634);
            resList.Add(BigInteger.Parse("27007945847003119234"));
            resList.Add(BigInteger.Parse("227294921443710303874"));
            resList.Add(BigInteger.Parse("442889532515620191874"));
            resList.Add(BigInteger.Parse("795333649208448351874"));
            resList.Add(BigInteger.Parse("1630429106622661983874"));
            resList.Add(BigInteger.Parse("7628009071459802218114"));
            resList.Add(BigInteger.Parse("47515500915783925169794"));
            resList.Add(BigInteger.Parse("107000732668005959007874"));
            resList.Add(BigInteger.Parse("171032332156363195743874"));
            resList.Add(BigInteger.Parse("360511210103312228580994"));
            resList.Add(BigInteger.Parse("825504348697070548483714"));
       

            string stringN =   Console.ReadLine(); //"100000000000000000000000"

            BigInteger N = BigInteger.Parse(stringN);
            string res = getSum(N,set,resList);
            Console.WriteLine(res);     
        }
    }
}
