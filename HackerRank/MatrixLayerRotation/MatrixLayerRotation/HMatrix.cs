using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using MatrixLayerRotation;


namespace MatrixLayerRotation
{
    class HMatrix
    {
        int[,] matrix;
        public HMatrix(int[,] matrix)
        {
            this.matrix = matrix;
            RowSize = matrix.GetLength(0);
            ColSize = matrix.GetLength(1);
        }

        public int RowSize { get; private set; }
        public int ColSize { get; private set; }

        public int[] DisplaceArrayFromMatrix(Point displacePos)
        {
            Point endPoint = new Point(RowSize - displacePos.Row - 1, ColSize - displacePos.Col - 1);

            int arraySize = 0;
            if (endPoint.Row == displacePos.Row && endPoint.Col == displacePos.Col)
                arraySize = 1;
            else if (endPoint.Row == displacePos.Row && endPoint.Col != displacePos.Col)
                arraySize = (endPoint.Col - displacePos.Col + 1);
            else if (endPoint.Row != displacePos.Row && endPoint.Col == displacePos.Col)
                arraySize = (endPoint.Row - displacePos.Row + 1);
            else if (endPoint.Row != displacePos.Row && endPoint.Col != displacePos.Col)
                arraySize = (endPoint.Row - displacePos.Row + 1) * 2 + (endPoint.Col - displacePos.Col + 1) * 2 - 4;

            int[] array = new int[arraySize];
            int counter = 0,
                i = 0,
                j = 0;

            i = displacePos.Row;
            {
                for (j = displacePos.Col; j <= endPoint.Col; j++)
                {
                    array[counter] = matrix[i, j];
                    counter++;
                }//for Col
            }

            j = endPoint.Col;
            for (i = displacePos.Row + 1; i <= endPoint.Row; i++)
            {
                array[counter] = matrix[i, j];
                counter++;
            }//for Row


            i = endPoint.Row;
            {
                for (j = endPoint.Col - 1; j >= displacePos.Col; j--)
                {
                    array[counter] = matrix[i, j];
                    counter++;
                }//for Col
            }//for Row

            j = displacePos.Col;
            for (i = endPoint.Row - 1; i > displacePos.Row; i--)
            {
                array[counter] = matrix[i, j];
                counter++;
            }//for Row

            if( counter != arraySize)
                throw( new ArgumentOutOfRangeException("The expected array size is invalid!"));
            return array;
        }

        public void InsertArrayToMatrix(Point insertPos, int[] array)
        {
            Point endPoint = new Point(RowSize - insertPos.Row - 1, ColSize - insertPos.Col - 1);


            int counter = 0,
                i = 0,
                j = 0;

            i = insertPos.Row;
            {
                for (j = insertPos.Col; j <= endPoint.Col; j++)
                {
                    matrix[i, j] = array[counter];
                    counter++;
                }//for Col
            }

            j = endPoint.Col;
            for (i = insertPos.Row + 1; i <= endPoint.Row; i++)
            {
                matrix[i, j] = array[counter];
                counter++;
            }//for Row


            i = endPoint.Row;
            {
                for (j = endPoint.Col - 1; j >= insertPos.Col; j--)
                {
                    matrix[i, j] = array[counter];
                    counter++;
                }//for Col
            }//for Row

            j = insertPos.Col;
            for (i = endPoint.Row - 1; i > insertPos.Row; i--)
            {
                matrix[i, j] = array[counter];
                counter++;
            }//for Row

            if (counter != array.Length)
                throw (new ArgumentOutOfRangeException("The expected array size is invalid!"));
        }
    }
}
