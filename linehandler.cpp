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
	const QStringList *params = line.getParams();
	const QString *channel = Channel(params);

	const QString command = line.getCommand();
	//const QString *trailing = line->last();
	// TODO: make enum for commands XD
	if (command == "PRIVMSG")
	{
		result = line.getNickname() + " | " + params->last();
	}
	else if (command == "JOIN")
	{
		if (line.sentFrom(name))
		{
			server->getChannelList()->addChannel(*channel);
			result = "Joined channel " + *channel;
		}
		else
		{
			result =  line.getNickname() + " joined the channel";
		}
	}
	else if (command == "MODE")
	{
		qDebug() << "MODE ALERT!!";
		qDebug() << params->size();
		result = line.getNickname() + " sets mode " + params->last() + " on " + params->first();
	}
	else if (command == "PART")
	{
		result = line.getNickname() + " parted " + channel;
	}
	else if (command == "QUIT")
	{
		result = line.getNickname() + " quit (" 
			+ params->last() + ")";
	}
	else if (command == "KICK")
	{
		result = line.getNickname() + " kicked " + params->at(1);
			+ " from " + *channel + " (" + params->last() + ")";
	}
	else if (command == "PING")
	{
		response = "PONG";
		qDebug() << line.getFullMessage();
		if (params->size() == 1)
		{
			response += " " + params->first();
		}
	}
	else
	{
		if (params->size() > 0)
		{
			result = params->last();
		}
		else
		{
			result = line.getFullMessage();
		}
	}
	LineResult lineResult;
	lineResult.text = result + "\n";

	int index = 0;
	if (channel != NULL)
	{
		index = server->getChannelList()->getIndex(*channel);
		delete channel;
	}
	lineResult.channelIndex = index;
	lineResult.response = response;
	return lineResult;
}

const QString *LineHandler::Channel(const QStringList *params)
{
	QString *channel = NULL;
	if (!params->isEmpty())
	{
		QStringList p = *params;
		for (QStringList::iterator it = p.begin(); it != p.end(); ++it)
		{
			const QString param = *it;
			if (param.at(0) == "#")
			{
				channel = new QString(param);
				//qDebug() << "FOUND";
				break;
			}
		}
	}
	/*QString t = (channel == NULL) ? " NULL " : " NOT NULL ";
	qDebug() << t;*/
	return channel;
}
