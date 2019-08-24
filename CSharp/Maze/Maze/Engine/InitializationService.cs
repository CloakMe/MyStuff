using System.Collections.Generic;
using System.Drawing;

using MazeGame.Engine.Interfaces;
using MazeGame.Rooms;
using MazeGame.Exits;
using MazeGame.Rooms.Interfaces;
using MazeGame.Exits.Interfaces;
using MazeGame.Maps.Interfaces;
using MazeGame.Maps;

namespace MazeGame.Engine
{

    public class InitializationService : IInitializationService
    {
        public InitializationService()
        {
            this.rooms = new List<IRoom>();
        }

        private readonly ICollection<IRoom> rooms;

        public IMap InitializeMap(ICollection<IRoom> roomList)
        {
            IMap map = new Map();
            List<IRoom> toList = new List<IRoom>(roomList);
            IRoom[] roomArray = toList.ToArray();
            map.AddRoom(roomArray[0], new Point(0, 3), new List<ExitPosition>() { ExitPosition.Right });
            map.AddRoom(roomArray[1], new Point(1, 3), new List<ExitPosition>() { ExitPosition.Left, ExitPosition.Right });
            map.AddRoom(roomArray[2], new Point(2, 3), new List<ExitPosition>() { ExitPosition.Left, ExitPosition.Top, ExitPosition.Right, ExitPosition.Bottom });
            map.AddRoom(roomArray[3], new Point(3, 3), new List<ExitPosition>() { ExitPosition.Left });

            map.AddRoom(roomArray[4], new Point(2, 2), new List<ExitPosition>() { ExitPosition.Top, ExitPosition.Bottom });
            map.AddRoom(roomArray[5], new Point(2, 1), new List<ExitPosition>() { ExitPosition.Right, ExitPosition.Bottom });
            map.AddRoom(roomArray[6], new Point(3, 1), new List<ExitPosition>() { ExitPosition.Left });

            map.AddRoom(roomArray[7], new Point(2, 4), new List<ExitPosition>() { ExitPosition.Top, ExitPosition.Bottom });
            map.AddRoom(roomArray[8], new Point(2, 5), new List<ExitPosition>() { ExitPosition.Top, ExitPosition.Right });
            map.AddRoom(roomArray[9], new Point(3, 5), new List<ExitPosition>() { ExitPosition.Left });

            return map;
        }

        public ICollection<IRoom> InitializeRooms()
        {
            IRoom firstRoom = new Room("A", false);
            IRoom secondRoom = new Room("B", true);
            IRoom thirdRoom = new Room("C", false);
            IRoom fourthRoom = new Room("D", false);
            IRoom fifthRoom = new Room("E", false);
            IRoom sixthRoom = new Room("F", false);
            IRoom seventhRoom = new Room("G", true);
            IRoom eightRoom = new Room("H", false);
            IRoom ninethRoom = new Room("I", false);
            IRoom tenthRoom = new Room("J", false);

            firstRoom.Revealed = true;
            firstRoom.AddExit(new Exit(firstRoom, secondRoom, false));

            secondRoom.AddExit(new Exit(secondRoom, thirdRoom, true));
            secondRoom.AddExit(new Exit(secondRoom, firstRoom, false));

            thirdRoom.AddExit(new Exit(thirdRoom, fourthRoom, true));
            thirdRoom.AddExit(new Exit(thirdRoom, secondRoom, false));
            thirdRoom.AddExit(new Exit(thirdRoom, fifthRoom, false));
            thirdRoom.AddExit(new Exit(thirdRoom, eightRoom, false));

            fourthRoom.AddExit(new Exit(fourthRoom, thirdRoom, false));

            fifthRoom.AddExit(new Exit(fifthRoom, sixthRoom, false));
            fifthRoom.AddExit(new Exit(fifthRoom, thirdRoom, false));

            sixthRoom.AddExit(new Exit(sixthRoom, seventhRoom, true));
            sixthRoom.AddExit(new Exit(sixthRoom, fifthRoom, false));

            seventhRoom.AddExit(new Exit(seventhRoom, sixthRoom, false));

            eightRoom.AddExit(new Exit(eightRoom, ninethRoom, false));
            eightRoom.AddExit(new Exit(eightRoom, thirdRoom, false));

            ninethRoom.AddExit(new Exit(ninethRoom, tenthRoom, true));
            ninethRoom.AddExit(new Exit(ninethRoom, eightRoom, false));

            tenthRoom.AddExit(new Exit(tenthRoom, ninethRoom, false));
            

            this.rooms.Add(firstRoom);
            this.rooms.Add(secondRoom);
            this.rooms.Add(thirdRoom);
            this.rooms.Add(fourthRoom);
            this.rooms.Add(fifthRoom);
            this.rooms.Add(sixthRoom);
            this.rooms.Add(seventhRoom);
            this.rooms.Add(eightRoom);
            this.rooms.Add(ninethRoom);
            this.rooms.Add(tenthRoom);

            List<IRoom> copiedList = new List<IRoom>();
            foreach(IRoom iroom in this.rooms)
                copiedList.Add(iroom);

            return copiedList;
        }
    }
}
