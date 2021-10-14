using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace nflShootOuts
{
    class Program
    {
        
        static void Main(string[] args)
        {
            int counter = 0;
            int subCounter = 0;
            string[] OffensiveRankingFPTS = new string[32];
            // Read the file and display it line by line.  
            foreach (string line in System.IO.File.ReadLines(@"F:\who\nfl\OffensiveRankingFPTS.txt"))
            {                
                if (line.Count() > 12)
                {
                    OffensiveRankingFPTS[subCounter] = line;
                    subCounter++;
                }
                counter++;
            }
            System.Console.WriteLine("There were {0} lines.", counter);

            string[] DefensiveRanking = new string[32];
            subCounter = 0;
            foreach (string line in System.IO.File.ReadLines(@"F:\who\nfl\DefensiveRanking.txt"))
            {
                if (line.Count() > 12)
                {
                    DefensiveRanking[subCounter] = line;
                    subCounter++;
                }
                counter++;
            }
            System.Console.WriteLine("There were {0} lines.", counter);

            while (true)
            {
                System.Console.Write(">");
                string command = System.Console.ReadLine();
                if (command.Contains("exit"))
                {
                    break;
                }

                CreateMatchupTable(OffensiveRankingFPTS, DefensiveRanking, command);
            }
            
        }

        static void CreateMatchupTable(string[] OffensiveRankingFPTS, string[] DefensiveRanking, string fileNumber)
        {
            int counter = 0;
            int subCounter = 0;
            bool flag = false;
            Matchup matchup = new Matchup();
            List<Matchup> matchups = new List<Matchup>();
            string fileName = @"F:\who\nfl\MatchupWeek" + fileNumber + ".txt";
            foreach (string line in System.IO.File.ReadLines(fileName))
            {
                if (subCounter == 1 && !line.Contains("Sunday") && !line.Contains("Monday") && !line.Contains("Thursday"))
                {//next line after matchup
                    matchup.awayTeam = line.Replace("[\n\r]", "").Trim();
                    matchup.awayTeamOffensiveRankFPTS = 1 + Array.FindIndex(OffensiveRankingFPTS, (x) => x.Contains(matchup.awayTeam));
                    matchup.awayTeamDefensiveRank = 1 + Array.FindIndex(DefensiveRanking, (x) => x.Contains(matchup.awayTeam));
                    subCounter++;
                    flag = true;
                    continue;
                }

                if (subCounter == 2 && flag)
                {//next next line after matchup
                    matchup.homeTeam = line.Replace("[\n\r]", "").Trim();
                    matchup.homeTeamOffensiveRankFPTS = 1 + Array.FindIndex(OffensiveRankingFPTS, (x) => x.Contains(matchup.homeTeam));
                    matchup.homeTeamDefensiveRank = 1 + Array.FindIndex(DefensiveRanking, (x) => x.Contains(matchup.homeTeam));
                    subCounter++;
                    matchups.Add(matchup);
                    System.Console.WriteLine(matchup.ToString());
                    matchup = new Matchup();
                    flag = false;
                    continue;
                }

                if (line.Contains("matchup") || line.Contains("Tickets") || line[0] == '\t')
                {
                    subCounter = 0;
                    subCounter++;
                }
                else
                {
                    subCounter++;
                }

                counter++;
            }
            System.Console.WriteLine("There were {0} lines.", counter);
        }
    }
}
