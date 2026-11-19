/*
Standalone policy test. Run with:
g++ -std=c++20 -ITelegram/SourceFiles Telegram/Tests/channel_guard_policy_test.cpp -o /tmp/channel_guard_policy_test
*/
#include "core/channel_guard.h"

#include <cassert>
#include <initializer_list>

int main() {
	using Window::ChannelGuard::ChatKind;
	using Window::ChannelGuard::ShouldBlock;

	for (const auto joined : { false, true }) {
		for (const auto channels : { false, true }) {
			for (const auto groups : { false, true }) {
				assert(!ShouldBlock(ChatKind::User, joined, channels, groups));
				assert(ShouldBlock(ChatKind::Channel, joined, channels, groups)
					== (!joined && channels));
				assert(ShouldBlock(ChatKind::Group, joined, channels, groups)
					== (!joined && groups));
			}
		}
	}
}
