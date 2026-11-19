# Telegram Desktop — independently configurable channel and group restrictions

Based on the official [Telegram Desktop](https://github.com/telegramdesktop/tdesktop)
source code (branch `dev`). The original project is licensed under GPLv3 with
an OpenSSL exception; see `LEGAL`.

## Features

In **Settings → Advanced → Access to unjoined chats** there are two independent
switches, initially disabled:

- **Block channels I haven't joined**: hides unjoined broadcast channels from
  search and prevents opening them through Telegram links, forwarded posts,
  profiles, message links, stories and standard navigation.
- **Block groups I haven't joined**: applies the same restriction to basic
  groups and supergroups (including group forums).

Unjoined channel and group invitations are also blocked while the matching
restriction is on.

Both switches leave users and bots searchable and accessible. Groups and
channels the current account has joined remain accessible. The restrictions
apply per account when determining whether a chat is joined, while the two
settings themselves are client-wide.

The policy is implemented in `core/channel_guard.h` and
`window/window_session_controller.cpp`. Search result filtering is handled in
`dialogs/dialogs_inner_widget.cpp` and `dialogs/ui/dialogs_suggestions.cpp`.

## Windows build

This repository contains **source code**, not a prebuilt or independently
verified Windows executable. A Windows build has not been tested yet.

1. Clone this fork using `git clone --recursive https://github.com/eiwosq/fogram.git`
   and enter the `fogram` directory. The default `main` branch contains
   both restrictions.
2. Follow the official instructions in `docs/building-win.md` for Visual
   Studio and other prerequisites. Use this clone instead of creating another
   copy of Telegram Desktop.
3. Initialize the corresponding Visual Studio x64 developer terminal and run
   `git submodule update --init --recursive` from the `fogram` directory.
   Next, run `Telegram\build\prepare\win.bat` to prepare libraries.
4. Set your own Telegram API credentials in that terminal (do not commit them):

   ```bat
   set "TDESKTOP_API_ID=your_api_id"
   set "TDESKTOP_API_HASH=your_api_hash"
   ```

5. Run `configure_fork_windows.cmd` from the repository root.
6. Open `out\Telegram.slnx` in Visual Studio and build the `Telegram` project
   in Release configuration. See `docs/building-win.md` for details.

The configure script explicitly disables the official application's updater,
which would otherwise risk replacing your modified executable with an
unmodified Telegram Desktop release. **You will need to rebuild the fork**
when applying security and feature updates from upstream.

Do not use the restricted, test-only Telegram API credentials for a real
account. Obtain your own as described in the official build documentation.

## Test the restriction policy without Telegram dependencies

On a system with a C++20 compiler:

```sh
g++ -std=c++20 -Wall -Wextra -Werror -ITelegram/SourceFiles \
  Telegram/Tests/channel_guard_policy_test.cpp -o channel_guard_policy_test
./channel_guard_policy_test
```

## Manual acceptance checks after building

Test with each switch off/on independently, and with both on:

1. Find a user not in contacts by username and open their profile.
2. Find a bot by username and open its chat.
3. Find and open an already-joined channel and an already-joined group.
4. Search for an unjoined channel and an unjoined public group.
5. Click channel and group origin names on forwarded messages.
6. Follow `t.me/name`, `t.me/name/123`, `tg://resolve?domain=name`, and
   `t.me/+invite_hash` links, from both Telegram and an external browser.
7. Try group forum topics, messages, profile information and stories.
8. Check behavior after leaving or joining a channel or group.
9. Switch restrictions while search results and a chat view are already open.
10. Check each account separately if multiple accounts are signed in.

## Boundaries

- This is a client-side interface restriction, **not a Telegram server-side
  account restriction**. Other Telegram clients will not enforce it.
- Webpages opened directly in a browser, including `t.me` previews, are not
  under the desktop client's control.
- Unjoined chat information is determined from the locally loaded membership
  flags. Membership state and search results must be tested on a real account.
- An already-open unjoined chat is not automatically closed when a restriction
  is switched on. Opening it again is blocked; handling an open view requires
  additional UI behavior.
- A complete Windows build and manual navigation/edge-case tests are still
  required before treating the restriction as exhaustive.

