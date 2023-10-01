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
            string[] OffensiveRanking = new string[32];
            Console.WriteLine("Select week ranking:");
            string weekrank = Console.ReadLine();
            string offensiveRankFileName = @"F:\who\MyStuff\nfl\OffensiveRankingw";
            offensiveRankFileName += weekrank + ".txt";
            // Read the file and display it line by line.  
            try
            {
                using (StreamReader reader = new StreamReader(offensiveRankFileName))
                {
                    string line = reader.ReadLine();

                    while (line != null)
                    {
                        if (line.Count() > 12)
                        {
                            if (subCounter == 0 || (!line.Contains(OffensiveRanking[subCounter-1]) && !OffensiveRanking[subCounter-1].Contains(line)))
                            {
                                OffensiveRanking[subCounter] = line;
                                subCounter++;
                            }
                        }
                        counter++;
                        line = reader.ReadLine();
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine("Could not read/find week OFENSIVE ranking file!");
                return;
            }
            
            System.Console.WriteLine("There were {0} lines.", counter);

            string[] DefensiveRanking = new string[32];
            subCounter = 0;
            string defensiveRankFileName = @"F:\who\MyStuff\nfl\DefensiveRankingw";
            defensiveRankFileName += weekrank + ".txt";
            try
            {
                using (StreamReader reader = new StreamReader(defensiveRankFileName))
                {
                    string line = reader.ReadLine();

                    while (line != null)
                    {
                        if (line.Count() > 12)
                        {
                            if (subCounter == 0 || (!line.Contains(DefensiveRanking[subCounter - 1]) && !DefensiveRanking[subCounter - 1].Contains(line)))
                            {
                                DefensiveRanking[subCounter] = line;
                                subCounter++;
                            }
                        }
                        counter++;
                        line = reader.ReadLine();
                    }
                }
            }
            catch (Exception)
            {
                Console.WriteLine("Could not read/find week DEFENSIVE ranking file!");
                return;
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
                try
                {
                    CreateMatchupTable(OffensiveRanking, DefensiveRanking, command);
                }
                catch(Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    Console.WriteLine(ex.StackTrace);
                    Console.WriteLine("\nTry again\n");
                }

            }
            
        }

        static void CreateMatchupTable(string[] OffensiveRanking, string[] DefensiveRanking, string fileNumber)
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
                        !line.Contains("------") &&
                        !line.Contains("Monday") &&
                        !line.Contains("Tuesday") &&
                        !line.Contains("matchup") && 
                        !line.Contains("MATCHUP") && 
                        !line.Contains("Thursday") && 
                        !line.Contains("Friday") && !line.Contains("Saturday") && !line.Contains("Sunday"))
                    {//next line after matchup
                        matchup.awayTeam = line.Replace("[\n\r]", "").Trim();
                        matchup.awayTeamOffensiveRank = 1 + Array.FindIndex(OffensiveRanking, (x) => x.Contains(matchup.awayTeam));
                        matchup.awayTeamDefensiveRank = 1 + Array.FindIndex(DefensiveRanking, (x) => x.Contains(matchup.awayTeam));
                        subCounter++;
                        flag = true;
                        continue;
                    }

                    if (subCounter == 2 && flag)
                    {//next next line after matchup
                        matchup.homeTeam = line.Replace("[\n\r]", "").Trim();
                        matchup.homeTeamOffensiveRank = 1 + Array.FindIndex(OffensiveRanking, (x) => x.Contains(matchup.homeTeam));
                        matchup.homeTeamDefensiveRank = 1 + Array.FindIndex(DefensiveRanking, (x) => x.Contains(matchup.homeTeam));
                        subCounter++;
                        matchups.Add(matchup);
                        System.Console.WriteLine(matchup.ToString());
                        matchup = new Matchup();
                        flag = false;
                        continue;
                    }

                    if (line.Contains("matchup") || line.Contains("------") || line.Contains("MATCHUP") || line.Contains("Tickets") || line[0] == '\t')
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
