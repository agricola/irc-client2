#include "linehandler.h"

LineHandler::LineHandler(QObject *parent) : QObject(parent)
{
}

LineHandler::~LineHandler()
{
}

LineResult LineHandler::HandleLine(
	QString message,
	Server *server,
	const QString &name)
{
	Line line(message);
	return processCommand(line, server, name);
}

LineResult LineHandler::processCommand(
	Line &line,
	Server *server,
	const QString &name)
{
	size_t channelIndex = 0;
	QString result = "N/A";
	// TODO: make enum for commands XD
	if (line.getCommand() == "JOIN")
	{
		QString channel = line.getMiddle().first();
		channelIndex = server->getChannelList()->getIndex(channel);
		if (line.sentFrom(name))
		{
			server->getChannelList()->addChannel(channel);
			result = "Joined channel " + channel + "\n";
		}
		else
		{
			result =  line.getNickname() + " joined the channel \n";
		}
	}
	else if (line.getCommand() == "PRIVMSG")
	{
		QString channel = line.getMiddle().first();
		channelIndex = server->getChannelList()->getIndex(channel);
		result = line.getNickname() + " | " + line.getTrailing();
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
	LineResult lineResult;
	lineResult.text = result;
	lineResult.channelIndex = channelIndex;
	return lineResult;
}
