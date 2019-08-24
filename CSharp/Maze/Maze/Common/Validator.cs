using System;

namespace MazeGame.Common
{
    public static class Validator
    {
        private const string emtpyOrNullStringMsg = "Cannot process empty or null string!";
        private const string nullObjectMsg = "Cannot pass null objects to method!";

        public static void CheckStringIfNullOrEmpty(string str)
        {
            if (str == String.Empty || str == null)
            {
                throw new InvalidOperationException(emtpyOrNullStringMsg);
            }
        }

        public static void CheckObjectIsNull(object obj)
        {
            if (obj == null)
            {
                throw new NullReferenceException(nullObjectMsg);
            }
        }
    }
}
