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
        public int awayTeamOffensiveRank;
        public int awayTeamDefensiveRank;

        public string homeTeam;
        public int homeTeamOffensiveRank;
        public int homeTeamDefensiveRank;

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            string daway_offense = (homeTeamDefensiveRank - awayTeamOffensiveRank).ToString("+#;-#;+0");
            daway_offense = daway_offense.Count() == 2 ? daway_offense + " " : daway_offense;
            result.AppendFormat(
                "{0,2} ({1,2}) {2,2} ",
                awayTeamOffensiveRank, daway_offense, awayTeamDefensiveRank);
            result.Append(awayTeam);
            for(int i=awayTeam.Count(); i< 14; i++)
                result.Append(" ");

            result.AppendFormat("VS {0} ", homeTeam);
            for (int i = homeTeam.Count(); i < 14; i++)
                result.Append(" ");

            string dhome_offense = (awayTeamDefensiveRank - homeTeamOffensiveRank).ToString("+#;-#;+0");
            dhome_offense = dhome_offense.Count() == 2 ? dhome_offense + " " : dhome_offense;
            result.AppendFormat("{0,2} ({1,2}) {2,2} ",
                homeTeamOffensiveRank, dhome_offense,homeTeamDefensiveRank);

            if (awayTeamOffensiveRank + 9 < homeTeamDefensiveRank && homeTeamOffensiveRank + 5 < awayTeamDefensiveRank)
                result.AppendFormat(" SHOOT OUT!");
            else if (awayTeamOffensiveRank + 6 < homeTeamDefensiveRank && homeTeamOffensiveRank + 3 < awayTeamDefensiveRank)
                result.AppendFormat(" ShOoT OuT!");
            else if (awayTeamOffensiveRank + 3 < homeTeamDefensiveRank && homeTeamOffensiveRank + 1 < awayTeamDefensiveRank)
                result.AppendFormat(" shoot out!");
            else if (awayTeamOffensiveRank - 6 > homeTeamDefensiveRank && homeTeamOffensiveRank - 9 > awayTeamDefensiveRank)
                result.AppendFormat(" STINGY!");
            else if (awayTeamOffensiveRank - 4 > homeTeamDefensiveRank && homeTeamOffensiveRank - 6 > awayTeamDefensiveRank)
                result.AppendFormat(" StInGy!");
            else if (awayTeamOffensiveRank - 2 > homeTeamDefensiveRank && homeTeamOffensiveRank - 3 > awayTeamDefensiveRank)
                result.AppendFormat(" stingy!");
            else if (awayTeamOffensiveRank + 9 < homeTeamDefensiveRank)
                result.AppendFormat( " opt " + awayTeam);
            else if (homeTeamOffensiveRank + 5 < awayTeamDefensiveRank)
                result.AppendFormat( " opt " + homeTeam);

            return result.ToString();
        }
    }
}
