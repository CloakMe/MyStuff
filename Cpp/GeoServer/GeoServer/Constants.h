#pragma once
namespace Constants
{
    char const* const TRIM_CHARS = " \t\n\r\f\v";
	char const COMMA = ',';
    char const SPACE = ' ';
	int const BUF_SIZE = 1025;
	int const MAX_CLIENTS = 30;
    int const MAX_PENDING_CONNECTIONS = 3;
    int const PORT = 54000;
    float const EARTH_RADIUS = 6378137; // Radius of earth in Meters
    double const PI = 3.14159265358979323846;  /* pi */

    char const* const CMD_SET = "set";
    char const* const CMD_SPEED = "speed";
    char const* const CMD_EXIT = "exit";
    char const* const CMD_UNKNOWN = "unknown";

    int const CMD_SET_SIZE = 4;
    int const CMD_SPEED_SIZE = 2;
    int const CMD_EXIT_SIZE = 1;
}