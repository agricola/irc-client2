#include "linehandler.h"

LineHandler::LineHandler(ChannelList *channels) :
	channelList(channels)
{
}

LineHandler::~LineHandler()
{
}

QString LineHandler::HandleLine(QString message)
{
	Line line(message);
	return processCommand(line);
}

QString LineHandler::processCommand(Line &line)
{
	QString result = "N/A";
	// TODO: make enum for commands XD
	if (line.getCommand() == "JOIN")
	{
		QString channel = line.getMiddle().first();
		channelList->addChannel(channel);
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
