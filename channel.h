#ifndef CHANNEL_H
#define CHANNEL_H


class Channel
{
public:
    Channel(const char *channelName);
	const char *getName();
	~Channel();

private:
	const char *name;
};

#endif // CHANNEL_H