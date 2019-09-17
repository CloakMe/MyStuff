using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatrixLayerRotation
{
    static class ArrayUtility
    {
        private static T[] SubArray<T>(this T[] data, int index, int length)
        {
            T[] result = new T[length];
            Array.Copy(data, index, result, 0, length);
            return result;
        }

        public static int[] ReArrangeArray(int[] oldArray, int cutPos)
        {
            if (cutPos == 0)
                return oldArray;
            int[] subFront = oldArray.SubArray(cutPos, oldArray.Length - cutPos); // contains {3,4,5,6}
            int[] subBack = oldArray.SubArray(0, cutPos);

            int[] newArray = new int[subFront.Length + subBack.Length];
            Array.Copy(subFront, newArray, subFront.Length);
            Array.Copy(subBack, 0, newArray, subFront.Length, subBack.Length);

            return newArray;
        }
    }
}
