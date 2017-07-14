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
	const QString command = line.getCommand();
	const QString *trailing = line.getTrailing();
	if (command == "PRIVMSG")
	{
		QString channel = line.getMiddle().first();
		channelIndex = server->getChannelList()->getIndex(channel);
		result = line.getNickname() + " | " + line.getTrailing();
	}
	else if (command == "JOIN")
	{
		QString channel = line.getMiddle().first();
		channelIndex = server->getChannelList()->getIndex(channel);
		if (line.sentFrom(name))
		{
			server->getChannelList()->addChannel(channel);
			result = "Joined channel " + channel;
		}
		else
		{
			result =  line.getNickname() + " joined the channel";
		}
	}
	else if (command == "MODE")
	{
		//result = line.getNickname() + ""
		if (trailing != NULL)
		{
			result = line.getNickname() + " sets mode " + trailing
				+ " on " + line.getMiddle()[0];
		}
		else
		{
			QString target = line.getMiddle()[0];
			result = line.getNickname() + " sets mode "
				+ line.getMiddle()[1] + " on " + target;
			if (target.at(0) == '#')
			{
				channelIndex =
					server->getChannelList()->getIndex(target);
			}
		}
		//qDebug() << line.getFullMessage();
	}
	else
	{
		if (trailing == NULL)
		{
			result = line.getFullMessage();
		}
		else
		{
			result = *trailing;
		}
		//qDebug() << line.getFullMessage();
	}
	LineResult lineResult;
	lineResult.text = result + "\n";
	lineResult.channelIndex = channelIndex;
	return lineResult;
}
