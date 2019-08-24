using System;
namespace MazeGame.Common
{
    public class RandomGenerator
    {
        private readonly Random rnd;

        public RandomGenerator()
        {
            this.rnd = new Random();
        }

        public int GetNumber(int minValue, int maxValue)
        {
            return this.rnd.Next(minValue, maxValue);
        }
            
    }
}
