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
            Console.WriteLine("Select week ranking:");
            string weekrank = Console.ReadLine();
            string offensiveRankFileName = @"F:\who\MyStuff\nfl\OffensiveRankingFPTSw";
            offensiveRankFileName += weekrank + ".txt";
            // Read the file and display it line by line.  
            using (StreamReader reader = new StreamReader(offensiveRankFileName))
            {
                string line = reader.ReadLine();

                while (line != null)
                {
                    if (line.Count() > 12)
                    {
                        OffensiveRankingFPTS[subCounter] = line;
                        subCounter++;
                    }
                    counter++;
                    line = reader.ReadLine();
                }
            }
            System.Console.WriteLine("There were {0} lines.", counter);

            string[] DefensiveRanking = new string[32];
            subCounter = 0;
            string defensiveRankFileName = @"F:\who\MyStuff\nfl\DefensiveRankingw";
            defensiveRankFileName += weekrank + ".txt";
            using (StreamReader reader = new StreamReader(defensiveRankFileName))
            {
                string line = reader.ReadLine();

                while (line != null)
                {
                    if (line.Count() > 12)
                    {
                        DefensiveRanking[subCounter] = line;
                        subCounter++;
                    }
                    counter++;
                    line = reader.ReadLine();
                }
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
            string fileName = @"F:\who\MyStuff\nfl\MatchupWeek" + fileNumber + ".txt";
            using (StreamReader reader = new StreamReader(fileName))
            {
                string line = "";

                while (true)
                {
                    line = reader.ReadLine();
                    if (line == null)
                        break;
                    if (subCounter == 1 && 
                        !line.Contains("Monday") &&
                        !line.Contains("matchup") && 
                        !line.Contains("Thursday") && 
                        !line.Contains("Friday") && !line.Contains("Saturday") && !line.Contains("Sunday"))
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
            }
            System.Console.WriteLine("There were {0} lines.", counter);
        }
    }
}
