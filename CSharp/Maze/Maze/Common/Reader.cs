using System;

namespace MazeGame.Common
{
    public class Reader
    {
        public string Read() 
        { 
            return Console.ReadLine();
        }

        public int ReadInt()
        { 
            return int.Parse(Console.ReadLine()); 
        }
    }
}
     