/*
This file is part of Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

class PeerData;

namespace Window::ChannelGuard {

extern const char kOptionBlockUnjoinedChannels[];
extern const char kOptionBlockUnjoinedGroups[];

// Independent rules for broadcast channels and groups (including supergroups).
// Users and bots, as well as joined chats, remain accessible.
enum class ChatKind {
	User,
	Channel,
	Group,
};

[[nodiscard]] constexpr bool ShouldBlock(
		ChatKind kind,
		bool joined,
		bool blockChannels,
		bool blockGroups) {
	return !joined && ((kind == ChatKind::Channel && blockChannels)
		|| (kind == ChatKind::Group && blockGroups));
}

[[nodiscard]] bool ChannelsEnabled();
[[nodiscard]] bool GroupsEnabled();
[[nodiscard]] bool Blocks(const PeerData *peer);

} // namespace Window::ChannelGuard
