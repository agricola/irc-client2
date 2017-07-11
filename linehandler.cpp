#include "linehandler.h"

LineHandler::LineHandler()
{
}

LineHandler::~LineHandler()
{
}

QString LineHandler::HandleLine(QString message, Server *server)
{
	Line line(message);
	return processCommand(line, server);
}

QString LineHandler::processCommand(Line &line, Server *server)
{
	QString result = "N/A";
	// TODO: make enum for commands XD
	if (line.getCommand() == "JOIN")
	{
		QString channel = line.getMiddle().first();
		server->getChannels()->addChannel(channel);
		result = "Joined channel " + channel + "\n";
	}
	else
	{
		if (line.getTrailing() == NULL)
		{
			result = line.getFullMessage();
		}
		else
		{
			result = line.getTrailing();
		}
	}
	return result;
}
