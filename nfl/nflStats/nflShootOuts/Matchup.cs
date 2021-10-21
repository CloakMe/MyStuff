using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace nflShootOuts
{
    public class Matchup
    {        
        public string awayTeam;
        public int awayTeamOffensiveRankFPTS;
        public int awayTeamDefensiveRank;

        public string homeTeam;
        public int homeTeamOffensiveRankFPTS;
        public int homeTeamDefensiveRank;

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            string daway_offense = (homeTeamDefensiveRank - awayTeamOffensiveRankFPTS).ToString("+#;-#;+0");
            daway_offense = daway_offense.Count() == 2 ? daway_offense + " " : daway_offense;
            result.AppendFormat(
                "{0,2} ({1,2}) {2,2} ",
                awayTeamOffensiveRankFPTS, daway_offense, awayTeamDefensiveRank);
            result.Append(awayTeam);
            for(int i=awayTeam.Count(); i< 14; i++)
                result.Append(" ");

            result.AppendFormat("VS {0} ", homeTeam);
            for (int i = homeTeam.Count(); i < 14; i++)
                result.Append(" ");

            string dhome_offense = (awayTeamDefensiveRank - homeTeamOffensiveRankFPTS).ToString("+#;-#;+0");
            dhome_offense = dhome_offense.Count() == 2 ? dhome_offense + " " : dhome_offense;
            result.AppendFormat("{0,2} ({1,2}) {2,2} ",
                homeTeamOffensiveRankFPTS, dhome_offense,homeTeamDefensiveRank);

            if (awayTeamOffensiveRankFPTS + 9 < homeTeamDefensiveRank && homeTeamOffensiveRankFPTS + 5 < awayTeamDefensiveRank)
                result.AppendFormat(" SHOOT OUT!");
            else if (awayTeamOffensiveRankFPTS + 6 < homeTeamDefensiveRank && homeTeamOffensiveRankFPTS + 3 < awayTeamDefensiveRank)
                result.AppendFormat(" ShOoT OuT!");
            else if (awayTeamOffensiveRankFPTS + 3 < homeTeamDefensiveRank && homeTeamOffensiveRankFPTS + 1 < awayTeamDefensiveRank)
                result.AppendFormat(" shoot out!");
            else if (awayTeamOffensiveRankFPTS - 6 > homeTeamDefensiveRank && homeTeamOffensiveRankFPTS - 9 > awayTeamDefensiveRank)
                result.AppendFormat(" STINGY!");
            else if (awayTeamOffensiveRankFPTS - 4 > homeTeamDefensiveRank && homeTeamOffensiveRankFPTS - 6 > awayTeamDefensiveRank)
                result.AppendFormat(" StInGy!");
            else if (awayTeamOffensiveRankFPTS - 2 > homeTeamDefensiveRank && homeTeamOffensiveRankFPTS - 3 > awayTeamDefensiveRank)
                result.AppendFormat(" stingy!");
            else if (awayTeamOffensiveRankFPTS + 9 < homeTeamDefensiveRank)
                result.AppendFormat( " opt " + awayTeam);
            else if (homeTeamOffensiveRankFPTS + 5 < awayTeamDefensiveRank)
                result.AppendFormat( " opt " + homeTeam);

            return result.ToString();
        }
    }
}
