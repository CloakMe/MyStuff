using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MatrixLayerRotation;

namespace MatrixLayerRotation
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] mnr = Console.ReadLine().TrimEnd().Split(' ');

            int m = Convert.ToInt32(mnr[0]);

            int n = Convert.ToInt32(mnr[1]);

            int r = Convert.ToInt32(mnr[2]);

            int[,] matrix = new int[m,n];


            for (int i = 0; i < m; i++)
            {
                int[] inArray = (Console.ReadLine().TrimEnd().Split(' ').ToArray().Select(matrixTemp => Convert.ToInt32(matrixTemp)).ToArray());
                for (int j = 0; j < n; j++)
                {
                    matrix[i, j] = inArray[j];
                }
            }
                
            int minValue = m < n ? m : n;
            HMatrix hMatrix = new HMatrix(matrix);
            for (int k = 0; k <= (minValue - 1) / 2; k++)
            {
                Point currentPoint = new Point(k,k);
                int[] array = hMatrix.DisplaceArrayFromMatrix(currentPoint);
                int rot = r % array.Length;
                int[] newArray = ArrayUtility.ReArrangeArray(array, rot);
                hMatrix.InsertArrayToMatrix(currentPoint, newArray);
            }

            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Console.Write(matrix[i, j]);
                    if(j < n-1)
                        Console.Write(' ');
                }
                Console.WriteLine();
            }

            bool breakPoint = true;
            int res = 54 % 3;
        }
    }
}
