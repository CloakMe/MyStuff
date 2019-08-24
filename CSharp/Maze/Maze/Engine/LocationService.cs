using System;
using System.Linq;
using MazeGame.Common;
using MazeGame.Items.Interfaces;
using MazeGame.Rooms.Interfaces;
using MazeGame.Renderer.Interfaces;
using MazeGame.Engine.Interfaces;
using MazeGame.Exits.Interfaces;
using MazeGame.Maps.Interfaces;

namespace MazeGame.Engine
{
    public class LocationService : ILocationService
    {
        private readonly IRenderer renderer;

        public LocationService(IRenderer renderer)
        {
            this.renderer = renderer;
        }

        public IRoom ChangeLocation(string destination, IRoom currentRoom, IItem key)
        {
            Validator.CheckStringIfNullOrEmpty(destination);

            IExit destinationExit = currentRoom.Exits.Where(e => e.SecondRoom.Name.ToLower() == destination.ToLower()).FirstOrDefault();

            if (destinationExit != null && ((!destinationExit.IsLocked) || (key != null && key.IsUsed == false)))
            {
                if (destinationExit.IsLocked)
                {
                    key.IsUsed = true;
                }
            }
            else if (destinationExit != null && destinationExit.IsLocked)
            {
                throw new InvalidOperationException("The exit is locked!");
            }
            else
            {
                throw new InvalidOperationException("There is no room with this name!");
            }

            return destinationExit.SecondRoom;
        }

        public void PrintCurrentLocation(IRoom currentRoom)
        {
            Validator.CheckStringIfNullOrEmpty(currentRoom.Name);

            this.renderer.RenderMessageOnNewLine("Current Room: " + currentRoom.Name);
            this.renderer.RenderMessageOnNewLine("Exits to: ");

            foreach (var exit in currentRoom.Exits)
            {
                var isLockedText = exit.IsLocked ? "Locked" : "UnLocked";
                this.renderer.RenderMessageOnNewLine("   - " + exit.SecondRoom.Name + "   - " + isLockedText);
            }
        }

        public void PrintMap(IRoomProperties[,] roomPropertiesMatrix)
        {
            int width = GlobalConstants.MapSize;
            int height = GlobalConstants.MapSize;

            string s = "";
            for (int j = 0; j < height; j++) 
            {
                for (int i3 = 0; i3 < GlobalConstants.MapRoomSize; i3++)
                {
                    for (int i = 0; i < width; i++)
                    {
                        if (i3 == 0)
                        {
                            if (!roomPropertiesMatrix[i, j].Revealed)
                            {
                                s += "   ";
                            }
                            else
                            {
                                if(roomPropertiesMatrix[i, j].ExitPositions.Contains(Maps.ExitPosition.Top) )
                                    s += "╔ ╗" ;
                                else
                                    s += "╔═╗" ;
                            }
                        }
                        else if (i3 == 1)
                        {
                            if (!roomPropertiesMatrix[i, j].Revealed)
                            {

                                s += "   ";
                            }
                            else
                            {
                                if (roomPropertiesMatrix[i, j].ExitPositions.Contains(Maps.ExitPosition.Left))
                                    s += " ";
                                else
                                    s += "║";
                                if (roomPropertiesMatrix[i, j].ExitPositions.Contains(Maps.ExitPosition.Right))
                                    s += roomPropertiesMatrix[i, j].RoomName + " ";
                                else
                                    s += roomPropertiesMatrix[i, j].RoomName + "║";
                            }
                        }
                        else if (i3 == 2)
                        {
                            if (!roomPropertiesMatrix[i, j].Revealed)
                            {
                                s += "   ";
                            }
                            else
                            {
                                if (roomPropertiesMatrix[i, j].ExitPositions.Contains(Maps.ExitPosition.Bottom))
                                    s += "╚ ╝";
                                else
                                    s += "╚═╝";
                            }
                        }//end switch if
                        
                    }//end for
                    s += "\n";
                }//end for
                
            }//end for
            this.renderer.RenderMessageOnNewLine(s);
        }

    }
}
