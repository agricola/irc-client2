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
	const QString *channel = ChannelName(params);

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
			
			result = "Joined channel " + *channel;
			Channel *c = server->getChannelList()->addChannel(*channel);
		}
		else
		{
			result =  line.getNickname() + " joined the channel";
			Channel *c = server->getChannelList()->getChannel(*channel);
			c->getUserList()->addUser(line.getNickname());
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
		Channel *c = server->getChannelList()->getChannel(*channel);
		c->getUserList()->removeUser(line.getNickname());
	}
	else if (command == "QUIT")
	{
		result = line.getNickname() + " quit (" 
			+ params->last() + ")";
		ChannelList *list = server->getChannelList();
		const QString nick = line.getNickname();
		list->forEach([nick](Channel *c) {
			qDebug() << "in";
			c->getUserList()->removeUser(nick);
		});
	}
	else if (command == "KICK")
	{
		result = line.getNickname() + " kicked " + params->at(1);
			+ " from " + *channel + " (" + params->last() + ")";
			Channel *c = server->getChannelList()->getChannel(*channel);
		c->getUserList()->removeUser(params->last());
	}
	else if (command == "353")
	{
		qDebug() << line.getParams()->size();
		//qDebug() << (server->getChannelList()->getChannel("#test4") == NULL);
		UserList *u = server->getChannelList()->getChannel(*channel)
			->getUserList();
		if (!u->isInitialized())
		{
			u->addUsers(params->last());
		}
	}
	else if (command == "366")
	{
		UserList *u = server->getChannelList()->getChannel(*channel)
			->getUserList();
		u->setIsInitialized(true);
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

const QString *LineHandler::ChannelName(const QStringList *params)
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
