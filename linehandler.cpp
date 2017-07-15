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
	QString result = "N/A";
	QString response = "";
	qDebug() << line.getFullMessage();
	// get channel and index if theres a channel in line
	const QStringList *mid = line.getMiddle();
	auto channelInfo = ifChannel(mid, server);
	QString channel = std::get<0>(channelInfo);
	size_t channelIndex = std::get<1>(channelInfo);

	const QString command = line.getCommand();
	const QString *trailing = line.getTrailing();
	// TODO: make enum for commands XD
	if (command == "PRIVMSG")
	{
		result = line.getNickname() + " | " + line.getTrailing();
	}
	else if (command == "JOIN")
	{
		//assert(mid != NULL);
		//assert(!mid->isEmpty());
		//assert(mid->at(0).at(0) == '#');
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
		if (trailing != NULL)
		{
			result = line.getNickname() + " sets mode " + trailing
				+ " on " + mid->at(0);
		}
		else
		{
			QString target = mid->at(0);
			result = line.getNickname() + " sets mode "
				+ line.getMiddle()->at(1) + " on " + target;
			/*if (target.at(0) == '#')
			{
				channelIndex =
					server->getChannelList()->getIndex(target);
			}*/
		}
	}
	else if (command == "PART")
	{
		result = line.getNickname() + " parted " + channel;
	}
	else if (command == "QUIT")
	{
		result = line.getNickname() + " quit (" 
			+ line.getTrailing() + ")";
	}
	else if (command == "KICK")
	{
		result = line.getNickname() + " kicked " + mid->at(1);
			+ " from " + channel + " (" + line.getTrailing() + ")";
	}
	else if (command == "PING")
	{
		response = "PONG";
		qDebug() << line.getFullMessage();
		if (trailing != NULL)
		{
			response += " " + *trailing;
		}
	}
	else
	{
		if (trailing != NULL)
		{
			result = *trailing;
		}
		else
		{
			result = line.getFullMessage();
		}
	}
	LineResult lineResult;
	lineResult.text = result + "\n";
	lineResult.channelIndex = channelIndex;
	lineResult.response = response;
	return lineResult;
}

std::tuple<QString, size_t> LineHandler::ifChannel(
	const QStringList *mid, Server *server)
{
	QString channel = "(MISSING CHANNEL XD)";
	size_t index = 0;
	if (mid != NULL && !mid->isEmpty() && mid->at(0).at(0) == '#')
	{
		channel = mid->at(0);
		index = server->getChannelList()->getIndex(channel);
	}
	return std::make_tuple(channel, index);
}
